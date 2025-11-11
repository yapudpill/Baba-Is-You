#include "model/property.hpp"
#include "model/entity.hpp"

class Property::EmptyProp: public Property {
  bool onEnter(const Entity &e) override { return true; }
  bool onStay(const Entity &e) override { return true; }
};

class Property::Push: public Property {
  bool onEnter(const Entity &e) override { /* Do something */ return true; }
  bool onStay(const Entity &e) override { return true; }
};

class Property::Stop: public Property {
  bool onEnter(const Entity &e) override { /* Do something */ return true; }
  bool onStay(const Entity &e) override { return true; }
};

class Property::Win: public Property {
  bool onEnter(const Entity &e) override { return true; }
  bool onStay(const Entity &e) override {
    if (e.hasProperty(Property::YOU)) {
      // Make the game stop by winning
    }
    return true;
  }
};

Property::EmptyProp Property::hidden_you;
Property::Stop Property::hidden_stop;
Property::Push Property::hidden_push;
Property::Win Property::hidden_win;

Property &Property::YOU{hidden_you};
Property &Property::WIN{hidden_win};
Property &Property::PUSH{hidden_push};
Property &Property::STOP{hidden_stop};
