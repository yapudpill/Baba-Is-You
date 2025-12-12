#ifndef MENU_MODEL_HPP
#define MENU_MODEL_HPP

#include <string>
#include <vector>

class MenuModel {
  public:
    static const std::string prefix;

    MenuModel();

    const std::vector<std::string> &getNames() const { return names; }
    std::string getPath(unsigned index) const;

  private:
    std::vector<std::string> names;
    std::vector<std::string> paths;
};

#endif // MENU_MODEL_HPP
