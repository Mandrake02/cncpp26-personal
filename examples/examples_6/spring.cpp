#include "spring.h"

Spring::Spring(std::string name, double k, double m) : Model(name, 2, 0), _k(k), _m(m) {}

Spring::~Spring() {}

Vec Spring::compute_x_dot_impl(double dt, Vec inputs, Vec states) {
  Vec x_dot = states;
  //states[0] position
  //states[1] velocity
  x_dot[0] = states[1];
  x_dot[1] = -states[0] * (_k / _m);

  return x_dot;
}