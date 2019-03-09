#ifndef __HAEXA_H__
#define __HAEXA_H__


#include <array>
#include <cmath>
#include <iostream>


namespace haexa {


  template <typename T>
  class Hex {
  public:
    Hex(T x, T y, T z)
      : x(x)
      , y(y)
      , z(z) { }


    Hex<int> round() {
      // return the closest integer-coordinate hex
      int ix = std::round(x);
      int iy = std::round(y);
      int iz = std::round(z);
      int sum = ix + iy + iz;
      if (sum != 0) {
        double dx = fabs(x - static_cast<double>(ix));
        double dy = fabs(y - static_cast<double>(iy));
        double dz = fabs(z - static_cast<double>(iz));
        if (dx > dy && dx > dz) {
          ix = -(iy + iz);
        } else if (dy > dx && dy > dz) {
          iy = -(ix + iz);
        } else if (dz > dx && dz > dy) {
          iz = -(ix + iy);
        }
      }
      return Hex<int>(ix, iy, iz);
    }


    bool valid() {
      // check if a hex is valid (on the zero sum diagonal plane)
      return x + y + z == 0;
    }

    template <typename T2>
    friend std::ostream &operator<<(std::ostream &, Hex<T2>);

  private:
    T x, y, z;
  };


  template <typename T>
  std::ostream &operator<<(std::ostream &out, Hex<T> hex) {
    out << '(' << hex.x << ", " << hex.y << ", " << hex.z << ')';
    return out;
  }


} // end namespace haexa


#endif
