#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <utility>
#include <vector>

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/util.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    using cell = std::vector<Entity*>;

    explicit Game(const std::string &path);
    ~Game();
    std::vector<std::pair<coordinates, Entity*>> operator[](const Property &p) const;
    cell &operator[](const coordinates &cds) const;

    Action moveAction(Direction d) const;
    void applyAction(const Action &a);
    void move(Direction d);

    int getHeight() const { return height; }
    int getWidth() const { return width; }

  private:
    cell **grid;
    int height, width;
    bool inBounds(coordinates cds) const;
};

#endif // GAME_HPP
