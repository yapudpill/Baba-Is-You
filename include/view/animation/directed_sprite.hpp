#ifndef DIRECTED_SPRITE_HPP
#define DIRECTED_SPRITE_HPP

#include "model/util.hpp"
#include "view/animation/static_sprite.hpp"

class DirectedSprite: public StaticSprite {
  public:
    DirectedSprite(const sf::Texture &sheet, sf::IntRect base, int gap);
    sf::Sprite getSprite(Direction d) const override;

  protected:
    const int gap;
    virtual int getOffset(Direction d) const;
};

#endif // DIRECTED_SPRITE_HPP
