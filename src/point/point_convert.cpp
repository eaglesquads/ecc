#include "point.hpp"
#include "scalar.hpp"

void Point::frombytes(const unsigned char inx[64], const unsigned char iny[64]){
  x.frombytes(inx);
  y.frombytes(iny);
}
void Point::frombytes(const unsigned char inxy[128]){
  x.frombytes(inxy);
  y.frombytes(inxy+64);
}

void Point::tobytes(unsigned char out[64]){
  x.tobytes(out);
  y.tobytes(out+64);
}

Scalar Point::toscalar(){
  Scalar result;
  unsigned char tmp[64];
  frombytes(tmp);
  result.frombytes(tmp);
  return result;
}

void Point::operator=(const Point& rhs){
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
}

bool equal(Point& P, Point& Q){
  bool b1, b2;
  b1 = P.x == Q.x;
  b2 = P.y == Q.y;
  return !(b1|b2);
}
