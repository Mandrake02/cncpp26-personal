#include <iostream>
#include <string>

// Per compilare: cmake --build build
// Per eseguire: ./build/examples/example_1

bool check_age(int);
std::string age_type(int);

int main() {

  int a = 10;
  float b = 20.1f;
  double c = 20.2;
  char character = 'c';

  int my_age = 10;

  if (my_age > 18)
  {
    character = 'm';
  }
  else
  {
    character = ' ';
  }
  std::cout << "caracter:" << my_age << std::endl;

  // //Per stampare più righe, usare il comando particolare: \n
  // //Per stampare uno spazio grande (Tab): \t
  // //Per commenti da più righe /* */
  // std::string line_of_text = "Content of the line. \nContent of the second
  // line \n\t- Item 1" ; std::cout << line_of_text << std::endl;

  if (check_age(my_age)) {
    std::cout << "adult" << std::endl;
  } else {
    std::cout << "Not adult" << std::endl;
  }

  std::cout << age_type(my_age) << std::endl;

  return 0;
}

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