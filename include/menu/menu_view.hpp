#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "menu/menu_model.hpp"

class MenuView {
  public:
    MenuView(sf::RenderWindow &win, const MenuModel &m);
    void draw();

  private:
    sf::RenderWindow &window;
    const MenuModel &model;
};

#endif // MENU_VIEW_HPP
