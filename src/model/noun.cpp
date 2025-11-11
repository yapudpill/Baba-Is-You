#include "model/noun.hpp"
#include "model/basic_entity.hpp"

Noun::Noun(BasicEntity &r): ref{r} {}

Noun Noun::NBABA{BasicEntity::BABA};
Noun Noun::NWALL{BasicEntity::WALL};
Noun Noun::NFLAG{BasicEntity::FLAG};
Noun Noun::NROCK{BasicEntity::ROCK};
