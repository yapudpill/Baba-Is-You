#include "menu/menu_controller.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "controller/util.hpp"

MenuController::MenuController(MainController &mc, sf::RenderWindow &win):
    SubController{mc, win}, view{window, model.getNames()} {
  view.draw();
}

void MenuController::onResized(unsigned width, unsigned height) {
  view.resize(width, height),
  view.draw();
}

void MenuController::onKeyPressed(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
    case sf::Keyboard::Left:
    case sf::Keyboard::Down:
      view.moveSelection(getDirection(code));
      view.draw();
      break;

    case sf::Keyboard::Enter:
      main_controller.loadLevel(model.getPath(view.getSelection()));
      break;

    default:;
  }
}
