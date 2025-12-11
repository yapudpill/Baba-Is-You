#include "controller/main_controller.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>

#include "controller/level_controller.hpp"
#include "controller/menu_controller.hpp"

MainController::MainController() {
  setFullscreen(false);
  loadLevel("resource/level/leveltest");
}

MainController::~MainController() {
  delete subController;
}

void MainController::run() {
  sf::Event event;
  while (window.isOpen()) {
    while (window.waitEvent(event)) {
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
              setFullscreen(!fullscreen);
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

void MainController::setFullscreen(bool fs) {
  static const std::string title{"Baba is You"};
  sf::VideoMode mode;
  sf::Uint32 style;
  if (fs) {
    mode = sf::VideoMode::getFullscreenModes()[0];
    style = sf::Style::Fullscreen;
  } else {
    mode = sf::VideoMode::getDesktopMode();
    mode.height = 2 * mode.height / 3;
    mode.width = 2 * mode.width / 3;
    style = sf::Style::Default;
  }
  window.create(mode, title, style);
  fullscreen = fs;
}
