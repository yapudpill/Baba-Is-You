#include "model/entity/text_entity.hpp"

#include "model/entity/property.hpp"

#include <set>

std::set<const Property*> TextEntity::properties;

bool TextEntity::hasProp(const Property &p) const {
  return properties.find(&p) != properties.end();
}

void TextEntity::addProp(const Property &p) {
  properties.insert(&p);
}

void TextEntity::clearProp() {
  properties.clear();
  properties.insert(&Property::PUSH);
}

const std::set<const Property*> TextEntity::getProp() const {
  return properties;
}
