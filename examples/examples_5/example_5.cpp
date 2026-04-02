#include "demo_smart_pointers.h"
#include "Shape.h"
#include "Circle.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
  //demo_smart_pointers();
  std::vector<std::unique_ptr<Shape>> shapes;
  std::unique_ptr<Circle> c1 = std::make_unique<Circle>();
  shapes.push_back(std::move(c1));
  std::unique_ptr<Triangle> t1 = std::make_unique<Triangle>();
  shapes.push_back(std::move(t1));

  for (size_t i = 0; i < shapes.size(); i++)
  {
    shapes[i]->print();
    shapes[i]->num_of_sides();
  }

  return 0;
}