#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "model/basic_entity.hpp"
#include "model/text_entity.hpp"

/* A Noun is a TextEntity that refers to a BasicEntity, compining it with
Operators and Propreties creates rules. */
class Noun: public TextEntity {
  public:
    static Noun NBABA, NWALL, NFLAG, NROCK;

  protected:
    Noun(BasicEntity &r);

  private:
    BasicEntity &ref;
};

#endif // OBJECT_HPP
