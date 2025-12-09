#include "controller/sub_controller.hpp"

SubController::SubController(MainController &mc, sf::RenderWindow &win):
  main_controller{mc}, window{win} {}
