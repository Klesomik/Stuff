#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"

struct Ball
{
    int x, y, r;
    int vx, vy;
    COLORREF color;

    Ball ();
    Ball (int a, int b, int c, int move_x, int move_y, COLORREF init);

    void draw ();
};

Ball :: Ball ():
    x     (),
    y     (),
    r     (),
    vx    (),
    vy    (),
    color ()
    {}

Ball :: Ball (int a, int b, int c, int move_x, int move_y, COLORREF init):
    x     (a),
    y     (b),
    r     (c),
    vx    (move_x),
    vy    (move_y),
    color (init)
    {}

void Ball :: draw ()
{
    COLORREF old_color = txGetColor ();

    txSetColor     (color);
    txSetFillColor (color);

    txCircle (x, y, r);

    txSetColor (old_color);
}

const double dt = 1;

void move_to   (Ball& a, Ball& b);
void set_balls (Ball data[], const int count);
int init ();
void distance (Ball& a, Ball& b);
void balls (int i);
void clear (int x1, int y1, int x2, int y2);

void move_to (Ball& a, Ball& b)
{
    a.x += (b.x - a.x) / (a.vx * dt);
    a.y += (b.y - a.y) / (a.vy * dt);
}

void set_balls (Ball data[], const int count)
{
    bool exit = false;
    for (int i = 0; i < count; i++)
    {
        while (true)
        {
            if (txMouseButtons () == 1)
            {
                data[i] = { txMouseX (), txMouseY (), 10, 5, 5, RGB (random (255), random (255), random (255)) };

                data[i].draw ();

                clear (750, 550, 800, 600);
                balls (i + 1);

                break;
            }

            if (GetAsyncKeyState (VK_ESCAPE))
            {
                exit = true;

                break;
            }
        }

        if (exit) break;

        txSleep (125);
    }
}

int init ()
{
    txCreateWindow (800, 600);

    int count = 0;
    printf ("Get number of balls ");
    scanf ("%d", &count);

    system ("cls");
    txTextCursor (false);

    return count;
}

void distance (Ball& a, Ball& b)
{
    txLine (a.x, a.y, b.x, b.y);
}

void balls (int i)
{
    txSetColor (TX_WHITE);

    char tmp[9] = "";

    sprintf (tmp, "%d", i);

    txTextOut (750, 550, tmp);
}

void clear (int x1, int y1, int x2, int y2)
{
    txSetColor     (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txRectangle (x1, y1, x2, y2);
}

int main ()
{
    const int count = init ();
    Ball* data = new Ball[count];

    set_balls (data, count);

    txSetFillColor (TX_BLACK);
    txClear ();

    txBegin ();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        if (GetAsyncKeyState (VK_SHIFT))
        {
            for (int i = 0; i < count; i++)
            {
                if (i < count - 1) distance (data[i], data[i + 1]);

                else distance (data[i], data[0]);
            }
        }

        for (int i = 0; i < count; i++)
        {
            data[i].draw ();

            if (i < count - 1) move_to (data[i], data[i + 1]);

            else move_to (data[i], data[0]);
        }

        txSetFillColor (TX_BLACK);
        txSleep (50);
        txClear ();
    }

    txEnd ();

    return 0;
}
