#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/operator.hpp"
#include "model/ref_entity.hpp"

const std::vector<sf::Color> background_colors{
  sf::Color{0x54a54bff},
  sf::Color{0x1b5999ff}
};
const unsigned sprite_size{24};

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

const std::map<Entity*, sf::Sprite> sprites {
  {&BasicEntity::BABA, {characters, {576, 1, sprite_size, sprite_size}}},
  {&BasicEntity::FLAG, {objects, {351, 226, sprite_size, sprite_size}}},
  {&BasicEntity::ROCK, {objects, {851, 601, sprite_size, sprite_size}}},
  {&BasicEntity::TILE, {objects, {101, 826, sprite_size, sprite_size}}},
  {&BasicEntity::WALL, {tiles, {476, 1501, sprite_size, sprite_size}}},
  {&BasicEntity::GRASS, {tiles, {476, 676, sprite_size, sprite_size}}},

  {&RefEntity::NBABA, {characters, {551, 1, sprite_size, sprite_size}}},
  {&RefEntity::NFLAG, {objects, {326, 226, sprite_size, sprite_size}}},
  {&RefEntity::NROCK, {objects, {826, 601, sprite_size, sprite_size}}},
  {&RefEntity::NTILE, {objects, {76, 826, sprite_size, sprite_size}}},
  {&RefEntity::NWALL, {tiles, {451, 1501, sprite_size, sprite_size}}},
  {&RefEntity::NGRASS, {tiles, {451, 676, sprite_size, sprite_size}}},

  {&Property::YOU,  {texts, {351, 226, sprite_size, sprite_size}}},
  {&Property::WIN,  {texts, {351, 1123, sprite_size, sprite_size}}},
  {&Property::STOP, {texts, {276, 301, sprite_size, sprite_size}}},
  {&Property::PUSH, {texts, {126, 301, sprite_size, sprite_size}}},

  {&Operator::IS, {texts, {226, 76, sprite_size, sprite_size}}}
};

GameView::GameView(sf::RenderWindow &window, const Game &game):
    window{window}, game{game}, view_width{1.f * sprite_size * game.getWidth()},
    view_height{1.f * sprite_size * game.getHeight()} {
  resize(window.getSize().x, window.getSize().y);
}

void GameView::draw() {
  window.clear();

  for (int i = 0; i < game.getHeight(); i++) {
    for (int j = 0; j < game.getWidth(); j++) {
      for (Entity *e : game[{i, j}]) {
        std::map<Entity*, sf::Sprite>::const_iterator it = sprites.find(e);
        if (it == sprites.end()) throw std::logic_error("cannot find sprite");
        sf::Sprite s{it->second};
        s.setPosition(j * sprite_size, i * sprite_size);
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
