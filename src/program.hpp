#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "defines.hpp"
#include "machine.hpp"
#include "block.hpp"
#include <list>

namespace cncpp {

class Program : public Object, public std::list<Block> {
public:
  //LIFECYCLE
  Program(const std::string &f, Machine *m);
  Program(Machine *m);
  ~Program();
  std::string desc(bool colored = true) const override;

  //OPERATORS/OPERATIONS
  void load(const std::string &filename, bool append = false);
  Program &operator<<(const std::string &line);
  iterator load_next();
  void rewind();
  void reset();

  //ACCESSORS
  iterator current();
  bool done();
private:
  Machine *_machine = nullptr;
  std::string _filename = "";
  iterator _current = this->end();
  bool _done = false;
};

} //namespace cncpp

#endif