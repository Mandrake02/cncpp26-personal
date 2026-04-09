#include "forced_spring.h"

ForcedSpring::ForcedSpring(std::string name)
    : Model(name, STATES_NUMBER, INPUTS_NUMBER), _k(100.0), _m(3.0) {}

ForcedSpring::ForcedSpring(std::string name, double k, double m)
    : Model(name, STATES_NUMBER, INPUTS_NUMBER), _k(k), _m(m) {}

Vec ForcedSpring::compute_x_dot_impl(double dt, Vec inputs, Vec states) {
  Vec x_dot(states.size());
  x_dot[STATE_X] = states[STATE_V];
  x_dot[STATE_V] = (inputs[INPUT_F] - states[STATE_X] * _k) / _m;
  return x_dot;
}