#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
  public:
  Triangle();
  void num_of_sides() override;
};

#endif