#ifndef MENU_MODEL_HPP
#define MENU_MODEL_HPP

#include <string>
#include <utility>
#include <vector>

class MenuModel {
  public:
    static const std::string prefix;

    MenuModel();
    void move(int nb);

    const std::vector<std::pair<std::string, std::string>> &getLevels() const { return levels; }
    std::string get();

  private:
    std::vector<std::pair<std::string, std::string>> levels;
    decltype(levels)::const_iterator pos;
};

#endif // MENU_MODEL_HPP
