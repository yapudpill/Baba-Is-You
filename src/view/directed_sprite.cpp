#include "view/directed_sprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "model/util.hpp"
#include "view/static_sprite.hpp"

DirectedSprite::DirectedSprite(const sf::Texture &sheet, sf::IntRect base, int gap):
  StaticSprite{sheet, base}, gap{gap} {}

sf::Sprite DirectedSprite::getSprite(Direction d) {
  sf::IntRect ret = base_rect;
  ret.left += getOffset(d);
  return {spritesheet, ret};
}

int DirectedSprite::getOffset(Direction d) {
  int ret = 0;
  switch (d) {
    case Direction::Down: ret += base_rect.width + gap;
    case Direction::Left: ret += base_rect.width + gap;
    case Direction::Up: ret += base_rect.width + gap;
    case Direction::Right:;
  }
  return ret;
}
