#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "model/game.hpp"

class GameView {
  public:
    GameView(sf::RenderWindow &window, const Game &game);
    void resize(unsigned win_w, unsigned win_h);
    void draw();

  private:
    sf::RenderWindow &window;
    const Game &game;
    const float view_width, view_height;
};

#endif // GAME_VIEW_HPP
