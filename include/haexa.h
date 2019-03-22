#ifndef __HAEXA_H__
#define __HAEXA_H__


#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>


namespace haexa {


  template <typename T>
  class Hex {
  public:
    Hex(T x, T y, T z)
      : x(x)
      , y(y)
      , z(z) { }


    template <typename TIntegral = int>
    Hex<TIntegral> round() {
      // return the closest integer-coordinate hex
      TIntegral ix = std::round(x);
      TIntegral iy = std::round(y);
      TIntegral iz = std::round(z);
      TIntegral sum = ix + iy + iz;
      if (sum != 0) {
        T dx = fabs(x - static_cast<T>(ix));
        T dy = fabs(y - static_cast<T>(iy));
        T dz = fabs(z - static_cast<T>(iz));
        if (dx > dy && dx > dz) {
          ix = -(iy + iz);
        } else if (dy > dz) {
          iy = -(ix + iz);
        } else {
          iz = -(ix + iy);
        }
      }
      assert(ix + iy + iz == 0);
      return Hex<TIntegral>(ix, iy, iz);
    }


    bool valid() {
      // check if a hex is valid (on the zero sum diagonal plane)
      return x + y + z == 0;
    }


    // Operator overloading
    template <typename TOther>
    Hex<T> operator+(const Hex<TOther> &other) {
      return Hex<T>(x + other.x, y + other.y, z + other.z);
    }

    Hex<T> operator+() {
      return Hex<T>(x, y, z);
    }

    template <typename TOther>
    Hex<T> operator-(const Hex<TOther> &other) {
      return Hex<T>(x - other.x, y - other.y, z - other.z);
    }

    Hex<T> operator-() {
      return Hex<T>(-x, -y, -z);
    }

    template <typename T2, typename TScalar>
    friend Hex<TScalar> operator*(const Hex<T2> &, TScalar);
    template <typename T2, typename TScalar>
    friend Hex<TScalar> operator*(TScalar, const Hex<T2> &);

    // Integral division needs a special case since simple division does not
    // guarantee correct rounding
    template <typename TScalar,
              typename std::enable_if<std::is_integral<TScalar>::value, int>::type = 0,
              typename TIntermediate = double>
    Hex<TScalar> operator/(TScalar a) {
      assert(a != 0);
      TIntermediate b = 1/static_cast<TIntermediate>(a);
      // return (Hex<TIntermediate>(x, y, z) / b).round();
      return Hex<TIntermediate>(static_cast<TIntermediate>(x)*b,
                                static_cast<TIntermediate>(y)*b,
                                static_cast<TIntermediate>(z)*b).round<TScalar>();
    }
    template <typename TScalar,
              typename std::enable_if<std::is_floating_point<TScalar>::value, int>::type = 0>
    Hex<TScalar> operator/(TScalar a) {
      assert(a != 0);
      TScalar b = 1/a;
      return Hex<TScalar>(x*b, y*b, z*b);
    }


    template <typename TOther>
    bool operator==(const Hex<TOther> &other) {
      return (x == other.x && y == other.y && z == other.z);
    }

    template <typename TOther>
    bool operator!=(const Hex<TOther> &other) {
      return !((*this) == other);
    }



    // Default printing
    template <typename T2>
    friend std::ostream &operator<<(std::ostream &, Hex<T2>);

  private:
    T x, y, z;
  };


  template <typename T, typename TScalar>
  Hex<TScalar> operator*(const Hex<T> &hex, TScalar a) {
    return Hex<TScalar>(hex.x*a, hex.y*a, hex.z*a);
  }
  template <typename T, typename TScalar>
  Hex<TScalar> operator*(TScalar a, const Hex<T> &hex) { return hex*a; }


  template <typename T>
  std::ostream &operator<<(std::ostream &out, Hex<T> hex) {
    out << '(' << hex.x << ", " << hex.y << ", " << hex.z << ')';
    return out;
  }


} // end namespace haexa


#endif
