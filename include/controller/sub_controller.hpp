#ifndef SUB_CONTROLLER_HPP
#define SUB_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "view/view.hpp"

class MainController;

class SubController {
  public:
    SubController(MainController &mc, sf::RenderWindow &win);
    virtual ~SubController() = default;
    virtual void onResized(unsigned width, unsigned height);
    virtual void onKeyPressed(sf::Keyboard::Key code) = 0;
    void update();

  protected:
    MainController &main_controller;
    sf::RenderWindow &window;
    virtual View &getView() = 0;
};

#endif // SUB_CONTROLLER_HPP
