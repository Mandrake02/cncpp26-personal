#include <iostream>

void sqaure(double &number) { // Aggiungendo la refernza abbiamo direttamente
                              // passato l'oggetto intero alla funzione

  // Utile soprattutto per modificare più valori con la stessa funzione

  number = number * number;
}

void scale(double s, double &x, double &y) {
  x = s * x;
  y = s * y;
}

void break_code();

std::string *get_age();
std::string &get_name();

int main() {

  double age = 23;
  double &reference_age = age; // Aggiungo & per renderla una reference, in
                               // questo caso di tipo intero

  std::cout << age << " " << reference_age << std::endl;

  reference_age = 22; // In questo modo andiamo a modificare non solo la
                      // reference ma anche l'oggetto iniziale

  std::cout << age << " " << reference_age << std::endl;

  sqaure(age);

  std::cout << "Age after square: " << age << std::endl;

  double x = 10.0, y = 10.0;

  scale(2, x, y);

  std::cout << "x: " << x << " y: " << y << std::endl;

  //====| PUNTATORI |=====//

  double second_age = 35;
  reference_age = second_age;
  std::cout << "age: " << reference_age << std::endl;
  reference_age = 22;
  std::cout << "age: " << reference_age << " second age: " << second_age
            << std::endl;

  double *pointer_age;
  pointer_age = &age;
  std::cout << pointer_age << "==" << &age << std::endl;
  std::cout << pointer_age << " age: " << *pointer_age << std::endl;
  *pointer_age = 18;
  std::cout << *pointer_age << " age: " << age << std::endl;

  pointer_age = &second_age;
  std::cout << *pointer_age << " age: " << age << std::endl;

  break_code();
  return 0;
}

std::string *get_age() {
  std::string age;
  return &age;
}

std::string &get_name() {
  std::string name = "Pippo";
  return name;
}

void break_code() {
  double *x_ptr = nullptr;
  if (x_ptr) {
    std::cout << x_ptr << std::endl;
    std::cout << *x_ptr << std::endl;
  }
  std::cout << "-----" << std::endl;

  //This will crash
  std::string *age_ptr = get_age();
  std::cout << age_ptr << std::endl;
  if (age_ptr) {
    std::cout << "age from get_age: " << *age_ptr << std::endl;
    *age_ptr = "AA";
  }

  //This will crash
  std::cout << get_name() << std::endl;
  std::string &name = get_name();
  name = "ploto";
  std::cout << name << std::endl;
}