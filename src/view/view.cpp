#include "view/view.hpp"

#include <SFML/Graphics/View.hpp>

View::View(float w, float h): width{w}, height{h} {}

sf::View View::resize(unsigned win_w, unsigned win_h) {
  sf::View win_view{{0, 0, width, height}};

  float ratio = std::min(win_w / width, win_h / height);
  float viewport_w = ratio * width / win_w;
  float viewport_h = ratio * height / win_h;

  win_view.setViewport({(1 - viewport_w) / 2, (1 - viewport_h) / 2, viewport_w, viewport_h});
  return win_view;
}