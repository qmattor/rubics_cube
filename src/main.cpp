// Quincy Mattor
// Copyright 2022

#include <iostream>

#include "../headers/rubics.hpp"

// Ok so if I just treat the whole program like an object
// then global context would effectively just be an object
// variable. Now that I'm saying it, I don't really see
// why globals are so hated.

int window_id;
rubics_cube *cube;

void init(void) {}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  cube->display();
  glFlush();
  glutSwapBuffers();
}

// mouse x and y at time of press
void keyboard(unsigned char key, int x, int y) {
  std::cout << x << ", " << y << std::endl;
  switch (key) {
    case 27:
      glutDestroyWindow(window_id);
      exit(0);
      break;
    case 'a':
      cube->rotate(rubics_cube::direction::left, 0);
      break;
    case 's':
      cube->rotate(rubics_cube::direction::down, 0);
      break;
    case 'd':
      cube->rotate(rubics_cube::direction::right, 0);
      break;
    case 'w':
      cube->rotate(rubics_cube::direction::up, 0);
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  cube = new rubics_cube();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(100, 100);
  window_id = glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
