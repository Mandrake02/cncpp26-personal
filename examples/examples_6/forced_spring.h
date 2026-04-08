#pragma once

#include "model.h"

class ForcedSpring : public Model {
public:
  ForcedSpring(std::string name, double k, double m);

  enum States {
    STATE_X, 
    STATE_V,
    STATES_NUMBER
  };
  enum Inputs {
    INPUT_F,
    INPUTS_NUMBER
  };

protected:
  Vec compute_x_dot_impl(double dt, Vec inputs, Vec states) override;

private:
  double _k;
  double _m;
};