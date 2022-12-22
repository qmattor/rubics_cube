// Quincy Mattor
// Copyright 2022

#include <iostream>

#include "../headers/rubics.hpp"

void init(void) { glClearColor(1.0, 1.0, 0, 1.0); }

void display(void) {
  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glVertex3f(-0.6, -0.75, 0.5);
  glVertex3f(0.6, -0.75, 0);
  glVertex3f(0, 0.75, 0);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

// void reshape(int w, int h) {

// }

// mouse x and y at time of press
void keyboard(unsigned char key, int x, int y) {
  std::cout << x << ", " << y << std::endl;
  switch (key) {}
}

int main(int argc, char **argv) {
  rubics_cube cube;
  glutInit(&argc, argv);
  // Select Pixel Format Attributes
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  // Configure Window
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  // Create the Window and Set up Rendering Context
  glutCreateWindow(argv[0]);
  // Configure Rendering Context
  init();
  // Connect callback functions that will respond to events
  glutDisplayFunc(display);
  // glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  // // Start listening for events
  glutMainLoop();
  return 0;
}
