#include "view/game_view.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/operator.hpp"
#include "model/ref_entity.hpp"

sf::Color const background_color{0x54a54bff};

sf::Texture load_spritesheet(std::string path){
  // Load an image file from a file
  sf::Image img;
  if (!img.loadFromFile(path))
    throw std::runtime_error(path);
  
  img.createMaskFromColor(background_color);
  sf::Texture t;
  t.loadFromImage(img);
  return t;
}

const sf::Texture characters {load_spritesheet("resource/image/characters.png")};
const sf::Texture objects {load_spritesheet("resource/image/objects.png")};
const sf::Texture texts {load_spritesheet("resource/image/texts.png")};
const sf::Texture tiles {load_spritesheet("resource/image/tiles.png")};

const std::map<Entity*, sf::Sprite> sprites {
  {&BasicEntity::BABA, {characters, {576, 1, 24, 24}}},
  {&BasicEntity::FLAG, {objects, {351, 226, 24, 24}}},
  {&BasicEntity::WALL, {tiles, {476, 1501, 24, 24}}},
  {&BasicEntity::ROCK, {objects, {851, 601, 24, 24}}},

  {&RefEntity::NBABA, {characters, {551, 1, 24, 24}}},
  {&RefEntity::NFLAG, {objects, {326, 226, 24, 24}}},
  {&RefEntity::NWALL, {tiles, {451, 1501, 24, 24}}},
  {&RefEntity::NROCK, {objects, {826, 601, 24, 24}}},

  {&Property::YOU,  {texts, {351, 226, 24, 24}}},
  {&Property::WIN,  {texts, {351, 1123, 24, 24}}},
  {&Property::STOP, {texts, {276, 301, 24, 24}}},
  {&Property::PUSH, {texts, {126, 301, 24, 24}}},

  {&Operator::IS, {texts, {226, 76, 24, 24}}}
};

sf::Sprite makeSprite(Entity *e, int cell_size, int x, int y) {
  auto it = sprites.find(e);
  sf::Sprite s{it->second};

  float scale = 1. * cell_size / s.getTextureRect().getSize().x;
  s.setScale(scale, scale);
  s.setPosition(y * cell_size, x * cell_size);

  return s;
}

GameView::GameView(sf::RenderWindow &window, const Game &game):
  window{window}, game{game} {}

void GameView::draw() {
  sf::Vector2u window_size = window.getSize();
  unsigned int cell_size =
    std::min(window_size.x / game.getWidth(), window_size.y / game.getHeight());

  window.clear();

  for (int i = 0; i < game.getHeight(); i++) {
    for (int j = 0; j < game.getWidth(); j++) {
      for (Entity *e : game[{i, j}]) {
        window.draw(makeSprite(e, cell_size, i, j));
      }
    }
  }

  window.display();
}
