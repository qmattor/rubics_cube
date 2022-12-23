// Quincy Mattor
// Copyright 2022

#include "../headers/rubics.hpp"

// so the plan is to learn open gl, and make a rubics
// cube simulation at the same time. The logic should
// be easy enough as it's just a bit of matrix manipulation

#pragma region Private

#pragma endregion

#pragma region Public
rubics_cube::rubics_cube() {
  for (uint8_t i = 0; i < 6; i++) {
    this->sides.push_back(new libqm::matrix<storage_type>(3, 3));
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        this->sides.back()->at(x, y).set_sideval(i);
        this->sides.back()->at(x, y).set_l(.1);
        this->sides.back()->at(x, y).set_w(.1);
        this->sides.back()->at(x, y).set_x(x / 5.f);
        this->sides.back()->at(x, y).set_y(y / 5.f);
      }
    }
  }
}

rubics_cube::rubics_cube(
    std::vector<libqm::matrix<storage_type> *> &start_pos) {
  for (auto m : start_pos)
    if (m->get_x() != 2 && m->get_y() != 2)
      throw std::runtime_error("invlaid matrix passed");
  std::copy(start_pos.begin(), start_pos.end(), this->sides.begin());
}

// todo: make this less of a shit show?
void rubics_cube::rotate(direction d, uint8_t select) {
  if (select > 2)  // should make this dynamic so can have large cubes
    throw std::out_of_range("select value out of range");
  storage_type tiles[3];
  // this technically works, but it's kinda gross
  switch (d) {
    // it copies backwards so it doesn't have to keep copying to tiles
    case direction::up: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i);
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
    } break;
    case direction::down: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i);
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
    } break;
    case direction::left: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i);
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
    } break;
    case direction::right: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides.at(static_cast<size_t>(side::FRONT))->at(select, i);
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
    } break;
    default:
      throw std::runtime_error("bad direction passed to rotate");
  }
}

libqm::matrix<storage_type> rubics_cube::get_side(side s) {
  libqm::matrix<storage_type> tmp;
  tmp = *(this->sides.at(static_cast<size_t>(s)));
  return tmp;
}

bool rubics_cube::is_solved() {
  for (auto m : this->sides)
    if (!m->foreach([m](storage_type x) {
          return (m->at(0, 0).get_sideval() == x.get_sideval());
        }))
      return false;
  return true;
}

void rubics_cube::display() {
  libqm::matrix<uint16_t> x(1, 1);
  for (auto c : (*this->sides.at(static_cast<size_t>(side::FRONT)))) c.draw(x);
}
#pragma endregion
