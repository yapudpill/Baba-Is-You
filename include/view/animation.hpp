#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "model/util.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation {
  public:
    Animation(const sf::Texture &sheet, sf::IntRect base);
    virtual sf::Sprite getSprite(Direction d) = 0;
    virtual void operator++() = 0;

  protected:
    const sf::Texture &spritesheet;
    sf::IntRect base_rect;
};

#endif // ANIMATION_HPP
