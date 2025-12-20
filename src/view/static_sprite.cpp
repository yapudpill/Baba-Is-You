#include "view/static_sprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "model/util.hpp"

StaticSprite::StaticSprite(const sf::Texture &sheet, sf::IntRect base):
  Animation{sheet, base} {}

sf::Sprite StaticSprite::getSprite(Direction) {
  return {spritesheet, base_rect};
}

void StaticSprite::operator++() {}
