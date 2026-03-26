#include "Vector2D.h"
#include <iostream>

int main() {
  Vector2D v1(3.0, 4.0);
  Vector2D v2("custom_vec", 1.0, 2.0);

  std::cout << "Vector 1: " << v1 << std::endl;
  std::cout << "Vector 2: " << v2 << std::endl;

  std::cout << "Norm of Vector 1: " << v1.norm() << std::endl;
  std::cout << "Distance from Vector 1 to Vector 2: " << v1.distance_to(v2) << std::endl;
  Vector2D v3 = v1 + v2;
  std::cout << "Vector 1 + Vector 2: " << v3 << std::endl;
  return 0;
}