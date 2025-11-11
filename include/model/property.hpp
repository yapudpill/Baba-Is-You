#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "model/text_entity.hpp"

/* A Property is a TextEntity that defines interaction rules via two functions.
Properties are referenced inside other other entities to define their behavior.
*/
class Property: public TextEntity {
  public:
    static Property &YOU, &STOP, &PUSH, &WIN;

    virtual bool onEnter(const Entity &e) = 0;
    virtual bool onStay(const Entity &e) = 0;

  private:
    class EmptyProp;
    class Stop;
    class Push;
    class Win;
    static EmptyProp hidden_you;
    static Stop hidden_stop;
    static Push hidden_push;
    static Win hidden_win;
};

#endif // PROPERTY_HPP
