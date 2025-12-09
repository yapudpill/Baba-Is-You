#include "controller/level_controller.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <string>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "model/property.hpp"
#include "model/util.hpp"

Direction getDirection(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Up: return Direction::Up;
    case sf::Keyboard::Down: return Direction::Down;
    case sf::Keyboard::Left: return  Direction::Left;
    case sf::Keyboard::Right: return Direction::Right;
    default: throw std::invalid_argument("getDirection");
  }
}

LevelController::LevelController(MainController &mc, sf::RenderWindow &win, std::string path):
  SubController{mc, win}, game{path}, view{window, game} {}

void LevelController::onResized(unsigned width, unsigned height) {
  view.resize(width, height);
  view.draw();
}

void LevelController::onKeyPressed(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
      game.move(getDirection(code));
      view.draw();
      break;

    default:;
  }

  if (game.win) main_controller.loadMenu();
}
