#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <map>

#include "model/entity.hpp"
#include "model/grid.hpp"
#include "view/animation.hpp"

class GameView final {
  public:
    GameView(sf::RenderWindow &window, const Grid &game);
    ~GameView();
    void resize(unsigned win_w, unsigned win_h);
    void draw();
    void advanceAnimations();

  private:
    sf::RenderWindow &window;
    const Grid &grid;
    const float view_width, view_height;
    const std::map<const Entity*, Animation*> sprites;
};

#endif // GAME_VIEW_HPP
