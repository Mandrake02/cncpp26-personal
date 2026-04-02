#include <string>
#include <iostream>
#include "Shape.h"

Shape::Shape(std::string name) {
  this->_name = name;
}

Shape::~Shape() {

}

void Shape::print() {
  std::cout << "Name: " << this->_name << std::endl;
}

void Shape::num_of_sides() {
  std::cout << "undefined" << std::endl;
}
