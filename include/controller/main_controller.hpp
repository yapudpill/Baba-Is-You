#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include "controller/sub_controller.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class MainController {
  public:
    MainController();
    virtual ~MainController();

    void run();
    void loadMenu();
    void loadLevel(std::string path);

  private:
    sf::RenderWindow window;
    SubController *subController = nullptr;
};

#endif // MAIN_CONTROLLER_HPP
