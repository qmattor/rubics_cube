// Quincy Mattor
// Copyright 2022

#include "../headers/cube.hpp"

Cube::Cube() : side_val(0), x(0), y(0), length(0), width(0) {}

Cube::Cube(uint8_t v) : side_val(v), x(0), y(0), length(0), width(0) {}

Cube::Cube(uint8_t v, double l, double w, double h)
    : side_val(v), x(0), y(0), length(l), width(w) {
  (void)h;
}

void Cube::draw(const libqm::matrix<uint16_t> &camera) {
  // ok so basically we just skew everything by the camera angle
  // aka just using the camera is a geometric transformation
  // HOWEVER, for this to work I need to translate the cube into a matrix
  (void)camera;
  glBegin(GL_QUADS);
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
  glVertex2f(this->x, this->y);
  glVertex2f(this->x + this->length, this->y);
  glVertex2f(this->x, this->y + this->width);
  glVertex2f(this->x + this->length, this->y + this->width);
  glEnd();
  // despite that, I'm going to start with a 2d view model and work from there
}
