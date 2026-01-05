#include "view/animation/directed_sprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "model/util.hpp"
#include "view/animation/static_sprite.hpp"

DirectedSprite::DirectedSprite(const sf::Texture &sheet, sf::IntRect base, int gap):
  StaticSprite{sheet, base}, gap{gap} {}

sf::Sprite DirectedSprite::getSprite(Direction d) const {
  sf::IntRect ret = base_rect;
  ret.left += getOffset(d);
  return {spritesheet, ret};
}

int DirectedSprite::getOffset(Direction d) const {
  int ret = 0;
  switch (d) {
    case Direction::Down: ret += base_rect.width + gap;
    case Direction::Left: ret += base_rect.width + gap;
    case Direction::Up: ret += base_rect.width + gap;
    case Direction::Right:;
  }
  return ret;
}
