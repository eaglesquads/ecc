#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <gmp.h>
#include "block.hpp"
#include "point.hpp"
#include "assert.h"

class Point;

class Scalar : public Block64 {
private:
  mpz_t element;
  static mpz_t modulus;
  static bool init;

public:
  Scalar ();
  ~Scalar ();
  void frombytes(const unsigned char in[64]);
  void tobytes(unsigned char out[64]);
  void fromint(const int in);

  void fromrandom();
  void print();

  void operator=(const Scalar& rhs);

  friend Scalar invert(Scalar& a);

  friend Scalar operator+(const Scalar& a, const Scalar& b);
  friend Scalar operator*(const Scalar& a, const Scalar& b);
  friend bool operator==(const Scalar& a, const Scalar& b);
  friend void scalarmult(Point& q, Scalar& d, Point& p);
};

#endif //SCALAR_HPP
