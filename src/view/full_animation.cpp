#include "view/full_animation.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "model/util.hpp"
#include "view/animated_sprite.hpp"
#include "view/directed_sprite.hpp"

FullAnimation::FullAnimation(const sf::Texture &sheet, sf::IntRect base, int gap, unsigned frames):
  DirectedSprite{sheet, base, gap}, AnimatedSprite{sheet, base, gap, frames} {}

sf::Sprite FullAnimation::getSprite(Direction d) {
  DirectedSprite::base_rect = AnimatedSprite::current_rect;
  return DirectedSprite::getSprite(d);
}

int FullAnimation::getOffset(Direction d) {
  return frames * DirectedSprite::getOffset(d);
}
