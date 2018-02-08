#include "matrix.h"

template <typename T, int N, T default_value>
std::ostream& operator<<(std::ostream& os, MatrixElement<T,1,N,default_value>& element)
{
    os<<element.Value();
    return os;
}

int main()
{
    Matrix<int,2,0> matrix;
    for(int i=0;i<10;++i)
    {
        matrix[i][i]=i;
        matrix[i][9-i]=9-i;
    }

    matrix.PrintFragment(1,1,8,8);
    std::cout<<matrix.Size()<<std::endl;
    matrix.Print();
    return 0;
}