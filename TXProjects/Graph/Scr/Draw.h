#include "Write.h"

//--------------------------------------------------------------------------------------------

class Draw
{
    private:

        //Draw (const Draw&);
        //Draw& operator = (const Draw&);

        HDC fon;

        const double began = 318.75, ent = 331.25;

    protected:

        COLORREF color;

    public:

        Draw() :
            fon   (txLoadImage ("Pictures\\Push.bmp")),
            color (TX_BLACK)
            {}

        ~Draw() {/*txDeleteDC(fon);*/}

        void FillColor();
        void DrawWeb();
        void X();
        void Y();
        void DrawPush();
        void Axis() {X(); Y();}
        void DrawAll(Write write);
        void DrawGraphics(Write write, Timeline timeline);
        void Control(Write write);
        void DrawWindow(Write write) {DrawAll(write); DrawPush();}
};

//--------------------------------------------------------------------------------------------

void Draw::FillColor()
{
    txSetFillColor(RGB(255, 255, 128));
    txRectangle(x_size / 2, 0, x_size, y_size / 2);

    txSetFillColor(RGB(255, 128, 128));
    txRectangle(0, 0, x_size / 2, y_size / 2);

    txSetFillColor(RGB(128, 255, 128));
    txRectangle(0, y_size / 2, x_size / 2, y_size);

    txSetFillColor(RGB(0, 255, 255));
    txRectangle(x_size / 2, y_size / 2, x_size, y_size);
}

//--------------------------------------------------------------------------------------------

void Draw::DrawWeb()
{
    txSetColor(TX_GRAY);

    for (double x = 25; x <= 650; x += 25 * zoom) txLine(x, 0, x, y_size);

    for (double y = 25; y <= 650; y += 25 * zoom) txLine(0, y, x_size, y);
}

//--------------------------------------------------------------------------------------------

void Draw::DrawAll(Write write)
{
    FillColor();

    if(TFW == true) DrawWeb();
    if(TFA == true) Axis();

    write.DoWrite();
}

//--------------------------------------------------------------------------------------------

void Draw::X()
{
    txSetColor(color, 3);

    txLine(0, y_size / 2, x_size, y_size / 2);

    txLine(x_size, y_size / 2, x_size - 25 * zoom, y_size / 2 - 25 * zoom);
    txLine(x_size, y_size / 2, x_size - 25 * zoom, y_size / 2 + 25 * zoom);

    txSetColor(color);

    for (int i = 25; i <= 625; i += 50 * zoom) txLine(i, began, i, ent);
}

//--------------------------------------------------------------------------------------------

void Draw::Y()
{
    txSetColor(color, 3);

    txLine(x_size / 2, 0, x_size / 2, y_size);

    txLine(x_size / 2, 0, x_size / 2 - 25 * zoom, 25 + 25 * zoom);
    txLine(x_size / 2, 0, x_size / 2 + 25 * zoom, 25 + 25 * zoom);

    txSetColor(color);

    for (int i = 25; i <= 625; i += 50 * zoom) txLine(began, i, ent, i);
}

//--------------------------------------------------------------------------------------------

void Draw::DrawPush()
{
    CheckPush q = {0, 0, 5, 55, 0};
    Push p = {0, 0, 50, 50, 0};

    //Зум
    q.x_min = 30, q.x_max = 80;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 30, p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 600, 0);
    else txBitBlt (txDC(), p.x +  30, p.y +   5, p.size_for_x, p.size_for_y, fon, p.began, 0);

    q.x_min = 85, q.x_max = 135;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 85, p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 650, 0);
    else txBitBlt (txDC(), p.x +  85, p.y +   5, p.size_for_x, p.size_for_y, fon, p.began + 50, 0);

    q.x_min = 140, q.x_max = 240;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 140, p.y + 5, p.size_for_x + 50, p.size_for_y, fon, p.began + 1000, 0);
    else txBitBlt (txDC(), p.x +  140, p.y + 5, p.size_for_x + 50, p.size_for_y, fon, p.began + 400, 0);

    //Режим
    q.x_min = 510, q.x_max = 560;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 510, p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 700, 0);
    else txBitBlt (txDC(), p.x + 510,   p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 100, 0);

    q.x_min = 565, q.x_max = 615;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 565, p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 750, 0);
    else txBitBlt (txDC(), p.x + 565,   p.y + 5, p.size_for_x, p.size_for_y, fon, p.began + 150, 0);

    q.x_min = 405, q.x_max = 505;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 405, p.y + 5, p.size_for_x + 50, p.size_for_y, fon, p.began + 1100, 0);
    else txBitBlt (txDC(), p.x +  405, p.y + 5, p.size_for_x + 50, p.size_for_y, fon, p.began + 500, 0);

    //Графики
    q.x_min = 25, q.x_max = 125, q.y_min = 568, q.y_max = 618;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x +  25, p.y + 568, p.size_for_x + 50, p.size_for_y, fon, p.began + 900, 0);
    else txBitBlt (txDC(), p.x +  25, p.y + 568, p.size_for_x + 50, p.size_for_y, fon, p.began + 300, 0);

    q.x_min = 135, q.x_max = 235;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 135, p.y + 568, p.size_for_x + 50, p.size_for_y, fon, p.began + 800, 0);
    else txBitBlt (txDC(), p.x +  135, p.y + 568, p.size_for_x + 50, p.size_for_y, fon, p.began + 200, 0);


    q.x_min = 355, q.x_max = 405;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 355, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 1200, 0);
    else txBitBlt (txDC(), p.x +  355, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 450, 0);

    q.x_min = 410, q.x_max = 460;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 410, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 1250, 0);
    else txBitBlt (txDC(), p.x +  410, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 500, 0);

    q.x_min = 465, q.x_max = 515;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 465, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 1300, 0);
    else txBitBlt (txDC(), p.x +  465, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 550, 0);

    q.x_min = 520, q.x_max = 570;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    txBitBlt(txDC(), p.x + 520, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 1350, 0);
    else txBitBlt (txDC(), p.x +  520, p.y + 568, p.size_for_x, p.size_for_y, fon, p.began + 600, 0);
}

//--------------------------------------------------------------------------------------------

void Draw::Control(Write write)
{
    CheckPush p = {0, 0, 5, 55, 1};

    p.x_min = 30, p.x_max = 80;
    if (((Key (VK_UP)) && (zoom < 4)) ||
       (apCheck(p.x_min, p.x_max, p.y_min, p.y_max, p.mode) && (zoom < 4)))
    {
        zoom *= 2;

        DrawWindow(write);

        txSleep(100);
    }

    p.x_min = 85, p.x_max = 135;
    if (((Key (VK_DOWN)) && (zoom > 1)) ||
       (apCheck(p.x_min, p.x_max, p.y_min, p.y_max, p.mode) && (zoom > 1)))
    {
        zoom /= 2;

        DrawWindow(write);

        txSleep(100);
    }

    p.x_min = 135, p.x_max = 235, p.y_min = 568, p.y_max = 618;
    if ((Key(VK_F7)) || apCheck(p.x_min, p.x_max, p.y_min, p.y_max, p.mode))
    DrawWindow(write);

    if(Key('Q')) {TFW =  true; DrawAll(write);}

    if(Key('W')) {TFW = false; DrawAll(write);}

    if(Key('E')) {TFA =  true; DrawAll(write);}

    if(Key('R')) {TFA = false; DrawAll(write);}
}
