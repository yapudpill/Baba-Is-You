#ifndef SUB_CONTROLLER_HPP
#define SUB_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

class MainController;

class SubController {
  public:
    SubController(MainController &mc, sf::RenderWindow &win);
    virtual ~SubController() = default;
    virtual void onResized(unsigned width, unsigned height) = 0;
    virtual void onKeyPressed(sf::Keyboard::Key code) = 0;

  protected:
    MainController &main_controller;
    sf::RenderWindow &window;
};

#endif // SUB_CONTROLLER_HPP
