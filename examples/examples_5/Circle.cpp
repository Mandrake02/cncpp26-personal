#include "Circle.h"
#include "Shape.h"

Circle::Circle() : Shape("circe") {

}

void Circle::num_of_sides() {
  std::cout << "infinite" << std::endl;
}