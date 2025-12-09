#include "menu/menu_model.hpp"

#include <fstream>
#include <sstream>
#include <string>

const std::string MenuModel::prefix = "resource/level/";

MenuModel::MenuModel() {
  std::ifstream index{prefix + "index"};
  if (!index) throw  std::runtime_error("No level index found");

  std::string l;
  while (std::getline(index, l)) {
    std::istringstream line{l};

    std::string name, path;
    std::getline(line, name, ',');
    std::getline(line, path, ',');

    levels.emplace_back(name, prefix + path);
  }

  pos = levels.cbegin();
}

void MenuModel::move(int nb) {
  pos += nb;
  if (pos < levels.begin()) pos = levels.begin();
  else if (pos >= levels.end()) pos = levels.end() - 1;
}

std::string MenuModel::get() {
  return pos->second;
}
