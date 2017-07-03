#include <TXLib.h>

//--------------------------------------------------------------------------------------------

class Pos
{
    public:

    struct Pash
    {
        int xMin, xMax, yMin, yMax, mode;
    };

    struct Hoope
    {
        int x, y, mode;
    };

    Pos():
        Pash p = {0, 0, 0, 0, 0},

        Hoope t = {0, 0, 0}
        {}

    ~Pos()
    {
    }

    void Scaner(Hoope* t);
};

//--------------------------------------------------------------------------------------------

void Scaner(Hoope* t)
{
    t -> x = txMouseX();
    t -> y = txMouseY();
    t -> mode = txMouseButtons();
}
