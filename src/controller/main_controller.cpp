#include "controller/main_controller.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>

#include "controller/level_controller.hpp"
#include "controller/menu_controller.hpp"

MainController::MainController() {
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  mode.height = 2 * mode.height / 3;
  mode.width = 2 * mode.width / 3;
  window.create(mode, "Baba is you");

  loadMenu();
}

MainController::~MainController() {
  delete subController;
}

void MainController::run() {
  sf::Event event;
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::Resized:
          subController->onResized(event.size.width, event.size.height);
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::F:
              // TODO: toggle fullscreen
              break;
            default:
              subController->onKeyPressed(event.key.code);
          }
          break;

        default:;
      }
    }
  }
}

void MainController::loadMenu() {
  delete subController;
  subController = new MenuController{*this, window};
}

void MainController::loadLevel(std::string path) {
  delete subController;
  subController = new LevelController{*this, window, path};
}
