#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <set>

class Property;

/* Everything on the grid is an entity. Entities have propreties that define how
they interact with other entites. Note that propreties themselves are entities
on the grid.

Entities cannot be created or copied and must be used through static variables
provided by subclasses. */
class Entity {
  public:
    virtual bool hasProp(const Property &p) const = 0;
    virtual void addProp(const Property &p) = 0;
    virtual void clearProp() = 0;
    virtual const std::set<const Property*> getProp() const = 0;
};

#endif // ENTITY_HPP
