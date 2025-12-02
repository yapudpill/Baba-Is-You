#ifndef SUB_CONTROLLER_HPP
#define SUB_CONTROLLER_HPP

#include <SFML/Window/Keyboard.hpp>

class SubController {
  public:
    virtual ~SubController() = default;
    virtual void onResized(unsigned width, unsigned height) = 0;
    virtual void onKeyPressed(sf::Keyboard::Key code) = 0;
};

#endif // SUB_CONTROLLER_HPP
