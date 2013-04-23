#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
    class Impl; // класс с реализацией функций класса Matrix
    Impl *pimpl; // указатель на класс с реализацией

  public:
    Matrix();
    Matrix(short x, short y);
    Matrix(const Matrix&a);
    ~Matrix();
    Matrix &operator = (const Matrix &a);
    Matrix operator + (const Matrix &a);
    Matrix &operator += (const Matrix &a);
    Matrix operator - (const Matrix &a);
    Matrix &operator -= (const Matrix &a);
    Matrix operator * (double a);
    Matrix &operator *= (double a);
    Matrix &operator /= (double a);
    Matrix operator / (double a);

  protected:
    short GetX() const; // функции для получения приватных данных
    short GetY() const;
    double **GetPtr() const;
};

#endif

