#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"
#include "Vector.hpp"
#include "Ball.hpp"

void Init ();
void ClearWindow ();

void Crash (Ball& first, Ball& second);

int main ()
{
    Init ();

    std::vector <Ball> data (2);

    txBegin ();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        ClearWindow ();

        for (int i = 0; i < data.size (); i++)
            data[i].control ();

        for (int i = 0; i < data.size (); i++)
            data[i].move ();

        for (int i = 0; i < data.size (); i++)
        {
            for (int j = 0; j < data.size (); j++)
            {
                if (i == j)
                    continue;

                Crash (data[i], data[j]);
            }
        }

        for (int i = 0; i < data.size (); i++)
        {
            if (data[i].coords[0] < 0 + data[i].radius)
                data[i].speed[0] = -data[i].speed[0];

            if (data[i].coords[0] > txGetExtentX () - data[i].radius)
                data[i].speed[0] = -data[i].speed[0];

            if (data[i].coords[1] < 0 + data[i].radius)
                data[i].speed[1] = -data[i].speed[1];

            if (data[i].coords[1] > txGetExtentY () - data[i].radius)
                data[i].speed[1] = -data[i].speed[1];
        }

        for (int i = 0; i < data.size (); i++)
            data[i].render ();


        txSleep (25);
    }

    txEnd ();

    return 0;
}

void Init ()
{
    const int size_x = 800, size_y = 600;

    srand (time (nullptr));

    txCreateWindow (size_x, size_y);
    SetWindowText (txWindow (), "Moleculs");

    _txExit = true;
}

void ClearWindow ()
{
    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txClear ();
}

void Crash (Ball& first, Ball& second)
{
    if (Math::Distance (first.coords, second.coords) < first.radius + second.radius)
    {
        std::swap (first.speed, second.speed);

        first.coords = { 100, 100 };
    }
}
