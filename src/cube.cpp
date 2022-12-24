// Quincy Mattor
// Copyright 2022

#include "../headers/cube.hpp"

Tile::Tile() : side_val(0), xyz(1, 3, 0), length(0), width(0) {}

Tile::Tile(uint8_t v) : side_val(v), xyz(1, 3, 0), length(0), width(0) {}

Tile::Tile(uint8_t side, double x, double y, double z, double length,
           double width)
    : side_val(side), xyz(1, 3, 0), length(length), width(width) {
  this->xyz(0, 0) = x;
  this->xyz(0, 1) = y;
  this->xyz(0, 2) = z;
}

void Tile::draw(const libqm::matrix<double> &camera) {
  // ok so basically we just skew everything by the camera angle
  // aka just using the camera is a geometric transformation
  // HOWEVER, for this to work I need to translate the cube into a matrix
  (void)camera;
  glBegin(GL_TRIANGLES);
  switch (this->side_val % 6) {
    case 0:
      glColor3f(1, 0, 0);
      break;
    case 1:
      glColor3f(0, 1, 0);
      break;
    case 2:
      glColor3f(0, 0, 1);
      break;
    case 3:
      glColor3f(1, 1, 0);
      break;
    case 4:
      glColor3f(1, 0, 1);
      break;
    case 5:
      glColor3f(0, 1, 1);
      break;
  }
  glVertex3f(X, Y, Z);
  glVertex3f(X + this->length, Y, Z);
  glVertex3f(X, Y + this->width, Z);

  glVertex3f(X + this->length, Y, Z);
  glVertex3f(X, Y + this->width, Z);
  glVertex3f(X + this->length, Y + this->width, Z);
  glEnd();
}
