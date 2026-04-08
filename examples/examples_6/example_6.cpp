#include "spring.h"

int main() {

  Spring spring("spring", 100.0, 33.3);

  spring.set_x0({1.0, 0.0});

  double tf = 20.0;
  double dt = 0.01;
  
  for (double t = 0.0; t < tf; t += dt) {
    spring.step(dt, {});
  }
  return 0;
}