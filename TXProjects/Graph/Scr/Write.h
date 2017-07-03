#include "Graphics.h"

//--------------------------------------------------------------------------------------------

class Write
{
    private:

        struct Digit
        {
            double x, y;
        };

    public:

        Write() {}
        ~Write() {}

        void Digit_x();
        void Digit_y();
        void Numbers();

        void DoWrite()
        {
            Digit_x();

            Digit_y();

            Numbers();
        }
};

//--------------------------------------------------------------------------------------------

void Write::Digit_x()
{
    Digit p = {327.5, 327.5};

    txSelectFont ("Comic Sans MS", 15);
    txSetColor(TX_BLACK);

    txTextOut((p.x - 300) + 50 * zoom, p.y, "-12");
    txTextOut((p.x - 250) + 50 * zoom, p.y, "-10");
    txTextOut((p.x - 200) + 50 * zoom, p.y,  "-8");
    txTextOut((p.x - 150) + 50 * zoom, p.y,  "-6");
    txTextOut((p.x - 100) + 50 * zoom, p.y,  "-4");
    txTextOut((p.x -  50) - 50 * zoom, p.y,  "-2");
    txTextOut(                    p.x, p.y,   "0");
    txTextOut((p.x +  50) + 50 * zoom, p.y,   "2");
    txTextOut((p.x + 100) + 50 * zoom, p.y,   "4");
    txTextOut((p.x + 150) + 50 * zoom, p.y,   "6");
    txTextOut((p.x + 200) + 50 * zoom, p.y,   "8");
    txTextOut((p.x + 250) + 50 * zoom, p.y,  "10");
}

//--------------------------------------------------------------------------------------------

void Write::Digit_y()
{
    Digit p = {305, 277.5};

    txTextOut(p.x * zoom, (p.y + 350) * zoom, "-12");
    txTextOut(p.x * zoom, (p.y + 300) * zoom, "-10");
    txTextOut(p.x * zoom, (p.y + 250) * zoom,  "-8");
    txTextOut(p.x * zoom, (p.y + 200) * zoom,  "-6");
    txTextOut(p.x * zoom, (p.y + 150) * zoom,  "-4");
    txTextOut(p.x * zoom, (p.y + 100) * zoom,  "-2");
    txTextOut(p.x * zoom,         p.y * zoom,   "2");
    txTextOut(p.x * zoom, (p.y -  50) * zoom,   "4");
    txTextOut(p.x * zoom, (p.y - 100) * zoom,   "6");
    txTextOut(p.x * zoom, (p.y - 150) * zoom,   "8");
    txTextOut(p.x * zoom, (p.y - 200) * zoom,  "10");
    txTextOut(p.x * zoom, (p.y - 250) * zoom,  "12");
}

//--------------------------------------------------------------------------------------------

void Write::Numbers()
{
    txSelectFont ("Comic Sans MS", 25);

    txTextOut(625,   5,  "I");
    txTextOut(  5,   5,  "II");
    txTextOut(  5, 620, "III");
    txTextOut(625, 620,  "IV");

    txTextOut(350,   0, "Y");
    txTextOut(625, 275, "X");

    txTextOut(55, 55, "Zoom");
    txTextOut(535, 55, "Mode");
}
