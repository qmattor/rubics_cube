// Quincy Mattor
// Copyright 2022

#include "rubics.hpp"

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
	std::copy(start_pos.begin(), start_pos.end(), this->sides.begin());
}

void rubics_cube::rotate(direction d, uint8_t select) {
	if (select > 2)
		throw std::runtime_error("");
	switch (d) {
		case direction::up:
			break;
		case direction::down:
			break;
		case direction::left:
			break;
		case direction::right:
			break;
		default:
			throw std::runtime_error("bad direction value passed to rotate");
	}
}

libqm::matrix<uint8_t> rubics_cube::get_side(side s) {
	return *(this->sides.at(static_cast<size_t>(s)));
}

bool rubics_cube::is_solved() {
	for (auto m : this->sides)
		if (m->foreach([m](uint8_t x){return (m->at(0, 0) == x);}))
			return false;
	return true;
}
#pragma endregion
