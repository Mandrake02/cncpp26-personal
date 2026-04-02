#include "Triangle.h"
#include "Shape.h"

Triangle::Triangle() : Shape("triangle") {
  
}

void Triangle::num_of_sides() {
  std::cout << "three" << std::endl;
}