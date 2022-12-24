// Quincy Mattor
// Copyright 2022

#include "../headers/rubics.hpp"

// so the plan is to learn open gl, and make a rubics
// cube simulation at the same time. The logic should
// be easy enough as it's just a bit of matrix manipulation

#pragma region Private

#pragma endregion

#pragma region Public

rubics_cube::~rubics_cube() {
  for (auto s : *this->sides) {
    for (auto i : *s) delete i;
    delete s;
  }
  delete this->sides;
}

rubics_cube::rubics_cube() : sides() {
  this->sides = new std::vector<libqm::matrix<storage_type *> *>(6);
  // top
  for (size_t i = 0; i < 6; i++)
    this->sides->at(i) = new libqm::matrix<Tile *>(3, 3);
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::TOP))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::TOP), x / 5.f, .3, y / 5.f, .2, .2);
    }
  }
  // BOTTOM
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::BOTTOM))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::BOTTOM), x / 5.f, -.3, y / 5.f, .2, .2);
    }
  }
  // LEFT
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::LEFT))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::LEFT), -.3, x / 5.f, y / 5.f, .2, .2);
    }
  }
  // RIGHT
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::RIGHT))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::RIGHT), .3, x / 5.f, y / 5.f, .2, .2);
    }
  }
  // BACK
  // this->sides->push_back(back);
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::BACK))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::BACK), x / 5.f, y / 5.f, -.3, .2, .2);
    }
  }
  // FRONT
  // this->sides->push_back(front);
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      this->sides->at(static_cast<uint8_t>(side::FRONT))->at(x, y) = new Tile(
          static_cast<uint8_t>(side::FRONT), x / 5.f, y / 5.f, -.3, .2, .2);
    }
  }
}

rubics_cube::rubics_cube(
    std::vector<libqm::matrix<storage_type *> *> &start_pos) {
  for (auto m : start_pos)
    if (m->get_x() != 3 && m->get_y() != 3)
      throw std::runtime_error("invlaid matrix passed");
  std::copy(start_pos.begin(), start_pos.end(), this->sides->begin());
}

// todo: make this less of a shit show?
void rubics_cube::rotate(direction d, uint8_t select) {
  if (select > 2)  // should make this dynamic so can have large cubes
    throw std::out_of_range("select value out of range");
  storage_type *tiles[3];
  // this technically works, but it's kinda gross
  switch (d) {
    // it copies backwards so it doesn't have to keep copying to tiles
    case direction::up: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides->at(static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides->at(static_cast<size_t>(side::FRONT))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::BOTTOM))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BOTTOM))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BACK))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::TOP))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::TOP))->at(select, i) =
            tiles[i];
      }
    } break;
    case direction::down: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides->at(static_cast<size_t>(side::FRONT))->at(select, i);
        this->sides->at(static_cast<size_t>(side::FRONT))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::TOP))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::TOP))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::BACK))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BACK))->at(select, i) =
            this->sides->at(static_cast<size_t>(side::BOTTOM))->at(select, i);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BOTTOM))->at(select, i) =
            tiles[i];
      }
    } break;
    case direction::left: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides->at(static_cast<size_t>(side::FRONT))->at(i, select);
        this->sides->at(static_cast<size_t>(side::FRONT))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::RIGHT))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::RIGHT))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::BACK))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BACK))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::LEFT))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::LEFT))->at(i, select) =
            tiles[i];
      }
    } break;
    case direction::right: {
      for (int i = 0; i < 3; i++) {
        tiles[i] =
            this->sides->at(static_cast<size_t>(side::FRONT))->at(i, select);
        this->sides->at(static_cast<size_t>(side::FRONT))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::LEFT))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::LEFT))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::BACK))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::BACK))->at(i, select) =
            this->sides->at(static_cast<size_t>(side::RIGHT))->at(i, select);
      }
      for (int i = 0; i < 3; i++) {
        this->sides->at(static_cast<size_t>(side::RIGHT))->at(i, select) =
            tiles[i];
      }
    } break;
    default:
      throw std::runtime_error("bad direction passed to rotate");
  }
}

libqm::matrix<storage_type *> rubics_cube::get_side(side s) {
  return *this->sides->at(static_cast<size_t>(s));
}

bool rubics_cube::is_solved() {
  for (auto m : *this->sides)
    if (!m->foreach([m](storage_type *x) {
          return (m->at(0, 0)->get_sideval() == x->get_sideval());
        }))
      return false;
  return true;
}

void rubics_cube::display(const libqm::matrix<double> &camera) {
  for (auto f : *this->sides)
    for (auto c : *f) c->draw(camera);
}

#pragma endregion
