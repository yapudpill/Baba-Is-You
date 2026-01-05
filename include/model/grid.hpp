#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "model/entity/entity.hpp"
#include "model/entity/property.hpp"
#include "model/util.hpp"

class Grid final {
  public:
    using cell = std::vector<Block>;

    Grid() = default;
    Grid(unsigned h, unsigned w);
    Grid(const Grid &other);
    Grid(Grid &&other) noexcept;
    ~Grid();
    Grid &operator=(const Grid &other);
    Grid &operator=(Grid &&other) noexcept;

    bool inBounds(unsigned i, unsigned j) const;
    bool inBounds(const coordinates &cds) const;

    cell &operator()(unsigned i, unsigned j);
    cell &operator[](coordinates cds);
    const cell operator()(unsigned i, unsigned j) const;
    const cell operator[](const coordinates &cds) const;

    local_blocks operator[](const Property &p);
    std::vector<coordinates> operator[](const Entity *entity);

    // Get all entities at position cds that can be casted to type T
    template<class T> std::vector<T*> getCast(const coordinates &cds);

    void swap(Grid &other) noexcept;

    unsigned getHeight() const { return height; }
    unsigned getWidth() const { return width; }

  private:
    unsigned height = 0, width = 0;
    cell **grid = nullptr;

  friend void swap(Grid &grid1, Grid &grid2) noexcept;
};

void swap(Grid &grid1, Grid &grid2) noexcept;

// Template implementation
template<class T>
std::vector<T*> Grid::getCast(const coordinates &cds) {
  if (!inBounds(cds)) return {};

  std::vector<T*> ret;
  for (Block &b : (*this)[cds]) {
    if (T *casted = dynamic_cast<T*>(b.entity()))
      ret.push_back(casted);
  }
  return ret;
}

#endif // GRID_HPP
