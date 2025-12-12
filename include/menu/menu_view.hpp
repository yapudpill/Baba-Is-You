#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include "model/util.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>

class MenuView {
  public:
    MenuView(sf::RenderWindow &win, const std::vector<std::string> &choices);
    void resize(unsigned win_w, unsigned win_h);
    void draw();

    void moveSelection(Direction d);
    int getSelection() const { return selected; }

  private:
    sf::RenderWindow &window;
    const float view_width, view_height;
    const std::vector<std::string> &choices;
    int selected = 0;
};

#endif // MENU_VIEW_HPP
