#include "model/property.hpp"

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/util.hpp"
#include "model/game.hpp"

// YOU + MOVE
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {}; }
  Action onStay(Block&, Block&, const coordinates&, Game&) const override { return {}; }
} hidden_you, hidden_move;

// PUSH
class : public Property {
  Action onEnter(Block &moving, Block &receiver, const coordinates &cds, Game &game) const override {
    receiver.d = moving.d;
    return game.moveAction(receiver, cds);
  }
  Action onStay(Block&, Block&, const coordinates&, Game&) const override { return {}; }
} hidden_push;

// STOP
class : public Property {
  Action onEnter(Block &, Block&, const coordinates&, Game&) const override {
    return {false};
  }
  Action onStay(Block&, Block&, const coordinates&, Game&) const override { return {}; }
} hidden_stop;

// WIN
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {}; }
  Action onStay(Block &staying, Block&, const coordinates&, Game &game) const override {
    if (staying.entity()->hasProp(Property::YOU)) {
      game.win = true;
    }
    return {};
  }
} hidden_win;

// DEFEAT
class : public Property {
  Action onEnter(Block&, Block&, const coordinates&, Game&) const override { return {}; }
  Action onStay(Block &staying, Block&, const coordinates &cds, Game&) const override {
    if (staying.entity()->hasProp(Property::YOU)) {
      return {{}, {{cds, staying}}};
    }
    return {};
  }
} hidden_defeat;

Property &Property::YOU{hidden_you};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
Property &Property::DEFEAT{hidden_defeat};
Property &Property::MOVE{hidden_move};
