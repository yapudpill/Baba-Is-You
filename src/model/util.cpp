#include "model/util.hpp"

coordinates next(coordinates cds, Direction d) {
  switch (d) {
    case Direction::Right: return {cds.first, cds.second + 1};
    case Direction::Left:  return {cds.first, cds.second - 1};
    case Direction::Up:    return {cds.first - 1, cds.second};
    case Direction::Down:  return {cds.first + 1, cds.second};
  }
}

// ca va etre utile pour afficher les enums clairement au lieu de int très peu signifiant
