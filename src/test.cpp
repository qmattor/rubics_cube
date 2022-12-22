// Quincy Mattor
// Copyright 2022

#include "../headers/rubics.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Tests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Constructor) {
  rubics_cube cube;
  BOOST_CHECK_EQUAL(cube.is_solved(), true);
  cube.rotate(rubics_cube::direction::up, 0);
  BOOST_CHECK_EQUAL(cube.is_solved(), false);
  auto face = cube.get_side(rubics_cube::side::FRONT);
  std::cout << face << std::endl;
  cube.rotate(rubics_cube::direction::down, 0);
  face = cube.get_side(rubics_cube::side::FRONT);
  std::cout << face << std::endl;
}
