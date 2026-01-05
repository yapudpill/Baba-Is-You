#ifndef SPRITESHEET_FACTORY_HPP
#define SPRITESHEET_FACTORY_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace SpritesheetFactory {
  extern const sf::Vector2i sprite_size;
  const sf::Texture &get(const std::string &file);
}

#endif // SPRITESHEET_FACTORY_HPP
