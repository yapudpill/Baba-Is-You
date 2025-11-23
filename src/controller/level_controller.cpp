#include "controller/level_controller.hpp"
#include "model/basic_entity.hpp"
#include "model/property.hpp"
#include "model/util.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <string>

bool isDirection(sf::Keyboard::Key key) {
  return key == sf::Keyboard::Up
    || key == sf::Keyboard::Down
    || key == sf::Keyboard::Left
    || key == sf::Keyboard::Right;
}

Direction getDirection(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Up:
      return Direction::Up;
    case sf::Keyboard::Down:
      return Direction::Down;
    case sf::Keyboard::Left:
      return  Direction::Left;
    case sf::Keyboard::Right:
      return Direction::Right;
    default: throw std::invalid_argument("getDirection");
  }
}

LevelController::LevelController(sf::RenderWindow &window, std::string path):
  window{window}, game{path}, view{window, game} {
  BasicEntity::BABA.addProp(Property::YOU);
}


void LevelController::run() {
  while (window.isOpen()) {

    // gérer les évènements
    sf::Event event;
    sf::FloatRect rect;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          return;

        case sf::Event::Resized:
          rect.width = event.size.width;
          rect.height = event.size.height;
          window.setView(sf::View{rect});

        case sf::Event::KeyPressed:
          if (isDirection(event.key.code)) {
            game.move(getDirection(event.key.code));
          }
          break;

        default:;
      }
    }

    // actualiser la vue
    view.draw();
  }
}
