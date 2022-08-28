#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
  Matrix(std::vector<std::vector<float>> m): m(m)
  {
    if ((m[0].size() != m.size()))
    {
      std::cout << "Could not allocate matrix" << std::endl;
      m.clear();
    }
  }

private:
  std::vector<std::vector<float>> m;
};

#endif // MATRIX_H