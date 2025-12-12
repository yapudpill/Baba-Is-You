#include "controller/util.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>

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
