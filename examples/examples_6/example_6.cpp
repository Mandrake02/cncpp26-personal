#include "spring.h"
#include "forced_spring.h"
#include <cmath>
#include <iostream>
#include <fmt/format.h>
#include <rang.hpp>

int main() {

  std::cout << fmt::format("CUSTOM SIMULINK") <<std::endl;
  std::cout << fmt::format("{:^40}", "CUSTOM SIMULINK") <<std::endl;
  std::cout << fmt::format("{:^40}", "v1.0") <<std::endl;
  std::cout << rang::bg::green << fmt::format("{:^40}", "Starting simulation") << rang::bg::reset << std::endl;

  Spring spring("spring", 100.0, 3.0);
  ForcedSpring fspring_1("constant_force", 100.0, 3.0);
  ForcedSpring fspring_2("sinusoidal_force", 100.0, 3.0);
  try {
    spring.load_config("./examples/examples_6/configs/");
  } 
  catch(std::exception &e) {
    std::cout << rang::fg::red << e.what() << rang::fg::reset << std::endl;
  }

  fspring_1.load_config("./examples/examples_6/configs/");
  fspring_2.load_config("./examples/examples_6/configs/"); 

  spring.start_log("./examples/examples_6/out/");
  fspring_1.start_log("./examples/examples_6/out/");
  fspring_2.start_log("./examples/examples_6/out/");

  spring.set_x0({1.0, 0.0});
  fspring_1.set_x0({0.0, 0.0});
  fspring_2.set_x0({0.0, 0.0});

  double tf = 20.0;
  double dt = 0.01;
  
  for (double t = 0.0; t < tf; t += dt) {
    spring.step(dt, {});
    fspring_1.step(dt, {1.0});
    fspring_2.step(dt, {1.0 + std::sin(t * 2 + M_PI * 10.0)});

    //spring.csv_row(std::cout);
  }
  return 0;
}