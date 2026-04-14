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

bool Spring::set_config(Str2Dbl config) {
  bool flag = true;
  if(config.find("k") != config.end()) {
    _k = config["k"];
  } 
  else {
    std::cout << "Key k was not found" << std::endl;
    flag = false;
  }
  if(config.find("m") != config.end()) {
    _m = config["m"];
  } 
  else {
    std::cout << "Key m was not found" << std::endl;
    flag = false;
  }
  return flag;
}

std::optional<Str2Dbl> Spring::get_config() const {
  return Str2Dbl{
      {"k", _k},
      {"m", _m},
    };
}