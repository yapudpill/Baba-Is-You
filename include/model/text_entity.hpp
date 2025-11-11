#ifndef TEXT_HPP
#define TEXT_HPP

#include "model/entity.hpp"

/* A text entity is a bloc of text on the grid. For example the blocs for BABA,
WIN, IS... These blocs always have the property PUSH. */
class TextEntity: public Entity {
  protected:
    TextEntity() = default;
};

#endif // TEXT_HPP
