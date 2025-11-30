#include "view/game_view.hpp"

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

const std::map<Entity*, std::string> textures {
  //{&BasicEntity::BABA, "resource/image/sprite_baba.png"},
  {&BasicEntity::BABA, "resource/image/baba_droite.png"},
  {&BasicEntity::FLAG, "resource/image/flag.png"},
  {&BasicEntity::WALL, "resource/image/wall.png"},
  {&BasicEntity::ROCK, "resource/image/rock.png"},

  {&RefEntity::NBABA, "resource/image/baba_text.png"},
  {&RefEntity::NFLAG, "resource/image/flag_textJClaire.png"},
  {&RefEntity::NWALL, "resource/image/wall_textGris.png"},
  {&RefEntity::NROCK, "resource/image/rock_textJaune.png"},

  {&Property::YOU, "resource/image/youRose.png"},
  {&Property::WIN, "resource/image/winC.png"},
  {&Property::STOP, "resource/image/stopC.png"},
  {&Property::PUSH, "resource/image/pushJ.png"},

  {&Operator::IS, "resource/image/isBlanc.png"}
};

std::map<Entity*, sf::Texture> loadTexture() {
  std::map<Entity*, sf::Texture> map;

  for (std::pair<Entity *const, std::string> p : textures) {
    sf::Texture tex;
    if (!tex.loadFromFile(p.second))
      throw std::runtime_error("Cannot load file " + p.second);
    map[p.first] = tex;
  }

  return map;
}

std::map<Entity*, sf::Texture> textureMap{loadTexture()};



sf::Sprite makeSprite(Entity *e, int cell_size, int x, int y) {
  sf::Texture t{textureMap.at(e)};
  float scale = 1. * cell_size / t.getSize().x;

  sf::Sprite s;
  s.setTexture(textureMap.at(e));
  //s.setTextureRect(sf::IntRect(0, 0, 40, 40));
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
