#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "model/grid.hpp"
#include "view/view.hpp"

class GameView: public View {
  public:
    GameView(const Grid &game);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:
    const Grid &grid;
};

#endif // GAME_VIEW_HPP
