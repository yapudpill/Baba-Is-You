#ifndef LEVEL_CONTROLLER_HPP
#define LEVEL_CONTROLLER_HPP

#include "model/game.hpp"
#include "view/game_view.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class LevelController {
  public:
    LevelController(sf::RenderWindow &window, std::string path);
    void run();

  private:
    sf::RenderWindow &window;
    Game game;
    GameView view;
};

#endif // LEVEL_CONTROLLER_HPP
