#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

#include "model/entity.hpp"
#include "model/grid.hpp"
#include "view/animation.hpp"
#include "view/view.hpp"

class GameView final: public View {
  public:
    GameView(const Grid &game);
    ~GameView();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void advanceAnimations();

  private:
    const Grid &grid;
    const std::map<const Entity*, Animation*> sprites;
};

#endif // GAME_VIEW_HPP
