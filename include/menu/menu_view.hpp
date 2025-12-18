#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include "menu/menu_model.hpp"
#include "view/view.hpp"

class MenuView: public View {
  public:
    MenuView(const MenuModel &m);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:
    int radius;
    unsigned char_size;
    float line_height, menu_height;
    const MenuModel &model;
    void drawChoices(sf::RenderTarget &target) const;
};

#endif // MENU_VIEW_HPP
