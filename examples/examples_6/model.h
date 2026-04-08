#pragma once

#include "types.h"
#include <iostream>
#include <fstream>
#include <string>

class Model {
public:
  Model(std::string name, size_t n_states, size_t n_inputs);
  ~Model();

  void set_x0(Vec initial_states);
  void step(double dt, Vec inputs);

protected:
  std::string _name;

  virtual Vec compute_x_dot_impl(double dt, Vec inputs, Vec states) = 0;


private:
  Vec compute_x_dot(double dt, Vec inputs, Vec states);

  size_t _n_states;
  size_t _n_inputs;
  std::ofstream _log_file;

  Vec _states;
  double _t; //Time
};