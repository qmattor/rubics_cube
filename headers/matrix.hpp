// Quincy Mattor
// Copyright 2022

#include <functional>
#include <iostream>
#include <vector>

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

namespace libqm {

template <class T>
class matrix {
 private:
  size_t y;
  size_t x;
  std::vector<T> *elements;

 public:
  matrix();  // purely for use of creating blank things to overwrite later
  matrix(size_t x, size_t y);
  matrix(size_t x, size_t y, T init);
  matrix(matrix &&other) noexcept;
  matrix(const matrix &other);
  ~matrix();
  matrix<T> &operator=(const matrix<T> &other);
  matrix<T> &operator=(matrix<T> &&other) noexcept;
  bool operator!=(const matrix<T> &);
  bool operator==(const matrix &other);
  // matrix ops
  matrix<T> operator*(const matrix<T> &other);
  matrix<T> operator+(const matrix<T> &other);
  matrix<T> operator-(const matrix<T> &other);
  // scaler ops
  matrix<T> operator*(const T &scaler);
  matrix<T> operator+(const T &scaler);
  matrix<T> operator-(const T &scaler);
  T &operator()(size_t x, size_t y);
  T operator()(size_t x, size_t y) const;
  size_t get_y();
  size_t get_x();
  size_t get_size();
  T &at(size_t x, size_t y);
  T at(size_t x, size_t y) const;

  // iterator stuff
  // just pass this stuff up
  typename std::vector<T>::iterator begin();
  typename std::vector<T>::iterator end();

