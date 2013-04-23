#include "matrix.h"
#include <cmath>

using namespace std;

class Matrix::Impl
{
    short x, y;
    double **ptr;

 public:
    Impl();
    Impl(short m, short n);
    Impl(const Impl &a);
    ~Impl();
	Impl &operator = (const Impl &a);
    Impl &operator += (const Impl &a);
    Impl operator + (const Impl &a);
    Impl operator - (const Impl &a);
    Impl &operator -= (const Impl &a);
    Impl &operator *= (double a);
    Impl operator * (double a);
    Impl &operator /= (double a);
    Impl operator / (double a);

    short GetX() const;
    short GetY() const;
    double **GetPtr();
};

// Конструкторы и деструктор объектов класса Impl

Matrix::Impl::Impl():
    x(0), y(0), ptr(0)
{
}

Matrix::Impl::Impl(short m, short n):
    x(m), y(n)
{
    ptr=new double *[x];
    for (short i=0; i<x; ++i)
        ptr[i]=new double[y];
}

Matrix::Impl::Impl(const Matrix::Impl &a):
    x(a.x), y(a.y), ptr(0)
{
    ptr=new double *[x];
    for (short i=0; i<x; ++i)
        ptr[i]=new double[y];
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]=a.ptr[i][j];
}

Matrix::Impl::~Impl()
{
    for (short i=0; i<x; ++i)
        delete [] ptr[i];
    delete[] ptr;
}


// перечисление операторов

Matrix::Impl &Matrix::Impl::operator = (const Matrix::Impl &a)
{
    if(this==&a)
        return *this;
    for (short i=0; i<x; ++i)
        delete [] ptr[i];
    delete[] ptr;
    x=a.x;
    y=a.y;
    ptr=new double *[x];
    for (short i=0; i<x; ++i)
        ptr[i]=new double[y];
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]=a.ptr[i][j];
    return *this;
}

Matrix::Impl &Matrix::Impl::operator += (const Matrix::Impl &a)
{

    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]+=a.ptr[i][j];
    return *this;
}

Matrix::Impl Matrix::Impl::operator + (const Matrix::Impl &a)
{

    Impl r;
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            r.ptr[i][j]=ptr[i][j]+a.ptr[i][j];
    return r;
}

Matrix::Impl Matrix::Impl::operator - (const Matrix::Impl &a)
{
     Impl r;
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            r.ptr[i][j]=ptr[i][j]-a.ptr[i][j];
    return r;
}

Matrix::Impl &Matrix::Impl::operator -= (const Matrix::Impl &a)
{

    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]-=a.ptr[i][j];
    return *this;
}

Matrix::Impl &Matrix::Impl::operator *= (double a)
{
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]*=a;
    return *this;
}

Matrix::Impl Matrix::Impl::operator * (double a)
{
    Impl r;
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            r.ptr[i][j]=ptr[i][j]*a;
    return r;
}

Matrix::Impl &Matrix::Impl::operator /= (double a)
{
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            ptr[i][j]/=a;
    return *this;
}

Matrix::Impl Matrix::Impl::operator / (double a)
{
    Impl r;
    for (short i=0; i<x; ++i)
        for (short j=0; j<y; ++j)
            r.ptr[i][j]=ptr[i][j]/a;
    return r;
}


// Функции, извлекающие данные об объекте

short Matrix::Impl::GetX() const
{
    return x;
}

short Matrix::Impl::GetY() const
{
    return y;
}

double **Matrix::Impl::GetPtr()
{
    return ptr;
}

// Всякие штуки через пимпл

Matrix::Matrix():
    pimpl(0)
{
    pimpl=new Impl();
}

Matrix::Matrix(short x, short y):
    pimpl(0)
{
    pimpl=new Impl(x, y);
}

Matrix::Matrix(const Matrix &a):
    pimpl(0)
{
    pimpl=new Impl(*(a.pimpl));
}

Matrix::~Matrix()
{
    delete pimpl;
    pimpl=0;
}


Matrix &Matrix::operator = (const Matrix &a)
{
    *(this->pimpl) = *(a.pimpl);
    return *this;
}

Matrix Matrix::operator + (const Matrix &a)
{
    Matrix res(*this);
    res+=a;
    return res;
}

Matrix Matrix::operator - (const Matrix &a)
{
    Matrix res(*this);
    res-=a;
    return res;
}

Matrix &Matrix::operator += (const Matrix &a)
{
    *(this->pimpl) += *(a.pimpl);
    return *this;
}


Matrix &Matrix::operator -= (const Matrix &a)
{
    *(this->pimpl) -= *(a.pimpl);
    return *this;
}

Matrix Matrix::operator * (double a)
{
    Matrix res(*this);
    res*=a;
    return res;
}


Matrix &Matrix::operator *= (double a)
{
    *(this->pimpl)*=a;
    return *this;
}

Matrix Matrix::operator / (double a)
{
    Matrix res(*this);
    res/=a;
    return res;
}


Matrix &Matrix::operator /= (double a)
{
    *(this->pimpl)/=a;
    return *this;
}


short Matrix::GetX() const
{
    return pimpl->GetX();
}

short Matrix::GetY() const
{
    return pimpl->GetY();
}

double **Matrix::GetPtr() const
{
    return pimpl->GetPtr();
}

