#include "spring.h"
#include "forced_spring.h"
#include <cmath>
#include <iostream>
#include <fmt/format.h>
#include <rang.hpp>

void test_optional() {
  bool set_x = true;
  bool set_y = true; 

  std::optional<double> new_x;
  std::optional<double> new_y;

  double new_x_d;
  double new_y_d;

  double machine_x = 10.0;
  double machine_y = 3.0;

  if(new_x) {
    machine_x = new_x.value();
  }
  if(new_y) {
    machine_y = new_y.value();
  }

  // OR

  if(set_x) {
    machine_x =  new_x_d;
  }
  if(set_y) {
    machine_y = new_y_d;
  }

  //LESS VARIABLES WITH THE OPTIONAL!!!
}

int main(int argc, char* argv[]) {

  std::cout << argc;
  for (size_t i = 0; i < argc; i++) {
    std::cout << ", " << argv[i];
  }
  std::cout << std::endl;

  std::cout << fmt::format("CUSTOM SIMULINK") <<std::endl;
  std::cout << fmt::format("{:^40}", "CUSTOM SIMULINK") <<std::endl;
  std::cout << fmt::format("{:^40}", "v1.0") <<std::endl;
  std::cout << rang::bg::green << fmt::format("{:^40}", "Starting simulation") << rang::bg::reset << std::endl;

  std::string out_folder = "./examples/examples_6/out/";
  std::string config_folder = "./examples/examples_6/configs/";

  if(argc > 1) {
    out_folder = argv[1];
  }
  if(argc > 2) {
    config_folder = argv[2];
  }

  Vec vec(10.0, 10.0);
  vec.front();
  vec.back();
  vec.size();
  vec.empty();

  Vec vec2 = {
    0, 
    10, 
    2, 
    6, 
    20
  };
  std::sort(vec2.begin(), vec2.end());
  
  struct Point {
    double x;
    double y;
  };
  std::vector<Point> points;
  // std::sort(points.begin(), points.end()); DOESN'T WORK
  std::sort(points.begin(), points.end(), [](Point a, Point b) -> bool {return a.x < b.x;});
  std::sort(points.begin(), points.end(), [](Point a, Point b) -> bool {return std::hypot(a.x, a.y) < std::hypot(b.x, b.y);});
  Point p0 = {10, 10};
  std::sort(points.begin(), points.end(), [p0](Point a, Point b) -> bool {return std::hypot(a.x-p0.x, a.y-p0.y) < std::hypot(b.x-p0.x, b.y-p0.y);});
  Point p1 = {11, 10};
  std::sort(points.begin(), points.end(), [&](Point a, Point b) -> bool {return std::hypot(a.x-p0.x-p1.x, a.y-p0.y-p1.y) < std::hypot(b.x-p0.x-p1.x, b.y-p0.y-p1.y);});

  Spring spring("spring");
  ForcedSpring fspring_1("constant_force", 100.0, 3.0);
  ForcedSpring fspring_2("sinusoidal_force", 100.0, 3.0);
  try {
    spring.load_config(config_folder);
  } 
  catch(std::exception &e) {
    std::cout << rang::fg::red << e.what() << rang::fg::reset << std::endl;
  }

  //fspring_1.load_config(config_folder);
  //fspring_2.load_config(config_folder); 

  spring.start_log(out_folder);
  fspring_1.start_log(out_folder);
  fspring_2.start_log(out_folder);

  spring.set_x0({1.0, 0.0});
  fspring_1.set_x0({0.0, 0.0});
  fspring_2.set_x0({0.0, 0.0});

  double tf = 20.0;
  double dt = 0.01;
  
  for (double t = 0.0; t < tf; t += dt) {
    spring.step(dt, {});
    fspring_1.step(dt, {1.0});
    fspring_2.step(dt, {1.0 + std::sin(t * 2 + M_PI * 10.0)});

    //  fspring_2.step(dt, {1.0 + std::sin(t * 2 + M_PI * 10.0)}, [](double dt, Vec states, Vec x_dot) {
    //    for(size_t i = 0; i < states.size(); i++) {
    //      ...
    //    }
    //  });

    //spring.csv_row(std::cout);
  }
  return 0;
}