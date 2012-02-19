
#ifndef SLG_MATH_HPP
#define SLG_MATH_HPP

#include <cmath>

namespace slg {
  
  const double PI = 3.1415926535897932;
  const double EPSILON = 0.0000001;
  
  inline double degToRad(double angle)
  {
    return (PI / 180.0) * angle;
  }
  
  template <typename T>
  inline bool equal(T const& a, T const& b)
  {
    return std::abs(a - b) < EPSILON;
  }
  
}

#endif