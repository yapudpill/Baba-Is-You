#include "model/entity.hpp"

void Entity::addProperty(const Property &p) {
  properties.insert(&p);
}

void Entity::delProperty(const Property &p) {
  properties.erase(&p);
}

bool Entity::hasProperty(const Property &p) const {
  return properties.find(&p) != properties.end();
}
