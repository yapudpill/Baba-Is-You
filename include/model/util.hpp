#ifndef UTIL_HPP
#define UTIL_HPP

#include <utility>

enum class Direction {Right, Left, Up, Down};

using coordinates = std::pair<int, int>;

coordinates next(coordinates cds, Direction d);

#endif // UTIL_HPP
