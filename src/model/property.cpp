#include "model/property.hpp"

#include "model/action.hpp"
#include "model/entity.hpp"

class : public Property {
  Action onEnter(const Entity &e, Direction d) const override { return {}; }
  Action onStay(const Entity &e) const override { return {}; }
} hidden_you;

class : public Property {
  Action onEnter(const Entity &e, Direction d) const override { /* Do something */ return {}; }
  Action onStay(const Entity &e) const override { return {}; }
} hidden_push;

class : public Property {
  Action onEnter(const Entity &e, Direction d) const override { /* Do something */ return {}; }
  Action onStay(const Entity &e) const override { return {}; }
} hidden_stop;

class : public Property {
  Action onEnter(const Entity &e, Direction d) const override { return {}; }
  Action onStay(const Entity &e) const override {
    if (e.hasProp(Property::YOU)) {
      // Make the game stop by winning
    }
    return {};
  }
} hidden_win;

Property &Property::YOU{hidden_you};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
