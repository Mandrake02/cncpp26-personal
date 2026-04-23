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

/**
 * @brief Represents a 3D point with optional coordinates.
 *
 * The class stores X, Y and Z components as optional values so it can
 * represent both complete and partial coordinates (modal CNC-style behavior).
 */
class Point : public Object{
public:
  //LIFECYCLE
  /**
   * @brief Constructs a point from optional coordinates.
   * @param x Optional X coordinate.
   * @param y Optional Y coordinate.
   * @param z Optional Z coordinate.
   */
  Point(opt_data_t x = std::nullopt, opt_data_t y = std::nullopt, opt_data_t z = std::nullopt);

  /**
   * @brief Returns a formatted string description of the point.
   * @param colored If true, use terminal color formatting for coordinates.
   * @return Formatted string representation in the form [x, y, z].
   */
  std::string desc(bool colored = true) const override;

  /**
   * @brief Resets all coordinates to an unset state.
   */
  void reset(); 


  //OPERATORS/OPERATIONS
  /**
   * @brief Computes the coordinate-wise difference with another point.
   * @param o Point to subtract from this point.
   * @return A new point equal to this - o.
   * @throw std::runtime_error If either point is not complete.
   */
  Point delta(Point const &o) const;

  /**
   * @brief Computes the Euclidean norm of the point.
   * @return The point length, i.e. sqrt(x^2 + y^2 + z^2).
   * @throw std::runtime_error If the point is not complete.
   */
  data_t length() const;

  /**
   * @brief Applies modal completion using another point.
   *
   * Copies each coordinate from @p o only if that coordinate is set in @p o
   * and currently unset in this point.
   *
   * @param o Source point used for modal completion.
   */
  void modal(Point const &o);

  /**
   * @brief Assigns coordinates from another point.
   * @param o Source point.
   * @return Reference to this point.
   */
  Point &operator=(Point const &o); // p1 = p2

  /**
   * @brief Computes the coordinate-wise sum with another point.
   * @param o Point to add.
   * @return A new point equal to this + o.
   * @throw std::runtime_error If either point is not complete.
   */
  Point operator+(Point const &o) const; // p3 = p1 + p2

  /**
   * @brief Checks whether all coordinates are set.
   * @return True if X, Y and Z are all available, false otherwise.
   */
  bool is_complete() const {return _x && _y && _z;}

  //ACCESSOR
  /**
   * @brief Returns the X coordinate.
   * @return X coordinate value.
   * @note Requires X to be set.
   */
  data_t x() const {return _x.value();}

  /**
   * @brief Returns the Y coordinate.
   * @return Y coordinate value.
   * @note Requires Y to be set.
   */
  data_t y() const {return _y.value();}

  /**
   * @brief Returns the Z coordinate.
   * @return Z coordinate value.
   * @note Requires Z to be set.
   */
  data_t z() const {return _z.value();}

  /**
   * @brief Sets the X coordinate.
   * @param v New X coordinate value.
   * @return The stored X coordinate.
   */
  data_t x(data_t v) {return(_x = v).value();} // == _x = v; return _x.value();

  /**
   * @brief Sets the Y coordinate.
   * @param v New Y coordinate value.
   * @return The stored Y coordinate.
   */
  data_t y(data_t v) {return(_y = v).value();}

  /**
   * @brief Sets the Z coordinate.
   * @param v New Z coordinate value.
   * @return The stored Z coordinate.
   */
  data_t z(data_t v) {return(_z = v).value();}
  
  /**
   * @brief Converts the point to a 3-element vector.
   * @return Vector containing {x, y, z}.
   * @throw std::runtime_error If the point is not complete.
   */
  std::vector<data_t> vec() const;


private:
  opt_data_t _x = std::nullopt;
  opt_data_t _y = std::nullopt;
  opt_data_t _z = std::nullopt;
};


} //namespace cncpp end

#endif