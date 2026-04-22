#include "block.hpp"
#include <iostream>
#include <sstream>
#include <fmt/color.h>
#include <fmt/format.h>

using namespace std;
using namespace cncpp;

//LIFECYCLE
Block::Block(string line) : _line(line), _n(0) {}

Block::Block(string line, Block &prev) : Block(line) {
  (*this) = prev;
}
Block::~Block() {
  cerr << "Block " << _line << "destroyed." <<endl;
}

string Block::desc(bool colored = true) {
  if(!parsed) {
    throw runtime_error("Not parsed yet");
  }
  stringstream ss;
  auto color = fmt::color::green;
  if(_type == BlockType::NO_MOTION) {
    color = fmt::color::gray;
  }
  else if(_type == BlockType::RAPID) {
    color = fmt::color::red;
  }
  //Remember fmt format string
  //{:} -> print as is
  //{:>3} -> rigth aligned 3 chars wide
  //{:0>2} -> pad with "0", rigth aligned, 2 chars wide
  //{:-^9} -> pad with "-", center aligned, 9 chars wide
  //{:>5.0f} -> rigth aligned, 5 characters wide, 0 decimal float
  ss << fmt::format("[{:>3}] ", _n);
  if(colored) {
    ss << fmt::format("G{:0>2} ", fmt::styled(static_cast<int>(_type), fmt::fg(color)));
  } else {
    ss << fmt::format("G{:0>2} ", static_cast<int>(_type));
  }
  ss << _target.desc(colored);
  ss << fmt::format(" F{:>5.0f} S{:>4.0f} ", _feedrate, _spindle);
  ss << fmt::format("T{:0>2} M{:0>2} ", _tool, _m);
  ss << fmt::format("L{:>6.2f}mm DT{:>6.2f}s", _length, _profile.dt);
  return ss.str();
}

Block &Block::operator=(Block &b) {
  if(!b._parsed) {
    throw runtime_error("Previous block has not been parsed!");
  }
  _tool = b._tool;
  _feedrate = b._feedrate;
  _spindle = b._spindle;
  _n = b._n + 1;
  _target.reset();
  prev = &b;
  b.next = this;
}

//OPERATION/OPERATORS
Block &Block::parse(const Machine *m) {
  _machine = m;
  stringstream ss(_line);
  string token;

  while(ss >> token) {
    try{
      if(!parse_token(token)) {break;}
    }
    catch(runtime_error &e) {
      stringstream es;
      es << "Parsing error at line: " << _line << endl;
      es << "Token: " << token << endl;
      es << "Exception: " << e.what() << endl;
      throw runtime_error(es.str());
    }
  }

  //Modal behaviour
  _target.modal(start_point());
  _delta = _target.delta(start_point());
  _acc = _machine->A();
  _length = _delta.length();

  //Calculate the profile
  switch (_type) {
  case BlockType::LINE:
    _arc_feedrate = _feedrate;
    compute();
    break;
  
  case BlockType::CWA:
  case BlockType::CCWA:
    calc_arc();
    _arc_feedrate = min(_feedrate, pow(pow(_machine->A(), 2) * pow(_r, 2), 0.25) * 60);

    compute();
    break;
  default:
    break;
  }

  _parsed = true;
  return *this;

}

data_t Block::lambda(data_t time, data_t &speed) {
  if(!_parsed) {
    throw runtime_error("Block not parsed");
  }
  return _profile.lambda(time, speed);
}

Point Block::interpolate(data_t lambda) {
  if(!_parsed) {
    throw runtime_error("Block not parsed");
  }
  Point result = Point();
  Point p0 = start_point();

  //Interpolation:
  //x(t) = x(0) + d_x * lambda(t)
  //y(t) = y(0) + d_y * lambda(t)
  //z(t) = z(0) + d_z * lambda(t)

  if(_type == BlockType::LINE) {
    result.x(p0.x() + _delta.x() * lambda);
    result.y(p0.y() + _delta.y() * lambda);
  }
  else if(_type == BlockType::CWA || _type == BlockType::CCWA) {
    data_t angle = _theta_0 + _dtheta * lambda;
    result.x(_center.x()+_r * cos(angle));
    result.y(_center.y()+_r * sin(angle));
  }
  else {
    throw runtime_error("Cannot interpolate block" + _line);
  }
  
  result.z(prev->target().z() + _delta.z() * lambda);

  return result;
}

Point Block::interpolate(data_t time, data_t &lambda, data_t &speed) {
  lambda = this->lambda(time, speed);
}

//b.walk ([&](Block &b, data_t t, data_t l, data_t s) {
//  do something!;
//});
void Block::walk(std::function<void(Block &b, data_t t, data_t l, data_t s)> func) {
  data_t t = 0.0;
  data_t l;
  data_t s;
  while(t < _profile.dt) {
    l = lambda(t, s);
    func(*this, t, l, s);
    t += _machine->tq();
  }
}

//PRIVATE MEMBER 
bool Block::parse_token(string &token) {
  bool res = true;
  char cmd = toupper(token[0]); // g -> G, G -> G
  string arg = token.substr(1);
  if(cmd == '#' || cmd == ';') { //Comments
    return false;
  }
  if(arg.empty()) {
    throw runtime_error("Empty command argument");
  }
  switch (cmd) {
  case 'N':
    _n = stoi(arg);
    if(prev && _n <= prev->_n) { //Block number not increasing
      throw runtime_error("Block number MUST be increasing: " + to_string(prev->_n));
    }
    break;
  case 'G':
    _type = static_cast<BlockType>(stoi(arg));
    break;
  case 'X':
    _target.x(stod(arg));
    break;
  case 'Y':
    _target.y(stod(arg));
    break;
  case 'Z':
    _target.z(stod(arg));
    break;
  case 'I':
    _i = stod(arg);
    break;
  case 'J':
    _j = stod(arg);
    break;
  case 'R':
    _r = stod(arg);
    break;
  case 'F':
    _feedrate = stod(arg);
    break;
  case 'S':
    _spindle = stod(arg);
    break;
  case 'T':
    _tool = stoi(arg);
    break;
  case 'M':
    _m = stoi(arg);
    break;
  default:
    stringstream ss;
    ss << "Unknown/Unsupported command: '" << token << "'";
    throw runtime_error(ss.str()); 
    break;
  }
  return res;
}

Point Block::start_point() {
  return prev ? prev->target() : _machine->zero();
}

void Block::compute() {

}

void Block::calc_arc() {

}