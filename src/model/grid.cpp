#include "model/grid.hpp"

#include <utility>
#include <vector>

#include "model/entity/entity.hpp"
#include "model/entity/property.hpp"
#include "model/util.hpp"

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

Grid::Grid(Grid &&other) noexcept {
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

Grid &Grid::operator=(Grid &&other) noexcept {
  swap(other);
  return *this;
}

bool Grid::inBounds(unsigned i, unsigned j) const {
  return i < height && j < width;
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

const Grid::cell Grid::operator()(unsigned i, unsigned j) const {
  return {grid[i][j].begin(), grid[i][j].end()};
}

const Grid::cell Grid::operator[](const coordinates &cds) const {
  return (*this)(cds.first, cds.second);
}

local_blocks Grid::operator[](const Property &p) {
  local_blocks ret;
  for (unsigned i = 0; i < height; i++) {
    for (unsigned j = 0; j < width; j++) {
      for (const Block &b : grid[i][j]) {
        if (b.entity()->hasProp(p)) {
          ret.emplace_back(coordinates{i, j}, b);
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
      for (const Block &b : grid[i][j]) {
        if (b.entity() == entity) ret.emplace_back(i, j);
      }
    }
  }
  return ret;
}

void Grid::swap(Grid &other) noexcept {
  using std::swap;
  swap(*this, other);

}

void swap(Grid &grid1, Grid &grid2) noexcept {
  using std::swap;
  swap(grid1.height, grid2.height);
  swap(grid1.width, grid2.width);
  swap(grid1.grid, grid2.grid);
}
