// Vector2D class definition
// Implement a simple 2D vector class with basic operations and CSV output
// functionality.
#pragma once

#include <ostream>
#include <string>

/**
 * @brief Simple 2D vector with label, arithmetic operations, and CSV utilities.
 */
class Vector2D {
public:
  /**
   * @brief Construct a vector at the origin with an empty label.
   */
  Vector2D();

  /**
   * @brief Construct a vector with the given coordinates.
   * @param x X coordinate.
   * @param y Y coordinate.
   */
  Vector2D(double x, double y);

  /**
   * @brief Construct a labeled vector with the given coordinates.
   * @param label Label associated with the vector.
   * @param x X coordinate.
   * @param y Y coordinate.
   */
  Vector2D(const std::string label, double x, double y);

  /**
   * @brief Get the X coordinate.
   * @return The X coordinate value.
   */
  double x() const;

  /**
   * @brief Get the Y coordinate.
   * @return The Y coordinate value.
   */
  double y() const;

  /**
   * @brief Get the vector label.
   * @return The label string.
   */
  std::string label() const;

  /**
   * @brief Compute the Euclidean norm (magnitude) of the vector.
   * @return The norm of the vector.
   */
  double norm() const;

  /**
   * @brief Compute the Euclidean distance to another vector.
   * @param other The other vector.
   * @return The distance between this vector and @p other.
   */
  double distance_to(const Vector2D &other) const;

  /**
   * @brief Add two vectors.
   * @param other The vector to add.
   * @return The resulting vector sum.
   */
  Vector2D operator+(const Vector2D &other) const;

  /**
   * @brief Subtract another vector from this vector.
   * @param other The vector to subtract.
   * @return The resulting vector difference.
   */
  Vector2D operator-(const Vector2D &other) const;

  /**
   * @brief Scale the vector by a scalar.
   * @param scalar Multiplicative factor.
   * @return The scaled vector.
   */
  Vector2D operator*(double scalar) const;

  /**
   * @brief Set the vector coordinates.
   * @param x New X coordinate.
   * @param y New Y coordinate.
   */
  void set(double x, double y);

  /**
   * @brief Serialize the vector as a CSV row.
   * @return A CSV-formatted row representing this vector.
   */
  std::string to_csv_row() const;

  // Static members
  // call it like this: Vector2D::to_csv_header()
  /**
   * @brief Get the CSV header corresponding to @ref to_csv_row output.
   * @return A CSV header string.
   */
  static std::string to_csv_header();

  /**
   * @brief Stream insertion operator for human-readable output.
   * @param os Output stream.
   * @param v Vector to print.
   * @return Reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &os, const Vector2D &v);

private:
  double _x;
  double _y;
  std::string _label;
  static size_t _vector_count;
};

std::ostream &operator<<(std::ostream &os, const Vector2D &v);