// Quincy Mattor
// Copyright 2022

#include "./rubics.hpp"

// so the plan is to learn open gl, and make a rubics
// cube simulation at the same time. The logic should
// be easy enough as it's just a bit of matrix manipulation

#pragma region Private

#pragma endregion

#pragma region Public
rubics_cube::rubics_cube() {
  for (uint8_t i = 0; i < 6; i++) {
    this->sides.push_back(new libqm::matrix<uint8_t>(3, 3, i));
  }
}

rubics_cube::rubics_cube(std::vector<libqm::matrix<uint8_t> *> &start_pos) {
  for (auto m : start_pos)
    if (m->get_x() != 2 && m->get_y() != 2)
      throw std::runtime_error("invlaid matrix passed");
  std::copy(start_pos.begin(), start_pos.end(), this->sides.begin());
}


// todo:
void rubics_cube::rotate(direction d, uint8_t select) {
  if (select > 2)  // should make this dynamic so can have large cubes
    throw std::out_of_range("select value out of range");
  uint8_t tiles[3];
  // this technically works, but it's kinda gross
  switch (d) {
    // it copies backwards so it doesn't have to keep copying to tiles
    case direction::up: {
      for (int i = 0; i < 3; i++) {
        tiles[i] = this->sides.at(
          static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BOTTOM))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BOTTOM))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BACK))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::TOP))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::TOP))->at(select, i) =
          tiles[i];
      }
    }
    break;
    case direction::down: {
     for (int i = 0; i < 3; i++) {
        tiles[i] = this->sides.at(
          static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::TOP))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::TOP))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BACK))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BOTTOM))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BOTTOM))->at(select, i) =
          tiles[i];
      }
    }
    break;
    case direction::left: {
      for (int i = 0; i < 3; i++) {
        tiles[i] = this->sides.at(
          static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::RIGHT))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::RIGHT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BACK))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::LEFT))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::LEFT))->at(select, i) =
          tiles[i];
      }
    }
    break;
    case direction::right: {
       for (int i = 0; i < 3; i++) {
        tiles[i] = this->sides.at(
          static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::LEFT))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::LEFT))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::BACK))->at(select, i) =
          this->sides.at(static_cast<size_t>(side::RIGHT))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides.at(static_cast<size_t>(side::RIGHT))->at(select, i) =
          tiles[i];
      }
    }
    break;
    default:
      throw std::runtime_error("bad direction passed to rotate");
  }
}

libqm::matrix<uint8_t> rubics_cube::get_side(side s) {
  libqm::matrix<uint8_t> tmp;
  tmp = *(this->sides.at(static_cast<size_t>(s)));
  return tmp;
}

bool rubics_cube::is_solved() {
  for (auto m : this->sides)
    if (!m->foreach([m](uint8_t x){ return (m->at(0, 0) == x); }))
      return false;
  return true;
}
#pragma endregion
