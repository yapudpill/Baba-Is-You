#include "menu/menu_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "menu/menu_model.hpp"

sf::Font loadFont(std::string path) {
  sf::Font f;
  if (!f.loadFromFile(path))
    throw std::runtime_error("Cannot open font " + path);
  return f;
}

const sf::Font font = loadFont("resource/fonts/NotoSans-Regular.ttf");
const unsigned char_size = 30;

MenuView::MenuView(sf::RenderWindow &win, const MenuModel &m):
  window{win}, model{m} {}

void MenuView::draw() {
  window.clear();

  sf::Text t;
  t.setFont(font);
  t.setCharacterSize(char_size);
  t.setFillColor(sf::Color::White);

  sf::Vector2f pos{0, 0};
  for (std::pair<std::string, std::string> lvl : model.getLevels()) {
    t.setString(lvl.first);

    pos.y += char_size + 10;
    t.setPosition(pos);
    window.draw(t);
  }

  window.display();
}
