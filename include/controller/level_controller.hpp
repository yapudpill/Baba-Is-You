#ifndef LEVEL_CONTROLLER_HPP
#define LEVEL_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "model/game.hpp"
#include "view/game_view.hpp"
#include "view/view.hpp"

class LevelController: public SubController {
  public:
    LevelController(MainController &mc, sf::RenderWindow &win, const std::string &path);
    void onKeyPressed(sf::Keyboard::Key code) override;

  protected:
    View &getView() override { return view; }

  private:
    std::string path;
    Game game;
    GameView view;
};

#endif // LEVEL_CONTROLLER_HPP
