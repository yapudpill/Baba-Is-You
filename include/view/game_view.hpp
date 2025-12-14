#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "model/grid.hpp"

class GameView {
  public:
    GameView(sf::RenderWindow &window, const Grid &game);
    void resize(unsigned win_w, unsigned win_h);
    void draw();

  private:
    sf::RenderWindow &window;
    const Grid &grid;
    const float view_width, view_height;
};

#endif // GAME_VIEW_HPP
