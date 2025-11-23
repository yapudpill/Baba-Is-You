#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class GameController {
  public:
    GameController();
    void run();

  private:
    sf::RenderWindow window;
};

#endif // GAME_CONTROLLER_HPP
