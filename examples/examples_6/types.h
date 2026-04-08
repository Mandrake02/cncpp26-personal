#pragma once

#include <vector>
#include <memory>

using Vec = std::vector<double>;

// std::shared_ptr<double>
template <typename T>
using s_ptr = std::shared_ptr<T>;

// s_ptt<double>