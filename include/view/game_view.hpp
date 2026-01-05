#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "model/grid.hpp"
#include "view/animation/animation_factory.hpp"
#include "view/view.hpp"

class GameView final: public View {
  public:
    GameView(const Grid &game);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void advanceAnimations();

  private:
    const Grid &grid;
    AnimationFactory animations;
};

#endif // GAME_VIEW_HPP
