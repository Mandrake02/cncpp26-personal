#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "defines.hpp"
#include "point.hpp"
#include <functional>
#include <string>


namespace cncpp {

class Machine{
  public:
  Point zero() const {Point(0,0,0);}
  data_t tq() const {return 0.001;}
  data_t A() const {return 1000;}
};

class Block : public Object{
public:

  enum class BlockType {
    RAPID=0, // G0
    LINE, // G1
    CWA, // G2
    CCWA, // G3
    NO_MOTION
  };

  struct Profile {
    data_t a, d;
    data_t f, l;
    data_t fs, fe;
    data_t dt_1, dt_m, dt_2;
    data_t dt;
    data_t current_acc; //along an arc
    data_t lambda(data_t t, data_t &s);
  };
 
  //LIFECYCLE

  Block(std::string line);
  Block(std::string line, Block &prev);
  ~Block();

  std::string desc(bool colored = true);
  Block &operator=(Block &b);

  //OPERATION/OPERATORS

  Block &parse(const Machine *m);
  data_t lambda(data_t time, data_t &speed);
  Point interpolate(data_t lambda);
  Point interpolate(data_t time, data_t &lambda, data_t &speed); 
  void walk(std::function<void(Block &b, data_t t, data_t l, data_t s)> func);

  //ACCESSORS

  std::string line() const {return _line;}
  size_t n() const {return _n;}
  data_t dt() const {return _profile.dt;}
  BlockType type() const {return _type;} 
  size_t tool() const {return _tool;}
  data_t feedrate() const {return _feedrate;}
  data_t arc_feedrate() const {return _arc_feedrate;}
  data_t spindle() const {return _spindle;}
  data_t length() const {return _length;}
  const Point &target() const {return _target;} 
  const Point &center() const {return _center;} 
  const Point &delta() const {return _delta;} 
  size_t m() const {return _m;}
  const Profile &profile() const {return _profile;}
  bool parsed() const {return _parsed;}
  
  Block *prev = nullptr;
  Block *next = nullptr;

private:
  std::string _line; //original G-Code line
  size_t _n=0; //block numer
  Point _target=Point();
  Point _center=Point();
  Point _delta=Point();
  data_t _length=0;
  data_t _i=0, _j=0, _r=0; //arc parameter
  data_t _theta_0=0, _dtheta=0; 
  data_t _feedrate=0; //feedrate
  data_t _arc_feedrate=0; //feedrate along the rate
  data_t _spindle=0; 
  data_t _acc=0; //spindle rate
  size_t _m=0; //M command argument
  size_t _tool=0; //Current tool machine
  BlockType  _type=BlockType::NO_MOTION; //type of motion
  Profile _profile;
  bool _parsed = false;
  Machine const *_machine = nullptr;

  //UTILITIES
  bool parse_token(std::string &token);
  Point start_point();
  void compute();
  void calc_arc();
};
}//namespace ncpp

#endif