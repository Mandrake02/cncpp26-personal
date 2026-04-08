#pragma once

#include "model.h"

class Spring : public Model {
public:
  Spring(std::string name, double k, double m);
  ~Spring();
protected:
  Vec compute_x_dot_impl(double dt, Vec inputs, Vec states) override;
private:
  double _k;
  double _m;
};