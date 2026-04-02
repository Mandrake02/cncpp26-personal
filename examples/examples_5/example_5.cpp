#include "demo_smart_pointers.h"
#include <iostream>
#include <vector>

class Shape {

};

class Circle : public Shape {

};

class Triangle : public Shape {

};

int main() {
  demo_smart_pointers();
  std::vector<std::unique_ptr<Shape>> shapes;
  std::unique_ptr<Circle> c1 = std::make_unique<Circle>();
  shapes.push_back(std::move(c1));
  std::unique_ptr<Triangle> t1 = std::make_unique<Triangle>();
  shapes.push_back(std::move(t1));
  return 0;
}