#include "defines.hpp"
#include "program.hpp"
#include <fstream>
#include <sstream>

using namespace std;
using namespace cncpp;


//LIFECYCLE

Program::Program(const std::string &f, Machine *m) :_filename(f), _machine(m) {
  load(_filename);
}

Program::Program(Machine *m) : _machine(m) {}

Program::~Program() {}

std::string Program::desc(bool colored) const {
  ostringstream ss;
  for(auto &current_block : *this) {
    ss << current_block << endl;
  }
  return ss.str();
}

//OPERATORS/OPERATIONS

void Program::load(const string &filename, bool append) {
  
  _filename = filename;
  ifstream file(_filename);
  
  if(!file.is_open()) {
    throw runtime_error("Could not open: " + _filename);
  }
  
  if(!append) {
    reset();
  }
  
  string line;
  while(getline(file, line)) {
    if(line[0] == '#') continue;
    *this << line;
  }
  
  file.close();
}

Program &Program::operator<<(const std::string &line) {
  if(size() > 0) { //This is not the fisrt block
    emplace_back(line, back());
  } else { //This is the first block
    emplace_back(line);
  }
  back().parse(_machine);
  return *this;
}

block_iterator Program::load_next() {
  if(_current == end()) {
    _current = begin();
  } else {
    _current++;
  }
  _done = (_current == end());
  return _current;
}

void Program::rewind() {
  _current = begin();
  _done = false;
}

void Program::reset() {
  clear();
  rewind();
}

#ifdef CNCPP_TEST_PROGRAM

#include <rang.hpp>
#include <fmt/format.h>


int main(int argc, const char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <file.g>" << endl;
    return EXIT_FAILURE;
  }
  Machine machine{};
  Program program{&machine};
  try {
    program.load(argv[1]);
  } catch (exception &e) {
    cerr << rang::fg::red << "Error: " << e.what() << rang::fg::reset << endl;
    return EXIT_FAILURE;
  }
  cerr << program << endl;
  cerr << "Sequence of positions (to stdout only):" << endl;
  cout << "n,t_tot,t,lambda,s,x,y,z" << endl;
  data_t t_tot = 0;
  for(auto &current_block : program) {
    //cout << program.current() << ",";
    current_block.walk([&](Block &b, data_t t, data_t l, data_t s) {
      if (b.type() > Block::BlockType::RAPID && b.type() < Block::BlockType::NO_MOTION)  {
        Point pos = b.interpolate(l);
        cout << fmt::format("{:},{:},{:},{:},{:},{:},{:},{:}", b.n(), t_tot, t, l, s, pos.x(), pos.y(), pos.z()) << endl;
        t_tot += machine.tq();
      };
    });
  }
  
  return EXIT_SUCCESS;
}

#endif //CNCPP_TEST_PROGRAM

//TASK: If the error is under the _max_error in the machine class we don't want to rise an error
//TASK: We want to rise an error in R is nan
//TASK: Fix the color missinh situation