#include "model.h"
#include <exception>

Model::Model(std::string name, size_t n_states, size_t n_inputs)
    : _name(name), _n_inputs(n_inputs), _n_states(n_states) 
{
  _states.resize(_n_states, 0.0);
}

Model::~Model() {}

void Model::set_x0(Vec initial_states) {
  if(_states.size() != initial_states.size()) {
    throw std::invalid_argument("Invalid size");
  }
  _states = initial_states;

}

void Model::step(double dt, Vec inputs) {
  Vec x_dot = compute_x_dot(dt, inputs, _states);
  for(size_t i = 0; i<_n_states; i++) {
    _states[i] = _states[i] + dt * x_dot[i];
  }
  _t += dt;
}

Vec Model::compute_x_dot(double dt, Vec inputs, Vec states) {
  if(dt <= 0) {
    throw std::invalid_argument("Invalid dt");
  }
  if(inputs.size() != _n_inputs) {
    throw std::invalid_argument("Invalid input sizes");
  }
  return compute_x_dot_impl(dt, inputs, states);
}