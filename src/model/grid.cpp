#include "model/grid.hpp"
#include "model/entity.hpp"
#include "model/property.hpp"
#include "model/ref_entity.hpp"
#include "model/util.hpp"

#include <utility>

Grid::Grid(unsigned h, unsigned w): height{h}, width{w}, grid{new cell*[h]} {
  for (unsigned i = 0; i < height; i++) {
    grid[i] = new cell[width];
  }
}

Grid::Grid(const Grid &other): Grid{other.height, other.width} {
  for (unsigned i = 0; i < height; i++) {
    for (unsigned j = 0; i < width; j++) {
      grid[i][j] = other.grid[i][j];
    }
  }
}

Grid::Grid(Grid &&other) {
  swap(other);
}

Grid::~Grid() {
  for (unsigned i = 0; i < height; i++) {
    delete[] grid[i];
  }
  delete[] grid;
}

Grid &Grid::operator=(const Grid &other) {
  Grid copy{other};
  swap(copy);
  return *this;
}

Grid &Grid::operator=(Grid &&other) {
  swap(other);
  return *this;
}

bool Grid::inBounds(unsigned i, unsigned j) const {
  return
    0 <= i && i < height &&
    0 <= j && j < width;
}

bool Grid::inBounds(const coordinates &cds) const {
  return inBounds(cds.first, cds.second);
}

Grid::cell &Grid::operator()(unsigned i, unsigned j) {
  return grid[i][j];
}

Grid::cell &Grid::operator[](coordinates cds) {
  return (*this)(cds.first, cds.second);
}

Grid::const_cell Grid::operator()(unsigned i, unsigned j) const {
  return {grid[i][j].begin(), grid[i][j].end()};
}

Grid::const_cell Grid::operator[](coordinates cds) const {
  return (*this)(cds.first, cds.second);
}

local_entities Grid::operator[](const Property &p) {
  local_entities ret;
  for (unsigned i = 0; i < height; i++) {
    for (unsigned j = 0; j < width; j++) {
      for (Entity *e : grid[i][j]) {
        if (e->hasProp(p)) {
          ret.emplace_back(coordinates{i, j}, e);
        }
      }
    }
  }
  return ret;
}

std::vector<coordinates> Grid::operator[](const Entity *entity) {
  std::vector<coordinates> ret;
  for (unsigned i = 0; i < height; i++) {
    for (unsigned j = 0; j < width; j++) {
      for (Entity *e : grid[i][j]) {
        if (e == entity) ret.emplace_back(i, j);
      }
    }
  }
  return ret;
}

RefEntity *Grid::getRefEntity(coordinates cds) {
  for (Entity *e : (*this)[cds]) {
    if (RefEntity *re = dynamic_cast<RefEntity*>(e))
      return re;
  }
  return nullptr;
}

Property *Grid::getProperty(coordinates cds) {
  for (Entity *e : (*this)[cds]) {
    if (Property *p = dynamic_cast<Property*>(e))
      return p;
  }
  return nullptr;
}

void Grid::swap(Grid &other) {
  using std::swap;
  swap(*this, other);

}

void swap(Grid &grid1, Grid &grid2) {
  using std::swap;
  swap(grid1.height, grid2.height);
  swap(grid1.width, grid2.width);
  swap(grid1.grid, grid2.grid);
}
