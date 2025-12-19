#include "model/property.hpp"

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/util.hpp"
#include "model/game.hpp"

// YOU
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {}; }
  Action onStay(Block&, Game&) const override { return {}; }
} hidden_you;

// PUSH
class : public Property {
  Action onEnter(Block &moving, Block &receiver, const coordinates &cds, Game &game) const override {
    receiver.d = moving.d;
    return game.moveAction(receiver, cds);
  }
  Action onStay(Block&, Game&) const override { return {}; }
} hidden_push;

// STOP
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {false}; }
  Action onStay(Block&, Game&) const override { return {}; }
} hidden_stop;

// WIN
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {}; }
  Action onStay(Block &b, Game &game) const override {
    if (b.entity()->hasProp(Property::YOU)) {
      game.win = true;
    }
    return {};
  }
} hidden_win;

Property &Property::YOU{hidden_you};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
