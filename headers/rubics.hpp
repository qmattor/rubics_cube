// Quincy Mattor
// Copyright 2022

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "./libqm.hpp"

#ifndef RUBICS_HPP_
#define RUBICS_HPP_

#define storage_type uint16_t

class rubics_cube {
 private:
  std::vector<libqm::matrix<storage_type> *> sides;

 public:
  enum class direction : char { up = 0, down, left, right };
  enum class side : char { TOP = 0, BOTTOM, LEFT, RIGHT, BACK, FRONT };
  rubics_cube();
  explicit rubics_cube(std::vector<libqm::matrix<storage_type> *> &start_pos);
  void rotate(direction d, storage_type select);
  libqm::matrix<storage_type> get_side(side s);
  bool is_solved();
  void display();
};

#endif  // RUBICS_HPP_
