#include "APLib.h"

#define x_size 800
#define y_size 600

struct Voxel
{
    double x, y, z;
};

Voxel V[3] = { { -100,  50, -1 },
               {   50, 100, -1 },
               {  100,  50, -1 } };

double Z_BUFFER[800][600] = {};

double Lerp(double A, double B, double K);
void MyLine(double x1, double y1, double z1, double x2, double y2, double z2, COLORREF color);
void Sravnenya(double x, double y, double z, COLORREF color);
void apPixel(double x, double y, double z, COLORREF color);
void apTriangle();
void Selection_Sort();
void Swap(int i, int j);

int main()
{
    apCreateWindow(800, 600, "Test");

    apTriangle();

    return 0;
}

double Lerp(double A, double B, double K)
{
    double X = A + (B - A) * K;

    return X;
}

void MyLine(double x1, double y1, double z1, double x2, double y2, double z2, COLORREF color)
{
    for(double k = 0; k <= 1; k += 0.1)
    {
        apPixel(Lerp(x1, x2, k),
                Lerp(y1, y2, k),
                Lerp(z1, z2, k), color);
    }
}

void Sravnenya(double x, double y, double z, COLORREF color)
{
    if(Z_BUFFER[(int) x][(int) y] == 0)
    {
        Z_BUFFER[(int) x][(int) y] = z;

        txSetPixel(x, y, color);
    }

    else
    {
        if(Z_BUFFER[(int) x][(int) y] < z)
        {
            Z_BUFFER[(int) x][(int) y] = z;

            txSetPixel(x, y, color);
        }
    }
}

void apPixel(double x, double y, double z, COLORREF color)
{
    double a =  x * 400 / (-z + 400) + x_size / 2;
    double b = -y * 400 / (-z + 400) + y_size / 2;

    Sravnenya(a, b, z, color);
}

void apTriangle()
{
    Selection_Sort();

    double A1Lerp = fabs(V[0].y - V[2].y) / fabs(V[1].y - V[2].y);

    Voxel A1 = {}, M = {}, K = {};

    A1.x = Lerp(V[0].x, V[2].x, A1Lerp);
    A1.y = V[1].y;
    A1.z = Lerp(V[0].z, V[2].z, A1Lerp);

    for(double k = 0; k <= 1; k += 0.01)
    {
        //B to A1
        M.x = Lerp(A1.x, V[0].x, k);
        M.y = Lerp(A1.y, V[0].y, k);
        M.z = Lerp(A1.z, V[0].z, k);

        //B to C
        K.x = Lerp(V[1].x, V[0].x, k);
        K.y = Lerp(V[1].y, V[0].y, k);
        K.z = Lerp(V[1].z, V[0].z, k);

        MyLine(M.x, M.y, M.z,
               K.x, K.y, K.z, TX_GREEN);
    }

    for(double k = 0; k <= 1; k += 0.01)
    {
        //A to A1
        M.x = Lerp(A1.x, V[2].x, k);
        M.y = Lerp(A1.y, V[2].y, k);
        M.z = Lerp(A1.z, V[2].z, k);

        //A to C
        K.x = Lerp(V[1].x, V[2].x, k);
        K.y = Lerp(V[1].y, V[2].y, k);
        K.z = Lerp(V[1].z, V[2].z, k);

        MyLine(M.x, M.y, M.z,
               K.x, K.y, K.z, TX_RED);
    }

    MyLine(V[0].x, V[0].y, V[0].z,
           V[1].x, V[1].y, V[1].z, TX_WHITE);
}

void Selection_Sort()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(V[i].y < V[j].y)
            {
                Swap(i, j);
            }
        }
    }
}

void Swap(int i, int j)
{
    Voxel tmp = V[i];
                V[i] = V[j];
                       V[j] = tmp;
}
