#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

class View : public sf::Drawable {
  public:
    View() = default;
    View(float w, float h);
    virtual sf::View resize(unsigned win_w, unsigned win_h);

  protected:
    float width = 0, height = 0;
};

#endif // VIEW_HPP
