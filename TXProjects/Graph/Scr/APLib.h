#include <C:/Users/Artem/Desktop/TXLib.h>

//--------------------------------------------------------------------------------------------

void apCircle(double x, double y, double r, COLORREF color);
bool apCheck(int x_min, int x_max, int y_min, int y_max, int mode);
bool Key(char c);
void apColor(COLORREF color);

//--------------------------------------------------------------------------------------------

void apCircle(double x, double y, double r, COLORREF color)
{
    txSetColor(color);
    txSetFillColor(color);

    txCircle(x, y, r);
}

//--------------------------------------------------------------------------------------------

bool apCheck(int x_min, int x_max, int y_min, int y_max, int mode)
{
    if((txMouseX() >= x_min && txMouseX() <= x_max) &&
       (txMouseY() >= y_min && txMouseY() <= y_max) &&
       (txMouseButtons() == mode)) return true;

    else return false;
}

//--------------------------------------------------------------------------------------------

bool Key(char c)
{
    if (GetAsyncKeyState(c)) return true;

    else return false;
}

//--------------------------------------------------------------------------------------------

void apColor(COLORREF color)
{
    txSetColor(color);
    txSetFillColor(color);
}
