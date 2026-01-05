#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "model/grid.hpp"
#include "model/util.hpp"
#include "view/animation/animation.hpp"
#include "view/spritesheet_factory.hpp"

using SpritesheetFactory::sprite_size;

GameView::GameView(const Grid &grid):
  View(sprite_size.x * grid.getWidth(), sprite_size.y * grid.getHeight()),
  grid{grid} {}

void GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (const Block &b : grid(i, j)) {
        sf::Sprite s = animations[b.entity()].getSprite(b.d);
        s.setPosition(j * sprite_size.x, i * sprite_size.y);
        target.draw(s, states);
      }
    }
  }
}

void GameView::advanceAnimations() { animations.advanceAll(); }
