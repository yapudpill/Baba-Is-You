#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/ref_entity.hpp"
#include "model/util.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    using cell = std::vector<Entity*>;

    explicit Game(const std::string &path);
    virtual ~Game();
    local_entities operator[](const Property &p) const;
    std::vector<coordinates> operator[](const Entity *entity) const;
    cell &operator[](const coordinates &cds) const;

    Action moveAction(Entity *entity, const coordinates &cds, Direction d) const;
    Action stayAction() const;
    void applyAction(const Action &a);
    void move(Direction d);

    void actualiseRegle();
    RefEntity *getRefEntity(coordinates cds);
    Property *getProperty(coordinates cds);
    void clearAll();

    int getHeight() const { return height; }
    int getWidth() const { return width; }

  private:
    cell **grid;
    int height, width;
    bool inBounds(coordinates cds) const;
};

#endif // GAME_HPP
