#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Vector2D {
private:
  std::string label;

public:
  double x;
  double y;
  Vector2D();
  Vector2D(std::string label, double x, double y);
  void set_label(std::string new_label);
  void set(double x, double y);
  void print() const;
  void to_csv_header() const;
  void to_csv_row() const;
  double norm() const;
  void scale(double factor);
  void add(const Vector2D &other);
};

#endif