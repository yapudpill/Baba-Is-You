#include "view/animation/animation_factory.hpp"

#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "model/entity/basic_entity.hpp"
#include "model/entity/entity.hpp"
#include "model/entity/operator.hpp"
#include "model/entity/property.hpp"
#include "model/entity/ref_entity.hpp"
#include "view/animation/animation.hpp"
#include "view/animation/full_animation.hpp"
#include "view/animation/static_sprite.hpp"
#include "view/spritesheet_factory.hpp"

using SpritesheetFactory::sprite_size;

AnimationFactory::~AnimationFactory() {
  for (const std::pair<const Entity *const, Animation*> &elem : cache) {
    delete elem.second;
  }
}

void AnimationFactory::advanceAll() {
  for (std::pair<const Entity *const, Animation*> &elem : cache) {
    ++*elem.second;
  }
}

Animation *makeAnim(const Entity *e);

const Animation &AnimationFactory::operator[](const Entity *e) const {
  Animation *&anim = cache[e];
  if (anim == nullptr) anim = makeAnim(e);
  return *anim;
};

Animation *makeCharacter(const sf::Vector2i &pos);
Animation *makeObject(const sf::Vector2i &pos);
Animation *makeTile(const sf::Vector2i &pos);
Animation *makeText(const sf::Vector2i &pos, const std::string &file = "texts.png");

Animation *makeAnim(const Entity *e) {
  // Basic entities
  if (e == &BasicEntity::BABA) return makeCharacter({576, 1});
  if (e == &BasicEntity::KEKE) return makeCharacter({576, 826});

  if (e == &BasicEntity::FLAG) return makeObject({351, 226});
  if (e == &BasicEntity::ROCK) return makeObject({851, 601});
  if (e == &BasicEntity::TILE) return makeObject({101, 826});
  if (e == &BasicEntity::KEY)  return makeObject({476, 376});
  if (e == &BasicEntity::DOOR) return makeObject({476, 151});

  if (e == &BasicEntity::WALL)  return makeTile({476, 1501});
  if (e == &BasicEntity::GRASS) return makeTile({476, 676});

  // Ref entities
  if (e == &RefEntity::NBABA) return makeText({551, 1}, "characters.png");
  if (e == &RefEntity::NKEKE) return makeText({551, 826}, "characters.png");

  if (e == &RefEntity::NFLAG) return makeText({326, 226}, "objects.png");
  if (e == &RefEntity::NROCK) return makeText({826, 601}, "objects.png");
  if (e == &RefEntity::NTILE) return makeText({76, 826}, "objects.png");
  if (e == &RefEntity::NKEY)  return makeText({451, 376}, "objects.png");
  if (e == &RefEntity::NDOOR) return makeText({451, 151}, "objects.png");

  if (e == &RefEntity::NWALL)  return makeText({451, 1501}, "tiles.png");
  if (e == &RefEntity::NGRASS) return makeText({451, 676}, "tiles.png");

  if (e == &RefEntity::NTEXT) return makeText({126, 1});

  // Properties
  if (e == &Property::YOU)    return makeText({351, 226});
  if (e == &Property::WIN)    return makeText({351, 1123});
  if (e == &Property::STOP)   return makeText({276, 301});
  if (e == &Property::PUSH)   return makeText({126, 301});
  if (e == &Property::DEFEAT) return makeText({51, 730});
  if (e == &Property::MOVE)   return makeText({351, 301});
  if (e == &Property::OPEN)   return makeText({276, 730});
  if (e == &Property::SHUT)   return makeText({351, 730});

  // Operators
  if (e == &Operator::IS) return makeText({226, 76});

  // Fallback
  throw std::logic_error("Sprite not found");
}

Animation *makeCharacter(const sf::Vector2i &pos) {
  return static_cast<StaticSprite*>(new FullAnimation{
    SpritesheetFactory::get("characters.png"),
    {pos, sprite_size},
    1,
    4
  });
}

Animation *makeObject(const sf::Vector2i &pos) {
  return new StaticSprite{SpritesheetFactory::get("objects.png"), {pos, sprite_size}};
}

Animation *makeTile(const sf::Vector2i &pos) {
  return new StaticSprite{SpritesheetFactory::get("tiles.png"), {pos, sprite_size}};
}

Animation *makeText(const sf::Vector2i &pos, const std::string &file) {
  return new StaticSprite{SpritesheetFactory::get(file), {pos, sprite_size}};

}
