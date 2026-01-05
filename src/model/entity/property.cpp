#include "model/entity/property.hpp"

#include "model/action.hpp"
#include "model/entity/entity.hpp"
#include "model/util.hpp"
#include "model/rule_manager.hpp"

// YOU + MOVE + OPEN
class EmptyProp : public Property {
  Action onEnter(Block&, Block&, const coordinates&, RuleManager&) const override { return {}; }
  Action onStay(Block&, Block&, const coordinates&, RuleManager&) const override { return {}; }
} hidden_you, hidden_move, hidden_open;

// PUSH
class : public EmptyProp {
  Action onEnter(Block &moving, Block &receiver, const coordinates &cds, RuleManager &rules) const override {
    receiver.d = moving.d;
    return rules.moveAction(receiver, cds);
  }
} hidden_push;

// STOP
class : public EmptyProp {
  Action onEnter(Block &, Block&, const coordinates&, RuleManager&) const override {
    return false;
  }
} hidden_stop;

// WIN
class : public EmptyProp {
  Action onStay(Block &staying, Block&, const coordinates&, RuleManager &rules) const override {
    if (staying.entity()->hasProp(Property::YOU)) {
      rules.setWin();
    }
    return {};
  }
} hidden_win;

// DEFEAT
class : public EmptyProp {
  Action onStay(Block &staying, Block&, const coordinates &cds, RuleManager&) const override {
    if (staying.entity()->hasProp(Property::YOU)) {
      return {{}, {{cds, staying}}};
    }
    return {};
  }
} hidden_defeat;

// SHUT
class : public EmptyProp {
  Action onEnter(Block &moving, Block &receiver, const coordinates &cds, RuleManager&) const override {
    if (moving.entity()->hasProp(Property::OPEN)) {
      return {{}, {{next(cds, oppositeDirection(moving.d)), moving}, {cds,receiver}}, false};
    }
    return false;
  }
} hidden_shut;

Property &Property::YOU{hidden_you};
Property &Property::MOVE{hidden_move};
Property &Property::OPEN{hidden_open};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
Property &Property::DEFEAT{hidden_defeat};
Property &Property::SHUT{hidden_shut};
