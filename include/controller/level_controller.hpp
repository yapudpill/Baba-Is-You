#ifndef LEVEL_CONTROLLER_HPP
#define LEVEL_CONTROLLER_HPP

#include "controller/sub_controller.hpp"
#include "model/game.hpp"
#include "view/game_view.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class LevelController: public SubController {
  public:
    LevelController(sf::RenderWindow &window, std::string path);
    void onResized() override;
    void onKeyPressed(sf::Keyboard::Key code) override;

  private:
    sf::RenderWindow &window;
    Game game;
    GameView view;
};

#endif // LEVEL_CONTROLLER_HPP
