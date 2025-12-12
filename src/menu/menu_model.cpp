#include "menu/menu_model.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

const std::string MenuModel::prefix = "resource/level/";

MenuModel::MenuModel() {
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
    paths.push_back(path);
  }
}

std::string MenuModel::getPath(unsigned index) const {
  return prefix + paths[index];
}
