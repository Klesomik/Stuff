#include "Declaration.h"

class MATRIX
{
    private:
        double matrix_[4][4] = { { 1, 0, 0, 0 },
                                 { 0, 1, 0, 0 },
                                 { 0, 0, 1, 0 },
                                 { 0, 0, 0, 1 } };

        void Mul(double Vect[4]);
        void Mul_local(double d[3][3]);

        void Swap_local(double tmp[3][3]);

        void MatClear();

    public:
        void MatRotX(double Vect[4], double angle);
        void MatRotY(double Vect[4], double angle);
        void MatRotZ(double Vect[4], double angle);
        void Mashtab(double Vect[4], double x, double y, double z);
};

void MATRIX::Mul(double Vect[4])
{
    double s[4] = { 0, 0, 0, 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            s[i] += Vect[j] * matrix_[i][j];
        }
    }

    for(int i = 0; i < 4; i++) Vect[i] = s[i];

    MatClear();
}

void MATRIX::MatClear()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j) matrix_[i][j] = 1;

            else matrix_[i][j] = 0;
        }
    }
}

void MATRIX::Mul_local(double d[3][3])
{
    double tmp[3][3] = { { 0, 0, 0 },
                         { 0, 0, 0 },
                         { 0, 0, 0 } };

    double s = 0;
    int p = 0, q = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int f = 0; f < 3; f++)
        {
            for(int j = 0; j < 3; j++)
            {
                s += d[i][j] * matrix_[j][f];
            }

            tmp[p][q] = s;

            if(q == 2) q = 0, p += 1;
            else q += 1;

            s = 0;
        }
    }

    Swap_local(tmp);
}

void MATRIX::Swap_local(double tmp[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix_[i][j] = tmp[i][j];
        }
    }
}

void MATRIX::MatRotX(double Vect[4], double angle)
{
    double data[3][3] = { {1,          0,           0},
                          {0, cos(angle), -sin(angle)},
                          {0, sin(angle),  cos(angle)} };

    Mul_local(data);

    Mul(Vect);
}

void MATRIX::MatRotY(double Vect[4], double angle)
{
    double data[3][3] = { {cos(angle), 0, -sin(angle)},
                          {         0, 1,           0},
                          {sin(angle), 0,  cos(angle)} };

    Mul_local(data);

    Mul(Vect);
}

void MATRIX::MatRotZ(double Vect[4], double angle)
{
    double data[3][3] = { {cos(angle), -sin(angle), 0},
                          {sin(angle),  cos(angle), 0},
                          {         0,           0, 1} };

    Mul_local(data);

    Mul(Vect);
}

void MATRIX::Mashtab(double Vect[4], double x, double y, double z)
{
    double data[3][3] = { { x, 0, 0 },
                          { 0, y, 0 },
                          { 0, 0, z } };

    Mul_local(data);

    Mul(Vect);
}
