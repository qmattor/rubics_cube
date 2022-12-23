// Quincy Mattor
// Copyright 2022

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif
#include "./libqm.hpp"
#ifndef CUBE_HPP_
#define CUBE_HPP_

class Cube {
 private:
  uint8_t side_val;
  double x;
  double y;
  // double z;
  double length;
  double width;
  // double height;

 public:
  Cube();
  explicit Cube(uint8_t);
  Cube(uint8_t, double, double, double);
  // uuuhhhhhggggg
  uint8_t get_sideval() { return this->side_val; }
  double get_x() { return this->x; }
  double get_y() { return this->y; }
  double get_l() { return this->length; }
  double get_w() { return this->width; }
  void set_sideval(uint8_t v) { this->side_val = v; }
  void set_x(double x) { this->x = x; }
  void set_y(double y) { this->y = y; }
  void set_l(double l) { this->length = l; }
  void set_w(double w) { this->width = w; }
  // double get_z() { return this->z; }
  // void set_z(double z) { this->z = z; }
  // double get_h() { return this->height; }
  // void set_h(double h) { this->height = h; }

  bool operator==(const Cube &other) {
    return this->side_val == other.side_val;
  }
  bool operator!=(const Cube &other) {
    return this->side_val != other.side_val;
  }

  void draw(const libqm::matrix<uint16_t> &camera);
};

#endif  // CUBE_HPP_
