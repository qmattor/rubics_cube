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

#define X this->xyz.at(0, 0)
#define Y this->xyz.at(0, 1)
#define Z this->xyz.at(0, 2)

class Tile {
 private:
  uint8_t side_val;
  libqm::matrix<double> xyz;
  double length;
  double width;

 public:
  Tile();
  explicit Tile(uint8_t);
  Tile(uint8_t side, double x, double y, double z, double length,
       double width);
  // uuuhhhhhggggg
  uint8_t get_sideval() const { return this->side_val; }
  double get_x() const { return this->xyz.at(0, 0); }
  double get_y() const { return this->xyz.at(0, 1); }
  double get_l() const { return this->length; }
  double get_w() const { return this->width; }
  double get_z() const { return this->xyz.at(0, 2); }
  void set_sideval(uint8_t v) { this->side_val = v; }
  void set_x(double x) { this->xyz.at(0, 0) = x; }
  void set_y(double y) { this->xyz.at(0, 1) = y; }
  void set_l(double l) { this->length = l; }
  void set_w(double w) { this->width = w; }
  void set_z(double z) { this->xyz.at(0, 2) = z; }

  bool operator==(const Tile &other) {
    return this->side_val == other.side_val;
  }
  bool operator!=(const Tile &other) {
    return this->side_val != other.side_val;
  }

  void draw(const libqm::matrix<double> &camera);
};

#endif  // CUBE_HPP_
