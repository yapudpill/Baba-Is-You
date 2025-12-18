#include "menu/menu_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>

#include "menu/menu_model.hpp"

sf::Texture loadTexture(std::string path) {
  sf::Texture t;
  if (!t.loadFromFile(path))
    throw std::runtime_error("Cannot open texture " + path);
  return t;
}

sf::Font loadFont(std::string path) {
  sf::Font f;
  if (!f.loadFromFile(path))
    throw std::runtime_error("Cannot open font " + path);
  return f;
}

const sf::Texture logo_texture = loadTexture("resource/image/logo.png");
const sf::Vector2u logo_size{logo_texture.getSize()};
const sf::Sprite logo{logo_texture};
const sf::Font font = loadFont("resource/fonts/NotoSans-Regular.ttf");

// TODO: find how to define view_width and view_height properly
MenuView::MenuView(const MenuModel &m): radius{2}, char_size{60},
    line_height{1.5f * char_size}, menu_height{(2 * radius + 1) * line_height},
    model{m} {
  width = logo_size.x;
  height = logo_size.y + menu_height;
}

void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(logo);

  sf::RenderTexture texture;
  texture.create(width, menu_height);
  drawChoices(texture);
  texture.display();

  sf::Sprite choices{texture.getTexture()};
  choices.move(0, logo_size.y);
  target.draw(choices, states);
}

void MenuView::drawChoices(sf::RenderTarget &target) const {
  sf::Text t{"", font, char_size};

  for (int i = -radius; i <= radius; i++, t.move(0, line_height)) {
    const std::string &name = model.getAroundSelected(i);
    if (i == 0) {
      t.setString("- " + name + " -");
      t.setFillColor(sf::Color::Yellow);
      t.setStyle(sf::Text::Bold);
    } else {
      t.setString(name);
      t.setFillColor(sf::Color{0xBBBBBBFF}); // Light grey
      t.setStyle(sf::Text::Regular);
    }
    target.draw(t);
  }
}
