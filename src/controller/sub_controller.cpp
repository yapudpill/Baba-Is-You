#include "controller/sub_controller.hpp"

SubController::SubController(MainController &mc, sf::RenderWindow &win):
  main_controller{mc}, window{win} {}

void SubController::onResized(unsigned width, unsigned height) {
  window.setView(getView().resize(width, height));
}

void SubController::update() {
  window.draw(getView());
}
