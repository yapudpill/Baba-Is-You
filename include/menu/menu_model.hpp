#ifndef MENU_MODEL_HPP
#define MENU_MODEL_HPP

#include <string>
#include <vector>

class MenuModel {
  public:
    MenuModel();

    void moveSelected(int amount);
    const std::string &getAroundSelected(int offset) const;
    const std::string &getPath() const;

  private:
    std::vector<std::string> names;
    std::vector<std::string> paths;
    int selected_index = 0;
};

#endif // MENU_MODEL_HPP
