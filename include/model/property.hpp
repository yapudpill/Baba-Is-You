#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "model/action.hpp"
#include "model/text_entity.hpp"
#include "model/util.hpp"

class Game;

/* A Property is a TextEntity that defines interaction rules via two functions.
Properties are referenced inside other other entities to define their behavior.
*/
class Property: public TextEntity {
  public:
    static Property &YOU, &STOP, &PUSH, &WIN, &DEFEAT, &MOVE;

    // The 'moving' block is entering of the 'receiver' block which is located
    // at 'cds'
    virtual Action onEnter(
      Block &moving,
      Block &receiver,
      const coordinates &cds,
      Game &game) const = 0;
    virtual Action onStay(
      Block &staying,
      Block &receiver,
      const coordinates &cds,
      Game &game) const = 0;
};

#endif // PROPERTY_HPP
