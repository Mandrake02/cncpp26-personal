/*
Common defines file
Author: Andrea Malacarne, 2026
...
*/

#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <optional>
#include <string>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <list>

// Semantic versioning
#define CNCPP_VERSION "0.1.0" //Major.Minor.Patch version
                              //Patch version -> mainly bug fixes
                              //Minor version changed when changing some user interface that could break something previous
                              //Major version changed when changing A LOT -> features and user interface

#define CNCPP_NUMBERS_WIDTH "9"
#define CNCPP_NUMBERS_PRECISION "3"

using data_t = double; //Type for data value -> userful to change if the pc we're using is not strong enough
                       //If we want to change all from double -> float we just need to change this line of code

using opt_data_t = std::optional<data_t>; //We will need it for optional values
using opt_int_t = std::optional<int>;
using iterator = std::list<Block>::iterator;

namespace cncpp{

class Object{
public:
  virtual std::string desc(bool colored = true) const = 0;
  friend std::ostream &operator<<(std::ostream &os, const Object &v);
};
inline std::ostream &operator<<(std::ostream &os, const Object &v) {
  bool is_terminal = (&os == &std::cout && isatty(STDOUT_FILENO)) ||
                     (&os == &std::cerr && isatty(STDERR_FILENO));
  os << v.desc(is_terminal);
  return os;
} //namespace cncpp
}

#endif