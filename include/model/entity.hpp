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
    void addProperty(const Property &p);
    void delProperty(const Property &p);
    bool hasProperty(const Property &p) const;
    // TODO: add a way to get the list of properties without beeing able to
    //       modify them

  protected:
    Entity() = default;

  private:
    std::set<const Property*> properties;

    Entity(const Entity&) = delete;
    Entity &operator=(const Entity&) = delete;
};

#endif // ENTITY_HPP
