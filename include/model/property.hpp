#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "model/action.hpp"
#include "model/text_entity.hpp"
#include "model/util.hpp"

/* A Property is a TextEntity that defines interaction rules via two functions.
Properties are referenced inside other other entities to define their behavior.
*/
class Property: public TextEntity {
  public:
    static Property &YOU, &STOP, &PUSH, &WIN;

    virtual Action onEnter(const Entity &e, Direction d) const = 0;
    virtual Action onStay(const Entity &e) const = 0;
};

#endif // PROPERTY_HPP
