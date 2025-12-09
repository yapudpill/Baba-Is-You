#include "controller/menu_controller.hpp"

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include <SFML/Window/Keyboard.hpp>

MenuController::MenuController(MainController &mc, sf::RenderWindow &win):
    SubController{mc, win}, view{window, model} {}

void MenuController::onResized(unsigned width, unsigned height) {
  view.draw();
}

void MenuController::onKeyPressed(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
      model.move(-1);
      view.draw();
      break;

    case sf::Keyboard::Left:
    case sf::Keyboard::Down:
      model.move(1);
      view.draw();
      break;

    case sf::Keyboard::Enter:
      main_controller.loadLevel(model.get());

    default:;
  }
}
