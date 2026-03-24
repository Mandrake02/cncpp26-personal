#include "vector2D.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

Vector2D::Vector2D() {
  this->label = "Default";
  this->x = 0.0;
  this->y = 0.0;
}

Vector2D::Vector2D(std::string label, double x, double y) {
  this->label = label;
  this->x = x;
  this->y = y;
}

void Vector2D::set_label(std::string new_label) { this->label = new_label; }

void Vector2D::set(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector2D::print() const {
  std::cout << "Label: " << this->label << ", x value: " << this->x
            << ", y value: " << y << std::endl;
}

void Vector2D::to_csv_header() const {
  std::cout << "Label" << ", " << "x" << ", " << "y" << std::endl;
}

void Vector2D::to_csv_row() const {
  std::cout << "\"" << label << "\", " << x << ", " << y << std::endl;
}

double Vector2D::norm() const { return std::hypot(this->x, this->y); }

void Vector2D::scale(double factor) {
  this->x *= factor;
  this->y *= factor;
}

void Vector2D::add(const Vector2D &other) {
  this->x += other.x;
  this->y += other.y;
}