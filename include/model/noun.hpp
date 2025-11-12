#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "model/entity.hpp"
#include "model/text_entity.hpp"

/* A Noun is a TextEntity that refers to a BasicEntity, compining it with
Operators and Propreties creates rules. */
class Noun: public TextEntity {
  public:
    static Noun NBABA, NWALL, NFLAG, NROCK, NTEXT;

  private:
    Entity &ref;
    Noun(Entity &r);
};

#endif // OBJECT_HPP
