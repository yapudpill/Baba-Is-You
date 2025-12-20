#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
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
const sf::Vector2i sprite_size{24, 24};

sf::Texture load_spritesheet(std::string path){
  sf::Image img;
  if (!img.loadFromFile(path))
    throw std::runtime_error(path);

  for (sf::Color col : background_colors) {
    img.createMaskFromColor(col);
  }
  sf::Texture t;
  t.loadFromImage(img);
  return t;
}

const sf::Texture characters{load_spritesheet("resource/image/characters.png")};
const sf::Texture objects{load_spritesheet("resource/image/objects.png")};
const sf::Texture texts{load_spritesheet("resource/image/texts.png")};
const sf::Texture tiles{load_spritesheet("resource/image/tiles.png")};

GameView::GameView(sf::RenderWindow &window, const Grid &grid):
    window{window}, grid{grid}, view_width(sprite_size.x * grid.getWidth()),
    view_height(sprite_size.y * grid.getHeight()),
    sprites {
      {&BasicEntity::BABA,  static_cast<StaticSprite*>(new FullAnimation{characters, {{576, 1}, sprite_size}, 1, 4})},
      {&BasicEntity::FLAG,  new StaticSprite{objects, {{351, 226}, sprite_size}}},
      {&BasicEntity::ROCK,  new StaticSprite{objects, {{851, 601}, sprite_size}}},
      {&BasicEntity::TILE,  new StaticSprite{objects, {{101, 826}, sprite_size}}},
      {&BasicEntity::WALL,  new StaticSprite{tiles, {{476, 1501}, sprite_size}}},
      {&BasicEntity::GRASS, new StaticSprite{tiles, {{476, 676}, sprite_size}}},

      {&RefEntity::NBABA,  new StaticSprite{characters, {{551, 1}, sprite_size}}},
      {&RefEntity::NFLAG,  new StaticSprite{objects, {{326, 226}, sprite_size}}},
      {&RefEntity::NROCK,  new StaticSprite{objects, {{826, 601}, sprite_size}}},
      {&RefEntity::NTILE,  new StaticSprite{objects, {{76, 826}, sprite_size}}},
      {&RefEntity::NWALL,  new StaticSprite{tiles, {{451, 1501}, sprite_size}}},
      {&RefEntity::NGRASS, new StaticSprite{tiles, {{451, 676}, sprite_size}}},
      {&RefEntity::NTEXT,  new StaticSprite{texts, {{126, 1}, sprite_size}}},

      {&Property::YOU,  new StaticSprite{texts, {{351, 226}, sprite_size}}},
      {&Property::WIN,  new StaticSprite{texts, {{351, 1123}, sprite_size}}},
      {&Property::STOP, new StaticSprite{texts, {{276, 301}, sprite_size}}},
      {&Property::PUSH, new StaticSprite{texts, {{126, 301}, sprite_size}}},

      {&Operator::IS, new StaticSprite{texts, {{226, 76}, sprite_size}}}
      }
{
  resize(window.getSize().x, window.getSize().y);
}

GameView::~GameView() {
  for (std::pair<const Entity*, Animation*> elem : sprites) {
    delete elem.second;
  }
}

void GameView::draw() {
  window.clear();

  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (const Block b : grid(i, j)) {
        std::map<const Entity*, Animation*>::const_iterator it = sprites.find(b.entity());
        if (it == sprites.end()) throw std::logic_error("cannot find sprite");
        sf::Sprite s{it->second->getSprite(b.d)};
        s.setPosition(j * sprite_size.y, i * sprite_size.x);
        window.draw(s);
      }
    }
  }

  window.display();
}

void GameView::resize(unsigned win_w, unsigned win_h) {
  sf::View win_view{{0, 0, view_width, view_height}};

  float ratio = std::min(win_w / view_width, win_h / view_height);
  float viewport_w = ratio * view_width / win_w;
  float viewport_h = ratio * view_height / win_h;

  win_view.setViewport({(1 - viewport_w) / 2, (1 - viewport_h) / 2, viewport_w, viewport_h});
  window.setView(win_view);
}

void GameView::advanceAnimations() {
  for (std::pair<const Entity*, Animation*> elem : sprites) {
    ++*elem.second;
  }
}
