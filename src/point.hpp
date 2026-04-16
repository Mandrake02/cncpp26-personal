/*
Point class
Author: Andrea Malacarne

Represent a 3-D coordinate position in space with optional components and basic operation
*/

#ifndef POINT_HPP
#define POINT_HPP

#include "defines.hpp"
#include <vector>
#include <string>

namespace cncpp{

//class names use CamelCase
//Attributes and methods use snake_case

class Point{
public:
  //LIFECYCLE
  Point(opt_data_t x = std::nullopt, opt_data_t y = std::nullopt, opt_data_t z = std::nullopt);
  std::string desc(bool colored = true) const;
  void reset(); 


  //OPERATORS/OPERATIONS
  Point delta(Point const &o) const;
  data_t length() const;
  void modal(Point const &o);

  Point &operator=(Point const &o); // p1 = p2
  Point operator+(Point const &o) const; // p3 = p1 + p2

  bool is_complete() const {return _x && _y && _z;}

  //ACCESSOR
  data_t x() const {return _x.value();}
  data_t y() const {return _y.value();}
  data_t z() const {return _z.value();}

  data_t x(data_t v) {return(_x = v).value();} // == _x = v; return _x.value();
  data_t y(data_t v) {return(_y = v).value();}
  data_t z(data_t v) {return(_z = v).value();}
  
  std::vector<data_t> vec() const;

  friend 
  std::ostream &operator<<(std::ostream &os, const Point &v);

private:
  opt_data_t _x = std::nullopt;
  opt_data_t _y = std::nullopt;
  opt_data_t _z = std::nullopt;
};

std::ostream &operator<<(std::ostream &os, const Point &v);

} //namespace cncpp end

#endif