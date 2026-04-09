#include "spring.h"

Spring::Spring(std::string name, double k, double m) : Model(name, STATES_NUMBER, INPUTS_NUMBER), _k(k), _m(m) {}
Spring::Spring(std::string name) : Model(name, STATES_NUMBER, INPUTS_NUMBER), _k(100.0), _m(3.0) {}

Spring::~Spring() {}

Vec Spring::compute_x_dot_impl(double dt, Vec inputs, Vec states) {
  Vec x_dot = states;
  //states[0] position
  //states[1] velocity
  x_dot[STATE_X] = states[STATE_V];
  x_dot[STATE_V] = -states[STATE_X] * (_k / _m);

  return x_dot;
}