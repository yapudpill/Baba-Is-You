#include "controller/game_controller.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <string>

#include "controller/level_controller.hpp"

GameController::GameController() {
  sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
  window.create({desktop_mode.width / 2, desktop_mode.height / 2}, "Baba is you");
}

void GameController::run() {
  while (window.isOpen()) {
    // Créer un menu
    std::string path = "resource/level/level1"; // menu.run();

    // Créer le niveau renvoyé par le menu
    if (!window.isOpen()) return;
    LevelController lvl{window, path};
    lvl.run();
  }
}
