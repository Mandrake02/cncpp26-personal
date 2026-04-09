#pragma once

#include "model.h"

class Spring : public Model {
public:
  Spring(std::string name);
  Spring(std::string name, double k, double m);
  ~Spring();
  
  enum States {
    STATE_X, 
    STATE_V,
    STATES_NUMBER
  };
  enum Inputs {
    INPUTS_NUMBER
  };

protected:
  Vec compute_x_dot_impl(double dt, Vec inputs, Vec states) override;
private:
  double _k;
  double _m;
};