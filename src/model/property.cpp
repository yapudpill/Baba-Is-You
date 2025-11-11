#include "model/property.hpp"
#include "model/entity.hpp"

class : public Property {
  bool onEnter(const Entity &e) const override { return true; }
  bool onStay(const Entity &e) const override { return true; }
} hidden_you;

class : public Property {
  bool onEnter(const Entity &e) const override { /* Do something */ return true; }
  bool onStay(const Entity &e) const override { return true; }
} hidden_push;

class : public Property {
  bool onEnter(const Entity &e) const override { /* Do something */ return true; }
  bool onStay(const Entity &e) const override { return true; }
} hidden_stop;

class : public Property {
  bool onEnter(const Entity &e) const override { return true; }
  bool onStay(const Entity &e) const override {
    if (e.hasProperty(Property::YOU)) {
      // Make the game stop by winning
    }
    return true;
  }
} hidden_win;

Property &Property::YOU{hidden_you};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
Property &Property::WIN{hidden_win};
