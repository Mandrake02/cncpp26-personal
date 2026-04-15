/*
Common defines file
Author: Andrea Malacarne, 2026
...
*/

#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <optional>

// Semantic versioning
#define CNCPP_VERSION "0.1.0" //Major.Minor.Patch version
                              //Patch version -> mainly bug fixes
                              //Minor version changed when changing some user interface that could break something previous
                              //Major version changed when changing A LOT -> features and user interface

#define CNCPP_NUMBER_WIDTH "9"                              

using data_t = double; //Type for data value -> userful to change if the pc we're using is not strong enough
                       //If we want to change all from double -> float we just need to change this line of code

using opt_data_t = std::optional<data_t>; //We will need it for optional values
using opt_int_t = std::optional<int>;




#endif