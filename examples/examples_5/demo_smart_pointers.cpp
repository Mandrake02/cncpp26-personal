#include "demo_smart_pointers.h"
#include <iostream>
#include <string>
#include <memory>

std::string *get_age() {
  std::string age = "18";
  return &age;
}

void demo_smart_pointers() {
  // int a;
  // int a;
  {
    int a = 1;
    std::cout << a << std::endl;
  }
  {
    int a;
    std::cout << a << std::endl;
  }
  // std::cout << a << std::endl;
  double *d_ptr;
  {
    double d = 3.14;
    d_ptr = &d;
  }
  double d = 10;
  std::cout << *d_ptr << " " << d << std::endl;
 
  //Heap allocation
  {
    d_ptr = new double;
  }
  std::cout << d_ptr << " " << *d_ptr << std::endl;
  *d_ptr = 100;
  std::cout << d_ptr << " " << *d_ptr << std::endl;
  delete d_ptr;
  {
    Tracker tracker("tracker_1");
  }
  {
    Tracker* tracker = new Tracker("tracker");
  }
  
  std::unique_ptr<Tracker> parent_ptr;
  {
    std::unique_ptr<Tracker> u_ptr = std::make_unique<Tracker>("unique_ptr");
    Tracker *raw_ptr = u_ptr.get();
    //parent_ptr = u_ptr; //NOT ALLOWED; UNIQUE PTR MUST BE UNIQUE
    parent_ptr = std::move(u_ptr);
    std::cout << ">scope exit" << std::endl;
  }
  
  std::shared_ptr<Tracker> shared_ptr;
  {
    std::shared_ptr<Tracker> s_ptr = std::make_shared<Tracker>("SHARED_PTR");
    shared_ptr = s_ptr;
    std::cout << "- scope exit" << std::endl;
  }

  std::cout << ">demo smart_pointer_scope_exit" <<std::endl;

}

Tracker::Tracker(std::string name) {
  this->_name = name;
  std::cout << "constructed " << _name <<std::endl;
}

Tracker::~Tracker() {
  std::cout << "destructed " << _name << std::endl;
}
