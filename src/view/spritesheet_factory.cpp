#include "view/spritesheet_factory.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

// Usefull constants
const std::string prefix = "resource/image/";
const std::vector<sf::Color> background_colors{
  sf::Color{0x54a54bff},
  sf::Color{0x1b5999ff}
};

const sf::Vector2i SpritesheetFactory::sprite_size{24,24};

// Cache of the already loaded textures
std::map<std::string, sf::Texture> cache;

const sf::Texture &SpritesheetFactory::get(const std::string &file) {
  if (cache.find(file) == cache.end()) {
    sf::Image img;
    if (!img.loadFromFile(prefix + file))
      throw std::runtime_error("Cannot load sprite sheet " + file);

    for (const sf::Color &col : background_colors) {
      img.createMaskFromColor(col);
    }

    sf::Texture t;
    t.loadFromImage(img);
    cache[file] = t;
  }
  return cache[file];
}
