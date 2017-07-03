#include "APLib.h"

struct Push
{
    int x, y, size_for_x, size_for_y, began;
};

struct CheckPush
{
    int x_min, x_max, y_min, y_max, mode;
};

int zoom = 1, x_size = 650, y_size = 650;
bool TFW = true, TFA = true;

class Window
{
    private:

        HDC graph;

    public:

        Window() :
            graph   (txLoadImage ("Pictures\\PushGraph.bmp"))
            {}

        ~Window() {/*txDeleteDC(graph);*/}

        void ClearWin();
        void PushWin();
        void ControlWin();

        void DrawWin()
        {
            ClearWin();

            PushWin();

            ControlWin();
        }
};

void Window::ClearWin()
{
    apColor(TX_GRAY);

    for (double x = 25; x <= 650; x += 25) txLine(x, 0, x, y_size);

    for (double y = 25; y <= 650; y += 25) txLine(0, y, x_size, y);
}

void Window::PushWin()
{
    /*CheckPush q = {0, 0, 0, 0, 0};
    Push p = {0, 0, 0, 0, 0};

    //Çóì
    q.x_min = 0, q.x_max = 0;
    if (apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode)) txBitBlt(txDC(), p.x, p.y, p.size_for_x, p.size_for_y, fon, p.began, 0);
    else txBitBlt (txDC(), p.x, p.y, p.size_for_x, p.size_for_y, fon, p.began, 0);*/
}

void Window::ControlWin()
{
}
