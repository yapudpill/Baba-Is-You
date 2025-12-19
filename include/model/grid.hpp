#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "model/entity.hpp"
#include "model/property.hpp"
#include "model/ref_entity.hpp"
#include "model/util.hpp"

class Grid final {
  public:
    using cell = std::vector<Block>;

    Grid() = default;
    Grid(unsigned h, unsigned w);
    Grid(const Grid &other);
    Grid(Grid &&other);
    ~Grid();
    Grid &operator=(const Grid &other);
    Grid &operator=(Grid &&other);

    bool inBounds(unsigned i, unsigned j) const;
    bool inBounds(const coordinates &cds) const;

    cell &operator()(unsigned i, unsigned j);
    cell &operator[](coordinates cds);

    const cell operator()(unsigned i, unsigned j) const;
    const cell operator[](coordinates cds) const;

    local_blocks operator[](const Property &p);
    std::vector<coordinates> operator[](const Entity *entity);

    RefEntity *getRefEntity(coordinates cds);
    Property *getProperty(coordinates cds);

    void swap(Grid &other);

    unsigned getHeight() const { return height; }
    unsigned getWidth() const { return width; }

  private:
    unsigned height = 0, width = 0;
    cell **grid = nullptr;

  friend void swap(Grid &grid1, Grid &grid2);
};

void swap(Grid &grid1, Grid &grid2);

#endif // GRID_HPP
