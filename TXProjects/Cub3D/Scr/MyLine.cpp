#include "APLib.h"

void apLine(int x1, int y1, int x2, int y2, int r, COLORREF color);

int main()
{
    apCreateWindow(800, 600, "MyLine");

    apLine(100, 100, 200, 200, 10, TX_RED);

    return 0;
}

void apLine(int x1, int y1, int x2, int y2, int r, COLORREF color)
{
    int j = y1;

    for(int i = x1; i <= x2 || j <= y2; i++, j++)
    {
        apCircle(i, j, r, color);
    }
}
