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