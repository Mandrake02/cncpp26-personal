#include <iostream>
#include <string>

// Per compilare: cmake --build build
// Per eseguire: ./build/examples/example_1

bool check_age(int age) {
  if (age > 18) {
    return true;
  } else {
    return false;
  }
}

std::string age_type(int age) {
  if (age >= 18) {
    return "adult";
  } else {
    return "Not adult";
  }
}

float sum(float a, float b); // Stiamo dichiarando una funzione per poi
                             // definirla dopo la funzione main
double sum(double a, double b);

template <typename T> T templated_sum(T a, T b);

int main() {

  int a = 10;
  float b = 20.1f;
  double c = 20.2;
  char character = 'c';

  int my_age = 10;

  // if (my_age > 18)
  // {
  //   character = 'm';
  // }
  // else
  // {
  //   character = 'B';
  // }
  // std::cout << "caracter:" << my_age << std::endl;

  // //Per stampare più righe, usare il comando particolare: \n
  // //Per stampare uno spazio grande (Tab): \t
  // //Per commenti da più righe /* */
  // std::string line_of_text = "Content of the line. \nContent of the second
  // line \n\t- Item 1" ; std::cout << line_of_text << std::endl;

  // if (check_age(my_age))
  // {
  //   std::cout << "adult" << std::endl;
  // }else{
  //   std::cout << "Not adult" << std::endl;
  // }

  // std::cout << age_type(my_age) << std::endl;

  float x1 = 1.0;
  float x2 = 2.0;
  float x3 = sum(x1, x2);

  double y1 = 1.0;
  double y2 = 2.0;
  double y3 =
      sum(y1, y2); // Because we have 2 different functions it will
                   // automatically use the best one in terms of the type used

  x3 = templated_sum(x1, x2);
  y3 = templated_sum(y1, y2);
  templated_sum<int>(0, 1);

  return 0;
}

float sum(float a, float b) {
  std::cout << "float sum" << std::endl;
  return a + b;
}

double sum(double a, double b) {
  std::cout << "double sum" << std::endl;
  return a + b;
}

template <typename T> T templated_sum(T a, T b) { return a + b; }

template <> int templated_sum(int a, int b) {
  std::cout << "float sum" << std::endl;
  return a + b;
}