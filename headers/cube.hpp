// Quincy Mattor
// Copyright 2022

#include "./libqm.hpp"

#ifndef CUBE_HPP_
#define CUBE_HPP_
// this is just for drawing purposes
class Cube {
 private:
  double length;
  double width;
  double height;

 public:
  Cube();
  Cube(double, double, double);
  void draw(libqm::matrix<uint16_t> camera);
};

#endif  // CUBE_HPP_
