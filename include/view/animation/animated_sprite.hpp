#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "model/util.hpp"
#include "view/animation/animation.hpp"

class AnimatedSprite: public Animation {
  public:
    AnimatedSprite(const sf::Texture &sheet, sf::IntRect base, int gap, unsigned frames);
    sf::Sprite getSprite(Direction d) const override;
    void operator++() override;

  protected:
    sf::IntRect current_rect;
    int gap;
    unsigned frames, frame_no = 0;
};

#endif // ANIMATED_SPRITE_HPP
