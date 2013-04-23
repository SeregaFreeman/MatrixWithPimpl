#include <iostream>
#include "matrix.h"

using namespace std;

class ConsoleOutputMatrix: public Matrix // наследует public Matrix
{
public:
    ConsoleOutputMatrix();
    ConsoleOutputMatrix(short x, short y);
    ConsoleOutputMatrix(const ConsoleOutputMatrix &a); // конструктор копирования
    ~ConsoleOutputMatrix();
    ConsoleOutputMatrix &operator = (const ConsoleOutputMatrix &a); // присваивание
    ConsoleOutputMatrix &operator = (const Matrix &a); // ещё одно присваивание
    friend istream &operator >> (istream &in, const ConsoleOutputMatrix &org);
    friend ostream &operator << (ostream &out, const ConsoleOutputMatrix &org);
};

// Конструкторы и деструктор

ConsoleOutputMatrix::ConsoleOutputMatrix():
    Matrix()
{
}

ConsoleOutputMatrix::ConsoleOutputMatrix(short x, short y):
    Matrix(x,y)
{
}

ConsoleOutputMatrix::ConsoleOutputMatrix(const ConsoleOutputMatrix &a):
    Matrix(a)
{
}

ConsoleOutputMatrix::~ConsoleOutputMatrix()
{
}

// Операторы присваивания

ConsoleOutputMatrix &ConsoleOutputMatrix::operator = (const ConsoleOutputMatrix &a)
{

    Matrix::operator=(a);
    return *this;
}

ConsoleOutputMatrix &ConsoleOutputMatrix::operator = (const Matrix &a)
{

    Matrix::operator=(a);
    return *this;
}

// Операторы ввода-вывода

istream &operator >> (istream &input, const ConsoleOutputMatrix &org)
{
    short x=org.GetX(); // получаем х из приватного класса implementation
    short y=org.GetY(); // y
    double **ptr=org.GetPtr(); // получаем сам указатель, задающий матрицу
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            input>>ptr[i][j];
    return input;
}

ostream &operator << (ostream &output, const ConsoleOutputMatrix &org)
{
    short x=org.GetX();
    short y=org.GetY();
    double **ptr=org.GetPtr();
    for (short i=0; i<x; ++i)
    {
        for (short j=0; j<y; ++j)
        {
            output.width(5);
            output<<ptr[i][j];
        }
        output<<endl;
    }
    return output;
}

int main()
{
    //тут чисто для просмотра все написано, без оформления и менюшек
    ConsoleOutputMatrix m(3,3), n(3,3), temp(3,3);
    cout<<"Введите матрицу а"<<endl;
    cin>>m;
    cout<<"Введите матрицу b"<<endl;
    cin>>n;
    temp=m+n;
    cout<<endl;
    cout<<temp;
    temp=m-n;
    cout<<endl;
    cout<<temp;
    cout<<endl<<"Матрица, умноженная на 5"<<endl;
    temp=m*5;
    cout<<temp;
    cout<<endl<<"Матрица, разделенная на 6"<<endl;
    temp=m/6;
    cout<<temp;

    return 0;
}
