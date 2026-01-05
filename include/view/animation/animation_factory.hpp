#ifndef ANIMATION_FACTORY_HPP
#define ANIMATION_FACTORY_HPP

#include <map>

#include "model/entity.hpp"
#include "view/animation/animation.hpp"

class AnimationFactory {
  public:
    ~AnimationFactory();
    const Animation &operator[](const Entity *e) const;
    void advanceAll();

  private:
    mutable std::map<const Entity*, Animation*> cache;
};

#endif // ANIMATION_FACTORY_HPP
