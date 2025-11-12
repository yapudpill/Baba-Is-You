#include "model/noun.hpp"
#include "model/basic_entity.hpp"
#include "model/entity.hpp"

Noun::Noun(Entity &r): ref{r} {}

Noun Noun::NBABA{BasicEntity::BABA};
Noun Noun::NWALL{BasicEntity::WALL};
Noun Noun::NFLAG{BasicEntity::FLAG};
Noun Noun::NROCK{BasicEntity::ROCK};

// Since all TextEntity share the same rules, we can pick any of them as a
// reference. Here we have chosen NTEXT.
Noun Noun::NTEXT{static_cast<Entity&>(NTEXT)};
