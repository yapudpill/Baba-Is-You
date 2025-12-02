#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "model/game.hpp"

class GameView {
  public:
    GameView(sf::RenderWindow &window, const Game &game);
    void resize(unsigned width, unsigned height);
    void draw();

  private:
    sf::RenderWindow &window;
    const Game &game;
};

#endif // GAME_VIEW_HPP
