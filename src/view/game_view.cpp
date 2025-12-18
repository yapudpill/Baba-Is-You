#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/grid.hpp"
#include "model/operator.hpp"
#include "model/ref_entity.hpp"
#include "model/property.hpp"

const std::vector<sf::Color> background_colors{
  sf::Color{0x54a54bff},
  sf::Color{0x1b5999ff}
};
const std::string prefix = "resource/image/";

sf::Texture load_spritesheet(std::string name) {
  sf::Image img;
  if (!img.loadFromFile(prefix + name))
    throw std::runtime_error("Cannot load sprite sheet " + name);

  for (sf::Color col : background_colors) {
    img.createMaskFromColor(col);
  }
  sf::Texture t;
  t.loadFromImage(img);
  return t;
}

const sf::Texture characters = load_spritesheet("characters.png");
const sf::Texture objects = load_spritesheet("objects.png");
const sf::Texture texts = load_spritesheet("texts.png");
const sf::Texture tiles = load_spritesheet("tiles.png");

const sf::Vector2i sprite_size{24, 24};
const std::map<const Entity*, sf::Sprite> sprites {
  {&BasicEntity::BABA, {characters, {{576, 1}, sprite_size}}},
  {&BasicEntity::FLAG, {objects, {{351, 226}, sprite_size}}},
  {&BasicEntity::ROCK, {objects, {{851, 601}, sprite_size}}},
  {&BasicEntity::TILE, {objects, {{101, 826}, sprite_size}}},
  {&BasicEntity::WALL, {tiles, {{476, 1501}, sprite_size}}},
  {&BasicEntity::GRASS, {tiles, {{476, 676}, sprite_size}}},

  {&RefEntity::NBABA, {characters, {{551, 1}, sprite_size}}},
  {&RefEntity::NFLAG, {objects, {{326, 226}, sprite_size}}},
  {&RefEntity::NROCK, {objects, {{826, 601}, sprite_size}}},
  {&RefEntity::NTILE, {objects, {{76, 826}, sprite_size}}},
  {&RefEntity::NWALL, {tiles, {{451, 1501}, sprite_size}}},
  {&RefEntity::NGRASS, {tiles, {{451, 676}, sprite_size}}},
  {&RefEntity::NTEXT, {texts, {{126, 1}, sprite_size}}},

  {&Property::YOU,  {texts, {{351, 226}, sprite_size}}},
  {&Property::WIN,  {texts, {{351, 1123}, sprite_size}}},
  {&Property::STOP, {texts, {{276, 301}, sprite_size}}},
  {&Property::PUSH, {texts, {{126, 301}, sprite_size}}},

  {&Operator::IS, {texts, {{226, 76}, sprite_size}}}
};

GameView::GameView(const Grid &grid):
  View(sprite_size.x * grid.getWidth(), sprite_size.y * grid.getHeight()),
  grid{grid} {}

void GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (const Entity *e : grid(i, j)) {
        std::map<const Entity*, sf::Sprite>::const_iterator it = sprites.find(e);
        if (it == sprites.end()) throw std::logic_error("Cannot find sprite");
        sf::Sprite s{it->second};
        s.setPosition(j * sprite_size.y, i * sprite_size.x);
        target.draw(s, states);
      }
    }
  }
}
