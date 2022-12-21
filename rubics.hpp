// Quincy Mattor
// Copyright 2022

#include "./libqm.hpp"

#ifndef RUBICS_HPP_
#define RUBICS_HPP_

class rubics_cube {
 private:
  enum class side : char {TOP = 0, BOTTOM, LEFT, RIGHT, BACK, FRONT};
  std::vector<libqm::matrix<uint8_t> *> sides;
 public:
  enum class direction : char {up = 0, down, left, right};
  rubics_cube();
  explicit rubics_cube(std::vector<libqm::matrix<uint8_t> *> &start_pos);
  void rotate(direction d, uint8_t select);
  libqm::matrix<uint8_t> get_side(side s);
  bool is_solved();
};

#endif  // RUBICS_HPP_
