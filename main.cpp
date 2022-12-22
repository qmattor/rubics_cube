// Quincy Mattor
// Copyright 2022

#include <iostream>
#include "./rubics.hpp"

int main() {
  rubics_cube cube;
  std::cout << cube.is_solved() << std::endl;
  auto face = cube.get_side(rubics_cube::side::FRONT);
  cube.rotate(rubics_cube::direction::up, 0);
  std::cout << cube.is_solved() << std::endl;
  return 0;
}

