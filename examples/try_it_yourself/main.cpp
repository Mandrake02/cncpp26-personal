#include <iostream>
#include <vector>
#include <string>
#include "vector2D.h"

int main() {
  std::vector<Vector2D> esercizio;
  esercizio.push_back(Vector2D("P1", 6, 7));
  esercizio.push_back(Vector2D("P2", 1, 2));
  esercizio.push_back(Vector2D("P3", 5, 4));
  
  esercizio[0].to_csv_header();
  for(auto i=0; i<esercizio.size(); ++i) {
    esercizio[i].to_csv_row();
  }
  
  for(auto i=0; i<esercizio.size(); ++i) {
    esercizio[i].print();
  }
  for(auto& element : esercizio) {
    element.scale(2);
  }
  for(auto i=0; i<esercizio.size(); ++i) {
    esercizio[i].print();
  }
  return 0;
}