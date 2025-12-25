#include "menu/menu_model.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


MenuModel::MenuModel() {
  static const std::string prefix = "resource/level/";

  std::ifstream index{prefix + "index"};
  if (!index) throw  std::runtime_error("No level index found");

  std::string l;
  while (std::getline(index, l)) {
    std::istringstream line{l};

    std::string name, path;
    if (!std::getline(line, name, ','))
      throw std::runtime_error("Missing level name");
    if (!std::getline(line, path, ','))
      throw std::runtime_error("Missing level path");

    names.push_back(name);
    paths.push_back(prefix + path);
  }
}

void MenuModel::moveSelected(int amount) {
  selected_index += amount;

  // Loop around so that selected_index stays in [0, nb_choices)
  int nb_choices = paths.size();
  selected_index = ((selected_index % nb_choices) + nb_choices) % nb_choices;
}

const std::string &MenuModel::getAroundSelected(int offset) const {
  int index = selected_index + offset;

  // Loop around so index stays in [0, nb_choices)
  int nb_choices = paths.size();
  index = ((index % nb_choices) + nb_choices) % nb_choices;

  return names[index];
}

const std::string &MenuModel::getPath() const {
  return paths[selected_index];
}
