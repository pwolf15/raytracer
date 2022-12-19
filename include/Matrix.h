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

  double operator () (int i, int j) const
  {
    return m[i][j];
  }

  bool operator== (const Matrix &b) const
  {
    size_t rows_a = m.size();
    size_t rows_b = b.m.size();
    if (!rows_a || !rows_b) return false;
    size_t cols_a = m[0].size();
    size_t cols_b = b.m[0].size();
    if (!cols_a || !cols_b) return false;
    if ((rows_a != rows_b) || (cols_a != cols_b)) return false;

    bool isEqual = true;
    for (size_t i = 0; i < rows_a; ++i)
    {
      for (size_t j = 0; j < cols_a; ++j)
      {
        if ((*this)(i,j) != b(i, j))
        {
          isEqual = false;
          break;
        }
      }

      if (!isEqual)
      {
        break;
      }
    }

    return isEqual;
  }

  bool operator!= (const Matrix &b) const
  {
    return !this->operator==(b);
  }
  
private:
  std::vector<std::vector<float>> m;
};

#endif // MATRIX_H