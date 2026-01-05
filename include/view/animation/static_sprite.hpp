#ifndef STATIC_SPRITE_HPP
#define STATIC_SPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "model/util.hpp"
#include "view/animation/animation.hpp"

class StaticSprite: public Animation {
  public:
    StaticSprite(const sf::Texture &sheet, sf::IntRect base);
    sf::Sprite getSprite(Direction d) const override;
    void operator++() override;
};

#endif // STATIC_SPRITE_HPP
