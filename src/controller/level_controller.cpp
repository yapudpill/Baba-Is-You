#include "controller/level_controller.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "controller/util.hpp"
#include "model/property.hpp"

LevelController::LevelController(MainController &mc, sf::RenderWindow &win, const std::string &path):
    SubController{mc, win}, game{path}, view{game.getGrid()} {
  onResized(window.getSize().x, window.getSize().y);
}

void LevelController::onKeyPressed(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
      game.move(getDirection(code));
      break;

    case sf::Keyboard::Z:
      game.undo();
      break;

    case sf::Keyboard::Y:
      game.redo();
      break;

    default:;
  }

  if (game.win) main_controller.loadMenu();
}
