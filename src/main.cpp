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
libqm::matrix<double> *camera;

void init(void) {}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  cube->display(*camera);
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
    case 'A':
    case 'a':
      cube->rotate(rubics_cube::direction::left, (key == 'A') * 2);
      break;
    case 'S':
    case 's':
      cube->rotate(rubics_cube::direction::down, (key == 'S') * 2);
      break;
    case 'D':
    case 'd':
      cube->rotate(rubics_cube::direction::right, (key == 'D') * 2);
      break;
    case 'W':
    case 'w':
      cube->rotate(rubics_cube::direction::up, (key == 'W') * 2);
      break;
  }
  glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y) {
  std::cout << key << " released " << x << ", " << y << std::endl;
  switch (key) {
    default:
      break;
  }
}

void mouse_func(int button, int state, int x, int y) {
  (void)state;
  switch (button) {
    case GLUT_LEFT_BUTTON:
      break;
    case GLUT_RIGHT_BUTTON:
      break;
    case GLUT_MIDDLE_BUTTON:
      break;
    default:
      break;
  }
  std::cout << "in mouse func " << x << ", " << y << std::endl;
}

int main(int argc, char **argv) {
  camera = new libqm::matrix<double>(3, 3, 0);
  camera->at(0, 0) = 1;
  camera->at(1, 1) = 1;
  camera->at(2, 2) = 1;
  cube = new rubics_cube();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(100, 100);
  window_id = glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyReleased);
  glutMouseFunc(mouse_func);
  glutMainLoop();
  delete cube;
  delete camera;
  return 0;
}
