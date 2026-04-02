#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>

class Shape{
  public:
  Shape(std::string name);
  virtual ~Shape();
  void print();
  virtual void num_of_sides();

  private:
  std::string _name;
};

#endif