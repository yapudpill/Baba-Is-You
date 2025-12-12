#include "model/ref_entity.hpp"

#include "model/basic_entity.hpp"
#include "model/entity.hpp"

RefEntity::RefEntity(Entity &r): ref{r} {}

RefEntity RefEntity::NBABA{BasicEntity::BABA};
RefEntity RefEntity::NWALL{BasicEntity::WALL};
RefEntity RefEntity::NFLAG{BasicEntity::FLAG};
RefEntity RefEntity::NROCK{BasicEntity::ROCK};
RefEntity RefEntity::NGRASS{BasicEntity::GRASS};
RefEntity RefEntity::NTILE{BasicEntity::TILE};

// Since all TextEntity share the same rules, we can pick any of them as a
// reference. Here we have chosen NTEXT.
RefEntity RefEntity::NTEXT{static_cast<Entity&>(NTEXT)};
