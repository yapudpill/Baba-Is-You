#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/grid.hpp"
#include "model/operator.hpp"
#include "model/ref_entity.hpp"
#include "model/property.hpp"
#include "model/util.hpp"
#include "view/animation.hpp"
#include "view/full_animation.hpp"
#include "view/static_sprite.hpp"

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

GameView::GameView(const Grid &grid):
  View(sprite_size.x * grid.getWidth(), sprite_size.y * grid.getHeight()),
  grid{grid}, sprites {
    {&BasicEntity::BABA,  static_cast<StaticSprite*>(new FullAnimation{characters, {{576, 1}, sprite_size}, 1, 4})},
    {&BasicEntity::KEKE,  static_cast<StaticSprite*>(new FullAnimation{characters, {{576, 826}, sprite_size}, 1, 4})},
    {&BasicEntity::FLAG,  new StaticSprite{objects, {{351, 226}, sprite_size}}},
    {&BasicEntity::ROCK,  new StaticSprite{objects, {{851, 601}, sprite_size}}},
    {&BasicEntity::TILE,  new StaticSprite{objects, {{101, 826}, sprite_size}}},
    {&BasicEntity::WALL,  new StaticSprite{tiles, {{476, 1501}, sprite_size}}},
    {&BasicEntity::GRASS, new StaticSprite{tiles, {{476, 676}, sprite_size}}},
    {&BasicEntity::KEY, new StaticSprite{objects, {{476, 376}, sprite_size}}},
    {&BasicEntity::DOOR, new StaticSprite{objects, {{476, 151}, sprite_size}}},


    {&RefEntity::NBABA,  new StaticSprite{characters, {{551, 1}, sprite_size}}},
    {&RefEntity::NKEKE,  new StaticSprite{characters, {{551, 826}, sprite_size}}},
    {&RefEntity::NFLAG,  new StaticSprite{objects, {{326, 226}, sprite_size}}},
    {&RefEntity::NROCK,  new StaticSprite{objects, {{826, 601}, sprite_size}}},
    {&RefEntity::NTILE,  new StaticSprite{objects, {{76, 826}, sprite_size}}},
    {&RefEntity::NWALL,  new StaticSprite{tiles, {{451, 1501}, sprite_size}}},
    {&RefEntity::NGRASS, new StaticSprite{tiles, {{451, 676}, sprite_size}}},
    {&RefEntity::NTEXT,  new StaticSprite{texts, {{126, 1}, sprite_size}}},
    {&RefEntity::NKEY,  new StaticSprite{objects, {{451, 376}, sprite_size}}},
    {&RefEntity::NDOOR,  new StaticSprite{objects, {{451, 151}, sprite_size}}},


    {&Property::YOU,  new StaticSprite{texts, {{351, 226}, sprite_size}}},
    {&Property::WIN,  new StaticSprite{texts, {{351, 1123}, sprite_size}}},
    {&Property::STOP, new StaticSprite{texts, {{276, 301}, sprite_size}}},
    {&Property::PUSH, new StaticSprite{texts, {{126, 301}, sprite_size}}},
    {&Property::DEFEAT, new StaticSprite{texts, {{51, 730}, sprite_size}}},
    {&Property::MOVE, new StaticSprite{texts, {{351, 301}, sprite_size}}},
    {&Property::OPEN, new StaticSprite{texts, {{276, 730}, sprite_size}}},
    {&Property::SHUT, new StaticSprite{texts, {{351, 730}, sprite_size}}},


    {&Operator::IS, new StaticSprite{texts, {{226, 76}, sprite_size}}}
    } {}

GameView::~GameView() {
  for (std::pair<const Entity*, Animation*> elem : sprites) {
    delete elem.second;
  }
}

void GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (const Block b : grid(i, j)) {
        std::map<const Entity*, Animation*>::const_iterator it = sprites.find(b.entity());
        if (it == sprites.end()) throw std::logic_error("cannot find sprite");
        sf::Sprite s{it->second->getSprite(b.d)};
        s.setPosition(j * sprite_size.y, i * sprite_size.x);
        target.draw(s, states);
      }
    }
  }
}

void GameView::advanceAnimations() {
  for (std::pair<const Entity*, Animation*> elem : sprites) {
    ++*elem.second;
  }
}
