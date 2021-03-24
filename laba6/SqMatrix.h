#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#define EPS 0.000001

class TeX_convertible
{
public:
    virtual std::string convert() const = 0;
};

class SqMatrix : public TeX_convertible
{
private:
    double** Mat;
    unsigned int size;

public:
    SqMatrix()
    {
        size = 0;
        Mat = nullptr;
    }

    explicit SqMatrix(unsigned int inSize)
    {
        size = inSize;
        Mat = new double*[inSize];
        for (int i = 0; i < inSize; i++)
        {
            Mat[i] = new double [inSize];
            for (int j = 0; j < inSize; j++)
                Mat[i][j] = 0;
        }
    }

    SqMatrix(const SqMatrix& Matrix)
    {
        size = Matrix.size;
        Mat = new double*[Matrix.size];
        for (int i = 0; i < Matrix.size; i++)
        {
            Mat[i] = new double[Matrix.size];
            for (int j = 0; j < Matrix.size; j++)
                Mat[i][j] = Matrix.Mat[i][j];
        }
    }

    unsigned int getSize()
    {
        return size;
    }

    ~SqMatrix()
    {
        if (Mat)
            for (int i = 0; i < size; i++ )
                delete []Mat[i];

        delete []Mat;
    }


    bool operator==(const SqMatrix& Matrix)
    {
        for (int i = 0; i < Matrix.size; i++)
        {
            for (int j = 0; j < Matrix.size; j++)
            {
                if (fabs(Mat[i][j] - Matrix.Mat[i][j]) > EPS)
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const SqMatrix& Matrix)
    {
        return !(*this == Matrix);
    }

    SqMatrix operator=(const SqMatrix& originalMatrix)
    {
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
                delete[] Mat[i];
            delete[] Mat;
        }
        size = originalMatrix.size;

        Mat = new double*[size];
        for (int i = 0; i < size; i++)
        {
            Mat[i] = new double[size];
            for (int j = 0; j < size; j++)
                Mat[i][j] = originalMatrix.Mat[i][j];
        }
        return *this;
    }


    SqMatrix& operator+=(const SqMatrix& firstMatrix)
    {
        if (firstMatrix.size != size)
            throw std::invalid_argument("Different size!");
        for (int i = 0; i < firstMatrix.size; i++)
            for (int j = 0; j < firstMatrix.size; j++)
                Mat[i][j] += firstMatrix.Mat[i][j];

        return *this;
    }


    SqMatrix operator+(SqMatrix& Matrix)
    {
        return *this += Matrix;
    }

    friend std::istream& operator>>(std::istream &in, SqMatrix& Matrix)
    {
        if (Matrix.size > 0)
        {
            for (int i = 0; i < Matrix.size; i++)
                delete[] Matrix.Mat[i];
            delete[] Matrix.Mat;
        }

        in >> Matrix.size;

        Matrix.Mat = new double*[Matrix.size];
        for (int i = 0; i < Matrix.size; i++)
        {
            Matrix.Mat[i] = new double[Matrix.size];
            for (int j = 0; j < Matrix.size; j++)
                in >> Matrix.Mat[i][j];
        }

        return in;

    }

    friend std::ostream &operator<<(std::ostream &out, const SqMatrix& Matrix)
    {
        for (int i = 0; i < Matrix.size; ++i)
        {
            for (int j = 0; j < Matrix.size; ++j)
            {
                out << Matrix.Mat[i][j] << ' ';
            }
            out << std::endl;
        }
        return out;
    }

    SqMatrix& operator-=(const SqMatrix& firstMatrix)
    {
        if (firstMatrix.size != size)
            throw std::invalid_argument("Different size!");
        for (int i = 0; i < firstMatrix.size; i++)
            for (int j = 0; j < firstMatrix.size; j++)
                Mat[i][j] -= firstMatrix.Mat[i][j];

        return *this;
    }


    SqMatrix operator-(SqMatrix& Matrix)
    {
        return *this -= Matrix;
    }

    SqMatrix& operator*=(const SqMatrix& firstMatrix)
    {
        SqMatrix result(size);
        if (firstMatrix.size != size)
            throw std::invalid_argument("Different size!");

        for(int i = 0; i < firstMatrix.size; i++)
        {
            for (int j = 0; j < firstMatrix.size; j++)
            {
                result.Mat[i][j] = 0;
                for (int k = 0; k < firstMatrix.size; k++)
                    result.Mat[i][j] += Mat[i][k] * firstMatrix.Mat[k][j];
            }
        }
        *this = result;
        return *this;
    }


    SqMatrix operator*(const SqMatrix& rightMatrix) const
    {
        return SqMatrix(*this) *= rightMatrix;
    }

    SqMatrix operator*(SqMatrix& Matrix)
    {
        return *this *= Matrix;
    }


    SqMatrix& operator*=(double num)
    {
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                this->Mat[i][j] *= num;
        return *this;
    }

    SqMatrix& operator*(double num)
    {
        return *this *= num;
    }

    friend SqMatrix operator*(double num, SqMatrix& Matrix)
    {
        for(int i = 0; i < Matrix.size; i++)
            for(int j = 0; j < Matrix.size; j++)
                Matrix.Mat[i][j] *= num;

        return Matrix;
    }

    double* operator[](int x)
    {
        return Mat[x];
    }


    friend double Determinant(const SqMatrix Matrix);
    friend double Trace(SqMatrix& Matrix);
    friend SqMatrix Transpose(SqMatrix& Matrix);
    friend SqMatrix Inverse(SqMatrix& tmp);
    friend SqMatrix MatPow(const SqMatrix& Matrix, int pow);
    friend SqMatrix MatExp( SqMatrix& Matrix, int pow);

    friend SqMatrix MatFromString(std::string& str);

    virtual std::string convert() const
    {
        std::string result = "\\begin{pmatrix}\n";
        for (int row = 0; row < size; ++row)
        {
            for (int col = 0; col < size; ++col)
            {
                result += std::to_string(Mat[row][col]);
                if (col != size - 1)
                    result += " & ";
            }
            if (row != size - 1)
                result += " \\\\";
            result += "\n";
        }
        result += "\\end{pmatrix}";

        return result;
    }
};

double Determinant(const SqMatrix Matrix)
{
    double det = 1;

    if (Matrix.size == 1)
        return Matrix.Mat[0][0];

    else if (Matrix.size == 2)
    {
        return Matrix.Mat[0][0] * Matrix.Mat[1][1] - Matrix.Mat[0][1] * Matrix.Mat[1][0];
    }
    for (int i = 0; i < Matrix.size; ++i)
    {
        int k = i;
        for (int j = i + 1; j < Matrix.size; ++j)
            if (std::abs (Matrix.Mat[j][i]) > std::abs (Matrix.Mat[k][i]))
                k = j;
        if (std::abs (Matrix.Mat[k][i]) < EPS)
        {
            det = 0;
            break;
        }
        std::swap (Matrix.Mat[i], Matrix.Mat[k]);
        if (i != k)
            det = -det;
        det *= Matrix.Mat[i][i];
        for (int j = i + 1; j < Matrix.size; ++j)
            Matrix.Mat[i][j] /= Matrix.Mat[i][i];
        for (int j = 0; j < Matrix.size; ++j)
            if (j != i && std::abs (Matrix.Mat[j][i]) > EPS)
                for (int k = i + 1; k < Matrix.size; ++k)
                    Matrix.Mat[j][k] -= Matrix.Mat[i][k] * Matrix.Mat[j][i];
    }
    return det;
}

double Trace(SqMatrix& Matrix)
{
    double res = 0;
    for(int i = 0; i < Matrix.size; i++)
        res += Matrix[i][i];
    return res;
}

SqMatrix Transpose(SqMatrix& Matrix)
{
    SqMatrix tmp(Matrix.size);
    for(int i = 0; i < Matrix.size; i++)
        for(int j = 0; j < Matrix.size; j++)
            tmp.Mat[i][j] = Matrix.Mat[j][i];
    return tmp;
}

SqMatrix Inverse(SqMatrix& Matrix)
{
    if (Determinant(Matrix) == 0)
    {
        throw std::invalid_argument("Inverse matrix doesn't exist!");
    }

    unsigned int size = Matrix.size;
    float tmpMat[size][2 * size];
    double temp;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 2 * size; j++)
        {
            if (j < size)
                tmpMat[i][j] = Matrix[i][j];
            else if (j == (i + size))
                tmpMat[i][j] = 1;
            else
                tmpMat[i][j] = 0;
        }
    }

    for (int i = size - 1; i > 0; i--)
    {
        if (tmpMat[i - 1][0] < tmpMat[i][0])
        {
            for (int j = 0; j < 2 * size; ++j)
            {
                temp = tmpMat[i][j];
                tmpMat[i][j] = tmpMat[i - 1][j];
                tmpMat[i - 1][j] = temp;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <  size; j++)
        {
            if (j != i)
            {
                temp = tmpMat[j][i] / tmpMat[i][i];
                for (int k = 0; k < 2 * size; k++)
                {
                    tmpMat[j][k] -= tmpMat[i][k] * temp;
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        temp = tmpMat[i][i];
        for (int j = 0; j < 2 * size; j++)
        {
            tmpMat[i][j] = tmpMat[i][j] / temp;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Matrix.Mat[i][j] = tmpMat[i][j + size];
        }
    }
    return Matrix;
}

long int fact(int n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    else
        return n * fact(n - 1);
}

SqMatrix MatPow(const SqMatrix& Matrix, int pow)
{
    SqMatrix res(Matrix);
    while (pow - 1)
    {
        res *= Matrix;
        pow--;
    }
    return res;
}

SqMatrix MatExp(SqMatrix& Matrix, int pow)
{
    if (pow < 0)
        throw std::invalid_argument("Power must be greater than 0!");
    SqMatrix res(Matrix.size);
    unsigned int k = 0;
    for (int i = 0; i < res.size; i++)
        res.Mat[i][i] = 1;

    while (k++ < pow)
    {
        double tmp = 1.0 / double(fact(k));
        res += MatPow(Matrix, k) * tmp ;
    }
    return res;
}