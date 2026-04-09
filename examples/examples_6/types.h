#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

using Vec = std::vector<double>;

// std::shared_ptr<double>
template <typename T>
using s_ptr = std::shared_ptr<T>;

// s_ptt<double>

using Str2Dbl = std::map<std::string, double>;