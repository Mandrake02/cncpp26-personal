#ifndef DEMO_SMART_POINTERS_H
#define DEMO_SMART_POINTERS_H
#include <iostream>
#include <string>

std::string *get_age();
void demo_smart_pointers();

class Tracker{
  public:
  std::string _name;
  Tracker(std::string name);
  ~Tracker();

};

#endif