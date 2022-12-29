#include <iostream>
#include <Matrix.h>

int main()
{
  std::cout << "Hello world!" << std::endl;
  Matrix m({
    {1,2,3},
    {4,5,6},
    {7,8,9}
  });
  std::cout << "Matrix: " << m << std::endl;
  Tuple t({
    1,2,3,4
  });
  std::cout << "Tuple: " << t << std::endl;
  return 0;
}