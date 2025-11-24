#include "controller/level_controller.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <string>

#include "model/basic_entity.hpp"
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

LevelController::LevelController(sf::RenderWindow &window, std::string path):
  window{window}, game{path}, view{window, game} {
  BasicEntity::BABA.addProp(Property::YOU);
}

void LevelController::onResized() {
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
}
