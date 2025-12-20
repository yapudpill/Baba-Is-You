#include "view/animated_sprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "model/util.hpp"

AnimatedSprite::AnimatedSprite(const sf::Texture &sheet, sf::IntRect base, int gap, unsigned frames):
  Animation{sheet, base}, gap{gap}, frames{frames} {}

sf::Sprite AnimatedSprite::getSprite(Direction) {
  return {spritesheet, current_rect};
}

void AnimatedSprite::operator++() {
  frame_no++;
  if (frame_no == frames) {
    frame_no = 0;
    current_rect = base_rect;
  } else {
    current_rect.left += base_rect.width + gap;
  }
}
