#ifndef MODEL_UTIL_HPP
#define MODEL_UTIL_HPP

#include <utility>
#include <vector>

class Entity;

enum class Direction {Right, Left, Up, Down};

using coordinates = std::pair<int, int>;
coordinates next(coordinates cds, Direction d);

using local_entities = std::vector<std::pair<coordinates, Entity*>>;

#endif // MODEL_UTIL_HPP
