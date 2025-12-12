#include "menu/menu_view.hpp"
#include "model/util.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>
#include <vector>

sf::Font loadFont(std::string path) {
  sf::Font f;
  if (!f.loadFromFile(path))
    throw std::runtime_error("Cannot open font " + path);
  return f;
}

const sf::Font font = loadFont("resource/fonts/NotoSans-Regular.ttf");
const unsigned char_size = 40;

// TODO: find how to define view_width and view_height properly
MenuView::MenuView(sf::RenderWindow &win, const std::vector<std::string> &choices):
    window{win}, view_width{1000}, view_height{800}, choices{choices} {
  resize(window.getSize().x, window.getSize().y);
}

void MenuView::resize(unsigned win_w, unsigned win_h) {
  sf::View win_view{{0, 0, view_width, view_height}};

  float ratio = std::min(win_w / view_width, win_h / view_height);
  float viewport_w = ratio * view_width / win_w;
  float viewport_h = ratio * view_height / win_h;

  win_view.setViewport({(1 - viewport_w) / 2, (1 - viewport_h) / 2, viewport_w, viewport_h});
  window.setView(win_view);
}

void MenuView::draw() {
  window.clear();

  sf::Text t;
  t.setFont(font);
  t.setCharacterSize(char_size);
  t.setFillColor(sf::Color::White);

  sf::Vector2f pos{0, 0};
  for (unsigned i = 0; i < choices.size(); i++, pos.y += 1.5f * char_size) {
    t.setString(choices[i]);
    t.setPosition(pos);
    if (i == selected) t.setFillColor(sf::Color::Red);
    window.draw(t);
    if (i == selected) t.setFillColor(sf::Color::White);
  }

  window.display();
}

void MenuView::moveSelection(Direction d) {
  switch (d) {
    case Direction::Down:
    case Direction::Left:
      if (selected < choices.size() -1) selected++;
      break;

    case Direction::Up:
    case Direction::Right:
      if (selected != 0) selected--;
      break;
  }
}
