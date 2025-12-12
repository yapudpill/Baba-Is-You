#ifndef MENU_CONTROLLER_HPP
#define MENU_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "controller/main_controller.hpp"
#include "controller/sub_controller.hpp"
#include "menu/menu_model.hpp"
#include "menu/menu_view.hpp"

class MenuController: public SubController {
  public:
    MenuController(MainController &mc, sf::RenderWindow &win);

    void onResized(unsigned width, unsigned height) override;
    void onKeyPressed(sf::Keyboard::Key code) override;

  private:
    MenuModel model;
    MenuView view;
};

#endif // MENU_CONTROLLER_HPP
