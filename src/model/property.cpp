#include "model/property.hpp"

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/util.hpp"
#include "model/game.hpp"

// YOU
class : public Property {
  Action onEnter(Entity&, Direction, Entity&, const coordinates&, const Game&)
    const override { return {}; }
  Action onStay(const Entity&, const Game&) const override { return {}; }
} hidden_you;

// PUSH
class : public Property {
  Action onEnter(Entity &moving, Direction d, Entity &receiver, const coordinates &cds, const Game &game) const override {
    return game.moveAction(&receiver, cds, d);
  }
  Action onStay(const Entity &e, const Game&) const override { return {}; }
} hidden_push;

// STOP
class : public Property {
  Action onEnter(Entity&, Direction, Entity&, const coordinates&, const Game&)
    const override { return {false}; }
  Action onStay(const Entity&, const Game&) const override { return {}; }
} hidden_stop;

// WIN
class : public Property {
  Action onEnter(Entity &e, Direction d, Entity&, const coordinates&, const Game &game) const override { return {}; }
  Action onStay(const Entity &e, const Game &game) const override {
    if (e.hasProp(Property::YOU)) {
      game.win = true;
    }
    return {};
  }
} hidden_win;

Property &Property::YOU{hidden_you};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
