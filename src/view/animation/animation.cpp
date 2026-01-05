#include "view/animation/animation.hpp"

Animation::Animation(const sf::Texture &sheet, sf::IntRect base):
  spritesheet{sheet}, base_rect{base} {}
