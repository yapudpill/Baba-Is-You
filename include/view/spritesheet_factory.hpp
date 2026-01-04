#ifndef SPRITESHEET_FACTORY_HPP
#define SPRITESHEET_FACTORY_HPP

#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace SpritesheetFactory {
  const sf::Texture &get(const std::string &file);
}

#endif // SPRITESHEET_FACTORY_HPP
