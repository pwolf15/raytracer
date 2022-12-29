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
    float threshold = 1e-5;
    for (size_t i = 0; i < rows_a; ++i)
    {
      for (size_t j = 0; j < cols_a; ++j)
      {
        if (std::abs((*this)(i,j) - b(i, j)) > threshold)
        {
          isEqual = false;
          std::cout << "i,j" << i << "," << j << std::endl;
          std::cout << (*this)(i,j) << "," << b(i,j) << std::endl;
          std::cout << "Diff: " << std::abs((*this)(i,j) - b(i, j)) << std::endl;
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

  Matrix operator* (const Matrix& b) const
  {
    std::vector<std::vector<float>> result(b.m.size());
    for (size_t i = 0; i < m.size(); ++i)
    {
      result[i].resize(b.m[0].size());
      for (size_t j = 0; j < m[0].size(); ++j)
      {
        float value = 0;
        for (size_t k = 0; k < m.size(); ++k)
        {
          value += (*this)(i,k) * b(k,j);
        }
        result[i][j] = value;
      }
    }
    Matrix c(result);
    return c;
  }

  Tuple operator* (const Tuple& b) const
  {
    std::vector<float> result((*this).m.size());
    for (int i = 0; i < (*this).m.size(); ++i)
    {
      result[i] = 0;
      result[i] += (*this).m[i][0] * b.x;
      result[i] += (*this).m[i][1] * b.y;
      result[i] += (*this).m[i][2] * b.z;
      result[i] += (*this).m[i][3] * b.w;
    }

    Tuple t(result[0], result[1], result[2], result[3]);
    return t;
  }

  Matrix transpose() const
  {
    std::vector<std::vector<float>> t_data((*this).m.size());

    for (int i = 0; i < (*this).m.size(); ++i)
    {
      t_data[i].resize((*this).m[i].size());
      for (int j = 0; j < (*this).m[i].size(); ++j)
      {
        t_data[i][j] = (*this).m[j][i];
      }
    }
    Matrix t(t_data);
    return t;
  }

  float determinant_2x2() const
  {
    const auto data = (*this).m;
    return data[0][0]*data[1][1] - data[0][1]*data[1][0];
  }

  float determinant() const
  {
    const auto data = (*this).m;
    const int rows = data.size();
    const int cols = rows;

    if (rows == 2)
    {
      return determinant_2x2();
    }
    else
    {
      float det = 0;
      for (int i = 0; i < cols; ++i)
      {
        const int row = 0;
        const int col = i;

        const auto cof = this->cofactor(row, col);
        det += data[row][col] * cof;
      }

      return det;
    }
  }
  
  Matrix submatrix(int row, int col) const
  {
    const auto data = (*this).m;
    std::vector<std::vector<float>> s(data.size() - 1);
    int sRow = 0, sCol = 0;
    for (int i = 0; i < data.size(); ++i)
    {
      if (i == row) continue;

      s[sRow].resize(data.size() - 1);
      sCol = 0;
      for (int j = 0; j < data[i].size(); ++j)
      {
        if (j == col) continue;

        s[sRow][sCol] = data[i][j];

        sCol++;
      }

      sRow++;
    }

    Matrix sMat(s);
    return sMat;
  }

  float minor(int row, int col) const
  {
    Matrix s = this->submatrix(row, col);
    return s.determinant();
  }

  float cofactor(int row, int col) const
  {
    float sign = (row + col) % 2 == 0 ? 1 : -1;
    return this->minor(row, col) * sign;
  }

  bool invertible() const
  {
    return this->determinant() != 0;
  }

  Matrix inverse() const
  {
    if (!this->invertible())
    {
      std::cout << "Failed to invert" << std::endl;
      Matrix m({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});
      return m;
    }

    const auto m_data = m;
    std::vector<std::vector<float>> data(m_data.size());
    const auto det = this->determinant();
    for (int i = 0; i < m_data.size(); ++i)
    {
      data[i].resize(m_data[i].size());
    }
    for (int i = 0; i < m_data.size(); ++i)
    {
      for (int j = 0; j < m_data[i].size(); ++j)
      {
        float c = this->cofactor(i, j);
        data[j][i] = c / det;
      }
    }

    Matrix m2(data);
    return m2;
  }


private:
  std::vector<std::vector<float>> m;
};

#endif // MATRIX_H