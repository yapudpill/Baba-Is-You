#include "menu/menu_controller.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"

MenuController::MenuController(MainController &mc, sf::RenderWindow &win):
    SubController{mc, win}, view{model} {
  onResized(window.getSize().x, window.getSize().y);
}

void MenuController::onKeyPressed(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Right:
      model.moveSelected(5);
      break;

    case sf::Keyboard::Down:
      model.moveSelected(1);
      break;

    case sf::Keyboard::Left:
      model.moveSelected(-5);
      break;

    case sf::Keyboard::Up:
      model.moveSelected(-1);
      break;

    case sf::Keyboard::Enter:
      main_controller.loadLevel(model.getPath());
      break;

    case sf::Keyboard::Q:
      window.close();
      break;

    default:;
  }
}
