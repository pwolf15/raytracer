#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

class Tuple
{
public:
  Tuple(double x, double y, double z, double w):
    x(x), y(y), z(z), w(w)
  {}

  bool isPoint()
  {
    return w == 1.0;
  }

  bool isVector()
  {
    return w == 0.0;
  }

  bool operator==(Tuple const& rhs) const
  {
    double th = 1e-5;
    bool equal = 
      (abs(x - rhs.x) < th) && 
      (abs(y - rhs.y) < th) &&
      (abs(z - rhs.z) < th) && 
      (abs(w - rhs.w) < th);
    return equal;
  }

  bool operator!=(Tuple const& rhs) const
  {
    return !(*this == rhs);
  }

  Tuple operator-() const
  {
    Tuple t(-this->x, -this->y, -this->z, -this->w);
    return t;
  }

  friend Tuple operator+(Tuple lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Tuple& rhs) // otherwise, both parameters may be const references
  {
    Tuple result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    return result;
  }

  friend Tuple operator-(Tuple lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Tuple& rhs) // otherwise, both parameters may be const references
  {
    Tuple result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return result;
  }

  friend Tuple operator*(Tuple lhs, double s)
  {
    Tuple result(lhs.x * s, lhs.y * s, lhs.z * s, lhs.w * s);
    return result;
  }

  friend Tuple operator/(Tuple lhs, double s)
  {
    Tuple result(lhs.x / s, lhs.y / s, lhs.z / s, lhs.w / s);
    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const Tuple &t)
  {
    std::string tmp = "\n";
    tmp += "[";
    tmp += fmt::format("{:03.5f}", t.x) + ",";
    tmp += fmt::format("{:03.5f}", t.y) + ",";
    tmp += fmt::format("{:03.5f}", t.z) + ",";
    tmp += fmt::format("{:03.5f}", t.w) + "]\n";

    os << tmp;
    return os;
  }

  double x, y, z, w;

};

#endif