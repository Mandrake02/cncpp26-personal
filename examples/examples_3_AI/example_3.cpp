#include "Vector2D.h"
#include <fstream>
#include <iostream>

int main() {
  // Vector2D v1(3.0, 4.0);
  // Vector2D v2("custom_vec", 1.0, 2.0);

  // std::cout << "Vector 1: " << v1 << std::endl;
  // std::cout << "Vector 2: " << v2 << std::endl;

  // std::cout << "Norm of Vector 1: " << v1.norm() << std::endl;
  // std::cout << "Distance from Vector 1 to Vector 2: " << v1.distance_to(v2)
  // << std::endl; Vector2D v3 = v1 + v2; std::cout << "Vector 1 + Vector 2: "
  // << v3 << std::endl;

  // Create a vector of Vector2D objects and print a csv file

  // std::fstream out;
  // out.open("output.csv", std::ios::out);

  std::vector<Vector2D> esercizio;

  esercizio.push_back(Vector2D("P1", 6, 7));
  esercizio.push_back(Vector2D("P2", 1, 2));
  esercizio.push_back(Vector2D("P3", 5, 4));

  std::cout << Vector2D::to_csv_header() << std::endl;

  for (const auto &element : esercizio) {
    std::cout << element.to_csv_row() << std::endl;
  }

  // out << Vector2D::to_csv_header() <<std::endl;

  // for(auto& element : esercizio) {
  //   out << element.to_csv_row() <<std::endl;
  // }

  // out.close();
  return 0;
}