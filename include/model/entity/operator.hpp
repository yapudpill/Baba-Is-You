#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "model/entity/text_entity.hpp"

/* An Operator is a TextEntity like IS, AND, HAS... */
class Operator: public TextEntity {
  public:
    static Operator IS;

  private:
    Operator() = default;
};

#endif // OPERATOR_HPP
