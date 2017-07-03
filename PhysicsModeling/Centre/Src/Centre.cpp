#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"
#include "..//TXAddition.hpp"

struct Point
{
    static const int measurements = 2;

    int coords[measurements];
    int weight;
};

int Init (const int size_x, const int size_y);
void SetPoints (std::vector <Point>& data, const int size_x, const int size_y, const COLORREF information, const COLORREF centre);
void Calculate (const std::vector <Point>& data, Point& middle, const size_t j);
void Clear (const int x1, const int y1, const int x2, const int y2);
void Sleep (const Point& current);
void Circle (const Point& current, const COLORREF color);

int main ()
{
    try
    {
        const COLORREF information = TX_WHITE, centre = TX_YELLOW;

        const int size_x = 800, size_y = 600;

        int size = Init (size_x, size_y);

        if (size < 1) throw "Your size of points < 1. It must be more than 0!";

        std::vector <Point> data (size);

        SetPoints (data, size_x, size_y, information, centre);

        Point middle;

        for (size_t i = 0; i < Point::measurements; i++)
            Calculate (data, middle, i);

        middle.weight = 5;

        txSetColor (centre);
        txSetFillColor (centre);

        txCircle (middle.coords[0], middle.coords[1], middle.weight);

        Clear (size_x - 150, size_y - 50, size_x, size_y);

        txSetColor (information);

        adTextOut (size_x - 150, size_y - 50, "(%d, %d, %d)", middle.coords[0], middle.coords[1], middle.weight);
    }
    catch (const char* message)
    {
        std::cout << "Error: " << message << "\n";
    }

    return 0;
}

int Init (const int size_x, const int size_y)
{
    adCreateWindow (size_x, size_y, "[Esc]");

    std::cout << "Input number of points ";

    int size = 0;

    std::cin >> size;

    system ("cls");

    txTextCursor (false);

    return size;
}

void SetPoints (std::vector <Point>& data, const int size_x, const int size_y, const COLORREF information, const COLORREF centre)
{
    const int none = 0, left = 1, range = 255;

    for (size_t i = 0; i < data.size (); i++)
    {
        while (true)
        {
            if (txMouseButtons () == left)
            {
                data[i] = { txMouseX (), txMouseY (), -1 };

                COLORREF color = RGB (random (range), random (range), random (range));

                while (color == information || color == centre)
                    color = RGB (random (range), random (range), random (range));

                for (; txMouseButtons () != none; data[i].weight++)
                {
                    Circle (data[i], color);

                    Clear (size_x - 150, size_y - 50, size_x, size_y);

                    txSetColor (information);
                    txSelectFont ("Comic Sans MS", 28);

                    adTextOut (size_x - 150, size_y - 50, "(%d, %d, %d)", data[i].coords[0], data[i].coords[1], data[i].weight + 1);

                    Sleep (data[i]);
                }

                break;
            }
        }
    }
}

void Calculate (const std::vector <Point>& data, Point& middle, const size_t j)
{
    int up = 0, down = 0;

    for (size_t i = 0; i < data.size (); i++)
        up += (data[i].coords[j] * data[i].weight);

    for (size_t i = 0; i < data.size (); i++)
        down += data[i].weight;

    if (down == 0) throw "Division by 0. Total mass must be more than 0!";

    middle.coords[j] = up / down;
}

void Clear (const int x1, const int y1, const int x2, const int y2)
{
    txSetColor     (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txRectangle (x1, y1, x2, y2);
}

void Sleep (const Point& current)
{
    const double eps = 1e-6, base_sleep = 100;

    double dist = sqrt (pow (txMouseX () - current.coords[0], 2) + pow (txMouseY () - current.coords[1], 2));

    if (dist > eps)
        txSleep (base_sleep / dist);

    else
        txSleep (base_sleep);
}

void Circle (const Point& current, const COLORREF color)
{
    txSetColor (color);
    txSetFillColor (color);

    txCircle (current.coords[0], current.coords[1], current.weight);
}
