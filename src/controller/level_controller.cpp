#include "controller/level_controller.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "controller/util.hpp"

LevelController::LevelController(MainController &mc, sf::RenderWindow &win, const std::string &path):
    SubController{mc, win}, path{path}, game{path}, view{game.getGrid()} {
  onResized(window.getSize().x, window.getSize().y);
}

void LevelController::onKeyPressed(sf::Keyboard::Key code) {
  view.advanceAnimations();
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

    case sf::Keyboard::R:
      game = Game(path);
      break;

    case sf::Keyboard::Q:
      main_controller.loadMenu();
      break;

    default:;
  }

  if (game.isWin()) main_controller.loadMenu();
}