  bool foreach(std::function<bool(T &)>);
  bool contains(const T ele);
  bool contains(std::function<bool(T)> func);
  T &find(T);
  template <class Z>
  friend std::istream &operator>>(std::istream &, matrix<Z> &);
  template <class Z>
  friend std::ostream &operator<<(std::ostream &, const matrix<Z> &);
};

template <class T>
matrix<T>::matrix() : y(0), x(0) {
  this->elements = nullptr;
}

template <class T>
matrix<T>::matrix(size_t x, size_t y, T init) : y(y), x(x) {
  if (y == 0 || x == 0) throw std::runtime_error("invalid initial size");
  this->elements = new std::vector<T>(y * x, init);
}

template <class T>
matrix<T>::matrix(size_t x, size_t y) : y(y), x(x) {
  if (y == 0 || x == 0) throw std::runtime_error("invalid initial size");
  this->elements = new std::vector<T>(y * x);
}

template <class T>
matrix<T>::~matrix() {
  delete this->elements;
}

template <class T>
matrix<T>::matrix(matrix &&other) noexcept {
  if (other != *this) {
    this->y = other.y;
    this->x = other.x;
    std::swap(this->elements, other.elements);
  }
}

template <class T>
matrix<T>::matrix(const matrix &other) {
  if (this != &other) {
    delete this->elements;
    this->y = other.y;
    this->x = other.x;
    this->elements = new std::vector<T>(this->y * this->x);
    // ezpz deep copy
    std::copy(other.elements->begin(), other.elements->end(),
              this->elements->begin());
  }
}

template <class T>
matrix<T> &matrix<T>::operator=(const matrix &other) {
  if (this != &other) {
    delete this->elements;
    this->y = other.y;
    this->x = other.x;
    this->elements = new std::vector<T>(this->y * this->x);
    std::copy(other.elements->begin(), other.elements->end(),
              this->elements->begin());
  }
  return *this;
}

template <class T>
matrix<T> &matrix<T>::operator=(matrix &&other) noexcept {
  if (other == *this) return *this;
  this->y = other.y;
  this->x = other.x;
  std::swap(this->elements, other.elements);
  return *this;
}

template <class T>
T &matrix<T>::operator()(size_t x, size_t y) {
  return this->elements->at(y * this->x + x);
}

template <class T>
T matrix<T>::operator()(size_t x, size_t y) const {
  return this->elements->at(y * this->x + x);
}

// const doesn't matter bc by value
template <class T>
size_t matrix<T>::get_y() {
  return this->y;
}

template <class T>
size_t matrix<T>::get_x() {
  return this->x;
}

template <class T>
size_t matrix<T>::get_size() {
  return this->elements->size();
}

template <class T>
T &matrix<T>::at(size_t x, size_t y) {
  if (y >= this->y) throw std::out_of_range("y overflow");
  if (x >= this->x) throw std::out_of_range("x overflow");
  return (*this)(x, y);
}

template <class T>
T matrix<T>::at(size_t x, size_t y) const {
  if (y >= this->y) throw std::out_of_range("y overflow");
  if (x >= this->x) throw std::out_of_range("x overflow");
  return (*this)(x, y);
}

template <class T>
bool matrix<T>::operator!=(const matrix<T> &other) {
  if (other.y != this->y) return true;
  if (other.x != this->x) return true;
  try {
    for (size_t i = 0; i < this->elements->size(); i++)
      if (this->elements->at(i) != other.elements->at(i)) return true;
  } catch (std::exception &e) {
    return true;
  }
  return false;
}

template <class T>
bool matrix<T>::operator==(const matrix &other) {
  if (other.y != this->y) return false;
  if (other.x != this->x) return false;
  try {
    for (size_t i = 0; i < this->elements->size(); i++)
      if (this->elements->at(i) != other.elements->at(i)) return false;
  } catch (std::out_of_range &e) {
    return false;
  }
  return true;
}
template <class T>
typename std::vector<T>::iterator matrix<T>::begin() {
  return elements->begin();
}
template <class T>
typename std::vector<T>::iterator matrix<T>::end() {
  return elements->end();
}

template <class T>
bool matrix<T>::contains(const T ele) {
  for (auto e : *this->elements)
    if (e == ele) return true;
  return false;
}

template <class T>
bool matrix<T>::contains(std::function<bool(T)> func) {
  for (auto e : *this->elements)
    if (func(e)) return true;
  return false;
}

template <class T>
T &matrix<T>::find(T ele) {
  for (size_t i = 0; i < this->elements->size(); i++)
    if (this->elements->at(i) == ele) return this->elements->at(i);
  throw std::runtime_error("Matrix does not contian element");
}

template <class T>
bool matrix<T>::foreach(std::function<bool(T &)> func) {
  for (size_t j = 0; j < this->y; j++)
    for (size_t i = 0; i < this->x; i++)
      if (!func(this->elements->at(j * this->x + i))) return false;
  return true;
}

template <class T>
std::istream &operator>>(std::istream &in, matrix<T> &m) {
  in >> m.x;
  in >> m.y;
  delete m.elements;
  m.elements = new std::vector<T>(m.x * m.y);
  size_t i = 0;
  while (i < (m.x * m.y)) {
    if (in.peek() == EOF)
      throw std::runtime_error("File EOF found prematurely");
    in >> m.elements->at(i++);
  }
  return in;
}

template <class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
  out << m.x << " " << m.y << "\n";
  for (size_t y = 0; y < m.y; y++) {
    for (size_t x = 0; x < m.x; x++) {
      out << m.elements->at(y * m.x + x) << ", ";
    }
    out << "\n";
  }
  return out;
}

// currently only for
// matrix cross product
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y || other.y != this->x ||
      other.x != this->y)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      size_t y1 = 0;
      T sum = (this->at(0, y) * other(x, y1++));
      for (size_t x1 = 1; x1 < this->x; x1++) {
        sum = sum + ((this->at(x1, y) * other(x, y1++)));
      }
      ret(x, y) = sum;
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator*(const T &scaler) {
  matrix<T> ret(*this);
  ret.foreach([scaler](T &ele) {
    ele *= scaler;
    return true;
  });
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      ret(x, y) = this->at(x, y) + other(x, y);
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator+(const T &scaler) {
  matrix<T> ret(*this);
  ret.foreach([scaler](T &ele) {
    ele += scaler;
    return true;
  });
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator-(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      ret(x, y) = this->at(x, y) - other(x, y);
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator-(const T &scaler) {
  matrix<T> ret(*this);
  ret.foreach([scaler](T &ele) {
    ele -= scaler;
    return true;
  });
  return ret;
}

}  // namespace libqm
#endif  // MATRIX_HPP_
