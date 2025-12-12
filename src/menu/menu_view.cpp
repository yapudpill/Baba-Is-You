#include "menu/menu_view.hpp"
#include "model/util.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

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
const unsigned logo_w{logo_texture.getSize().x}, logo_h{logo_texture.getSize().y};
const sf::Sprite logo{logo_texture};

const sf::Font font = loadFont("resource/fonts/NotoSans-Regular.ttf");
const unsigned char_size = 40;
const int lines{5};

// TODO: find how to define view_width and view_height properly
MenuView::MenuView(sf::RenderWindow &win, const std::vector<std::string> &choices):
    window{win}, view_width{1.f * logo_w},
    view_height{1.5f * char_size * lines + logo_h}, choices{choices} {
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

  window.draw(logo);

  sf::Text t{"", font, char_size};

  for (int i = std::max(0, selected - lines / 2);
      i < std::min(static_cast<int>(choices.size()), selected + lines /2);
      i++) {
    t.setString(choices[i]);
    t.setPosition({0, logo_h + 1.5f * char_size * i});
    if (i == selected) {
      t.setFillColor(sf::Color::Red);
      t.setStyle(sf::Text::Bold);
    } else {
      t.setFillColor(sf::Color::White);
      t.setStyle(sf::Text::Regular);
    }
    window.draw(t);
  }

  window.display();
}

void MenuView::moveSelection(Direction d) {
  switch (d) {
    case Direction::Down:
    case Direction::Left:
      if (selected < static_cast<int>(choices.size()) - 1) selected++;
      break;

    case Direction::Up:
    case Direction::Right:
      if (selected > 0) selected--;
      break;
  }
}
