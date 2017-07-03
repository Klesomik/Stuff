#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"

const int R = 150;

struct Horse
{
    int t;
    double x, y, v;

    Horse (double a, double b, double c);

    void move ();
    void draw ();
};

Horse :: Horse (double a, double b, double c):
    t (0),
    x (a),
    y (b),
    v (c)
    {}

void Horse :: move ()
{
    t++;

    double alpha = v * t / R;

    x = R * cos (alpha);
    y = R * sin (alpha);
}

void Horse :: draw ()
{
    txSetColor     (TX_RED);
    txSetFillColor (TX_RED);

    txCircle (x + 400, y + 300, 10);
}

int main ()
{
    txCreateWindow (800, 600);

    Horse t (400, 300, 10);

    txBegin ();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetColor     (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear ();

        txSetColor (TX_YELLOW);
        txCircle (400, 300, R);

        t.draw ();
        t.move ();

        txSleep (50);
    }

    txEnd ();

    return 0;
}
