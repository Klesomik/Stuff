#include <TXLib.h>

struct Check
{
    int x_min, x_max, y_min, y_max, mode;

    char c;
};

//--------------------------------------------------------------------------------------------

void apCircle(double x, double y, double r, COLORREF color);
bool apCheck(Check p);
bool Key(char c);
void apColor(COLORREF color, int sizeColor = 1);
void apCreateWindow(int width, int height, const char* header = 0);
void apClear(COLORREF color);

//--------------------------------------------------------------------------------------------

void apCircle(double x, double y, double r, COLORREF color)
{
    txSetColor(color);
    txSetFillColor(color);

    txCircle(x, y, r);
}

//--------------------------------------------------------------------------------------------

bool apCheck(Check p)
{
    if(((txMouseX() >= p.x_min && txMouseX() <= p.x_max) &&
       (txMouseY() >= p.y_min && txMouseY() <= p.y_max) &&
       (txMouseButtons() == p.mode)) || (Key(p.c))) return true;

    else return false;
}

//--------------------------------------------------------------------------------------------

bool Key(char c)
{
    if(GetAsyncKeyState(c)) return true;

    else return false;
}

//--------------------------------------------------------------------------------------------

void apColor(COLORREF color, int sizeColor)
{
    txSetColor(color, sizeColor);
    txSetFillColor(color);
}

//--------------------------------------------------------------------------------------------

void apCreateWindow(int width, int height, const char* header)
{
    txCreateWindow(width, height);

    SetWindowText(txWindow(), header);
}

//--------------------------------------------------------------------------------------------

void apClear(COLORREF color)
{
    apColor(color);

    txClear();
}
