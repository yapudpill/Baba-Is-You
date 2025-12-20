#ifndef FULL_ANIMATION_HPP
#define FULL_ANIMATION_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "model/util.hpp"
#include "view/animated_sprite.hpp"
#include "view/directed_sprite.hpp"

class FullAnimation: public DirectedSprite, public AnimatedSprite {
  public:
    FullAnimation(const sf::Texture &sheet, sf::IntRect base, int gap, unsigned frames);
    sf::Sprite getSprite(Direction d) override;

  protected:
    int getOffset(Direction d) override;
};

#endif // FULL_ANIMATION_HPP
