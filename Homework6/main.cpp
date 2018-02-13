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

    for(int i=1;i<=8;++i)
    {
        for(int j=1;j<=8;++j)
        {
            std::cout<<matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<matrix.Size()<<std::endl;
    matrix.Print();
    return 0;
}