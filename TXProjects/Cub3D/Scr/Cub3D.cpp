#include "Matrix.h"

inline void Rot_x(MATRIX p, double* x, double* y, double* z, double angle, double Vect[4])
{
    Vect[0] = (*x);
    Vect[1] = (*y);
    Vect[2] = (*z);

    p.MatRotX(Vect, angle);

    (*x) = Vect[0];
    (*y) = Vect[1];
    (*z) = Vect[2];
}

inline void Rot_y(MATRIX p, double* x, double* y, double* z, double angle, double Vect[4])
{
    Vect[0] = (*x);
    Vect[1] = (*y);
    Vect[2] = (*z);

    p.MatRotY(Vect, angle);

    (*x) = Vect[0];
    (*y) = Vect[1];
    (*z) = Vect[2];
}

inline void Rot_z(MATRIX p, double* x, double* y, double* z, double angle, double Vect[4])
{
    Vect[0] = (*x);
    Vect[1] = (*y);
    Vect[2] = (*z);

    p.MatRotZ(Vect, angle);

    (*x) = Vect[0];
    (*y) = Vect[1];
    (*z) = Vect[2];
}

inline void Sdvig(MATRIX p, double* x, double* y, double* z, double Vect[4], double x_s, double y_s, double z_s)
{
    Vect[0] = (*x);
    Vect[1] = (*y);
    Vect[2] = (*z);

    p.Mashtab(Vect, x_s, y_s, z_s);

    (*x) = Vect[0];
    (*y) = Vect[1];
    (*z) = Vect[2];
}

inline void apLine(MATRIX p, double     x1, double     y1, double     z1,
                   double     x2, double     y2, double     z2,
                   double angle, double Vect[4])
{
    apColor(TX_WHITE, 2);

    Rot_x(p, &x1, &y1, &z1, angle, Vect);
    Rot_x(p, &x2, &y2, &z2, angle, Vect);

    Rot_y(p, &x1, &y1, &z1, angle, Vect);
    Rot_y(p, &x2, &y2, &z2, angle, Vect);

    Rot_z(p, &x1, &z1, &y1, angle, Vect);
    Rot_z(p, &x2, &z2, &y2, angle, Vect);

    Sdvig(p, &x1, &y1, &z1, Vect, -1, 1, 1);
    Sdvig(p, &x2, &y2, &z2, Vect, -1, 1, 1);

    txLine( x1 * 400 / (-z1 + 400) + x_size / 2,
           -y1 * 400 / (-z1 + 400) + y_size / 2,
            x2 * 400 / (-z2 + 400) + x_size / 2,
           -y2 * 400 / (-z2 + 400) + y_size / 2);

}

void First();
void apCub(MATRIX p, double angle, double Vect[4]);

int main()
{
    First();

    MATRIX p;

    double x = 1, y = 1, z = 1;
    double Vect[4] = { x, y, z, 1 };

    txBegin();

    for(double angle = 0; (!Key(VK_ESCAPE)); angle += 0.01)
    {
        apClear(TX_BLACK);

        apCub(p, angle, Vect);
    }

    txEnd();

    return 0;
}

void First()
{
    apCreateWindow(x_size, y_size, "[For exit push ESCAPE]");

    txTextCursor(false);
}

void apCub(MATRIX p, double angle, double Vect[4])
{
    //1
    apLine(p, centreX - size / 2, centreY - size / 2, centreZ + size / 2,
           centreX - size / 2, centreY + size / 2, centreZ + size / 2, angle, Vect);

    apLine(p, centreX - size / 2, centreY + size / 2, centreZ + size / 2,
           centreX + size / 2, centreY + size / 2, centreZ + size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY + size / 2, centreZ + size / 2,
           centreX + size / 2, centreY - size / 2, centreZ + size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY - size / 2, centreZ + size / 2,
           centreX - size / 2, centreY - size / 2, centreZ + size / 2, angle, Vect);

    //2
    apLine(p, centreX - size / 2, centreY - size / 2, centreZ - size / 2,
           centreX - size / 2, centreY + size / 2, centreZ - size / 2, angle, Vect);

    apLine(p, centreX - size / 2, centreY + size / 2, centreZ - size / 2,
           centreX + size / 2, centreY + size / 2, centreZ - size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY + size / 2, centreZ - size / 2,
           centreX + size / 2, centreY - size / 2, centreZ - size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY - size / 2, centreZ - size / 2,
           centreX - size / 2, centreY - size / 2, centreZ - size / 2, angle, Vect);

    //3
    apLine(p, centreX - size / 2, centreY + size / 2, centreZ + size / 2,
           centreX - size / 2, centreY + size / 2, centreZ - size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY + size / 2, centreZ + size / 2,
           centreX + size / 2, centreY + size / 2, centreZ - size / 2, angle, Vect);

    //4
    apLine(p, centreX - size / 2, centreY - size / 2, centreZ + size / 2,
           centreX - size / 2, centreY - size / 2, centreZ - size / 2, angle, Vect);

    apLine(p, centreX + size / 2, centreY - size / 2, centreZ + size / 2,
           centreX + size / 2, centreY - size / 2, centreZ - size / 2, angle, Vect);

    txSleep(10);
}
