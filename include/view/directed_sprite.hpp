#ifndef DIRECTED_SPRITE_HPP
#define DIRECTED_SPRITE_HPP

#include "model/util.hpp"
#include "view/static_sprite.hpp"

class DirectedSprite: public StaticSprite {
  public:
    DirectedSprite(const sf::Texture &sheet, sf::IntRect base, int gap);
    sf::Sprite getSprite(Direction d) override;

  protected:
    const int gap;
    virtual int getOffset(Direction d);
};

#endif // DIRECTED_SPRITE_HPP
