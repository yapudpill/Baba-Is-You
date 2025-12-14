#ifndef MODEL_UTIL_HPP
#define MODEL_UTIL_HPP

#include <utility>
#include <vector>

class Entity;

enum class Direction {Right, Left, Up, Down};

using coordinates = std::pair<unsigned, unsigned>;
coordinates next(coordinates cds, Direction d);

using local_entity = std::pair<coordinates, Entity*>;
using local_entities = std::vector<local_entity>;

#endif // MODEL_UTIL_HPP
