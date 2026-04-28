#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "defines.hpp"
#include "point.hpp"
#include <functional>
#include <string>
#include "machine.hpp"


namespace cncpp {

/**
 * @brief Represents a parsed G-code block and its motion profile.
 *
 * A block stores the original input line, the parsed command metadata,
 * the motion type, and the interpolation profile used to traverse the block.
 */
class Block : public Object{
public:

  /**
   * @brief Motion categories supported by a block.
   */
  enum class BlockType {
    RAPID = 0, ///< G0 rapid move.
    LINE, ///< G1 linear move.
    CWA, ///< G2 clockwise arc.
    CCWA, ///< G3 counter-clockwise arc.
    NO_MOTION
  };

  /**
   * @brief Time and kinematic profile for block execution.
   */
  struct Profile {
    data_t a = 0.0, d = 0.0;
    data_t f = 0.0, l = 0.0;
    data_t fs = 0.0, fe = 0.0;
    data_t dt_1 = 0.0, dt_m = 0.0, dt_2 = 0.0;
    data_t dt = 0.0;
    data_t current_acc; ///< Current acceleration along an arc.

    /**
     * @brief Evaluates the normalized arc-length interpolation function.
     * @param t Current time instant.
     * @param s Output speed along the profile.
     * @return Interpolation parameter associated with @p t.
     */
    data_t lambda(data_t t, data_t &s);
  };
 
  //LIFECYCLE

  /**
   * @brief Builds a block from a raw G-code line.
   * @param line Input G-code line.
   */
  Block(std::string line);

  /**
   * @brief Builds a block from a raw G-code line and its predecessor.
   * @param line Input G-code line.
   * @param prev Previous block used for modal state inheritance.
   */
  Block(std::string line, Block &prev);

  /**
   * @brief Releases the block resources.
   */
  ~Block();

  /**
   * @brief Returns a textual description of the block.
   * @param colored If true, includes terminal coloring.
   * @return Human-readable block description.
   */
  std::string desc(bool colored = true) const override; 

  /**
   * @brief Assigns the content of another block.
   * @param b Source block.
   * @return Reference to this block.
   */
  Block &operator=(Block &b);

  //OPERATION/OPERATORS

  /**
   * @brief Parses the block using the machine state.
   * @param m Machine state used to resolve modal values.
   * @return Reference to this block.
   */
  Block &parse(const Machine *m);

  /**
   * @brief Evaluates the interpolation parameter at a given time.
   * @param time Current time instant.
   * @param speed Output speed at the requested instant.
   * @return Interpolation parameter in the range covered by the block.
   */
  data_t lambda(data_t time, data_t &speed);

  /**
   * @brief Computes the point corresponding to a normalized interpolation value.
   * @param lambda Normalized interpolation parameter.
   * @return Interpolated point on the block path.
   */
  Point interpolate(data_t lambda);

  /**
   * @brief Computes the interpolated point and kinematic state at a given time.
   * @param time Current time instant.
   * @param lambda Output interpolation parameter.
   * @param speed Output speed at the requested instant.
   * @return Interpolated point on the block path.
   */
  Point interpolate(data_t time, data_t &lambda, data_t &speed); 

  /**
   * @brief Iterates the block timeline and invokes a callback for each sample.
   * @param func Callback receiving the block, time, interpolation parameter, and speed.
   */
  void walk(std::function<void(Block &b, data_t t, data_t l, data_t s)> func);

  //ACCESSORS

  /**
   * @brief Returns the original G-code line.
   */
  std::string line() const {return _line;}

  /**
   * @brief Returns the block number.
   */
  size_t n() const {return _n;}

  /**
   * @brief Returns the total block duration.
   */
  data_t dt() const {return _profile.dt;}

  /**
   * @brief Returns the parsed motion type.
   */
  BlockType type() const {return _type;} 

  /**
   * @brief Returns the selected tool number.
   */
  size_t tool() const {return _tool;}

  /**
   * @brief Returns the linear feedrate.
   */
  data_t feedrate() const {return _feedrate;}

  /**
   * @brief Returns the arc feedrate.
   */
  data_t arc_feedrate() const {return _arc_feedrate;}

  /**
   * @brief Returns the spindle speed.
   */
  data_t spindle() const {return _spindle;}

  /**
   * @brief Returns the geometric length of the block.
   */
  data_t length() const {return _length;}

  /**
   * @brief Returns the target point.
   */
  const Point &target() const {return _target;} 

  /**
   * @brief Returns the arc center point.
   */
  const Point &center() const {return _center;} 

  /**
   * @brief Returns the arc delta vector.
   */
  const Point &delta() const {return _delta;} 

  /**
   * @brief Returns the M-code argument, if any.
   */
  size_t m() const {return _m;}

  /**
   * @brief Returns the motion profile.
   */
  const Profile &profile() const {return _profile;}

  /**
   * @brief Indicates whether the block has been parsed.
   */
  bool parsed() const {return _parsed;}

  /**
   * @brief Returns the arc radius parameter.
   */
  data_t r() const { return _r; }
  
  /**
   * @brief Pointer to the previous block in the program.
   */
  Block *prev = nullptr;

  /**
   * @brief Pointer to the next block in the program.
   */
  Block *next = nullptr;

private:
  std::string _line; ///< Original G-code line.
  size_t _n=0; ///< Block number.
  Point _target=Point();
  Point _center=Point();
  Point _delta=Point();
  data_t _length=0;
  data_t _i=0, _j=0, _r=0; ///< Arc parameters.
  data_t _theta_0=0, _dtheta=0; 
  data_t _feedrate=0; ///< Linear feedrate.
  data_t _arc_feedrate=0; ///< Feedrate along the arc.
  data_t _spindle=0; 
  data_t _acc=0; ///< Spindle acceleration rate.
  size_t _m=0; ///< M command argument.
  size_t _tool=0; ///< Current tool number.
  BlockType  _type=BlockType::NO_MOTION; ///< Motion type.
  Profile _profile;
  bool _parsed = false;
  Machine const *_machine = nullptr;

  //UTILITIES
  /**
   * @brief Parses a single token from the input line.
   * @param token Token to parse.
   * @return True if the token was accepted, false otherwise.
   */
  bool parse_token(std::string &token);

  /**
   * @brief Returns the starting point used for interpolation.
   * @return Starting point of the block.
   */
  Point start_point();

  /**
   * @brief Computes the derived block parameters after parsing.
   */
  void compute();

  /**
   * @brief Computes the geometric and kinematic data for an arc block.
   */
  void calc_arc();
};
} //namespace cncpp

#endif