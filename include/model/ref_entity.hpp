#ifndef REF_ENTITY_HPP
#define REF_ENTITY_HPP

#include "model/entity.hpp"
#include "model/text_entity.hpp"

/* A RefEntity is a TextEntity that refers to a BasicEntity, compining it with
Operators and Propreties creates rules. */
class RefEntity: public TextEntity {
  public:
    static RefEntity NBABA, NWALL, NFLAG, NROCK, NTEXT, NGRASS, NTILE, NKEKE, NKEY, NDOOR;
    Entity &ref;

  private:
    RefEntity(Entity &r);
};

#endif // REF_ENTITY_HPP
