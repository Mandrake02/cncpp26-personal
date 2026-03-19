#include <iostream>
#include <string>

class Point {
private:
  double x = 0.0;
  double y{0.0};
  std::string name;

public:
  Point() {
    x = 0;
    y = 0;
    name = "Default";
  }
  Point(double x, double y, std::string name) {
    this->x = x;
    this->y = y;
    this->name = name;
  }
  double return_x_pos() { return this->x; }
  double return_y_pos() { return this->y; }
  std::string return_name() { return this->name; }
  void print_point() {
    std::cout << "x:" << this->return_x_pos() << " y:" << this->return_y_pos()
              << " name: " << this->return_name() << std::endl;
  }
  ~Point() {}
};

int main() {
  Point p1;
  Point p2(2, 3, "Giorgio");
  // std::cout << "p1 x:" << p1.return_x_pos() << " y:" << p1.return_y_pos() <<
  // " name: " << p1.return_name() << std::endl; std::cout << "p2 x:" <<
  // p2.return_x_pos() << " y:" << p2.return_y_pos() << " name: " <<
  // p2.return_name() << std::endl;
  p1.print_point();
  p2.print_point();
  return 0;
}