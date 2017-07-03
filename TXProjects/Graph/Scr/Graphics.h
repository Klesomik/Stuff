#include "Window.h"

//--------------------------------------------------------------------------------------------

class Timeline
{
    private:

        struct Points
        {
            double x, y, r;
            COLORREF color;
            int k;
            bool COP;
        };

    public:

        Timeline() {}
        ~Timeline() {}

        double Straight(Points p) { return (p.COP == true)? p.y = -(p.k * p.x) : p.color = TX_BLACK; }

        double Parabola(Points p) { return (p.COP == true)? p.y = -(p.x * p.x) : p.color = TX_RED; }

        double CubParabola(Points p) { return (p.COP == true)? p.y = -(p.x * p.x * p.x) : p.color = TX_BLUE; }

        void Sqrt();

        double Giper(Points p) { return (p.COP == true)? p.y = -(p.k / p.x) : p.color = TX_LIGHTGREEN; }

        double Sin(Points p) { return (p.COP == true)? p.y = -(sin(p.x)) : p.color = TX_LIGHTBLUE; }

        double Cos(Points p) { return (p.COP == true)? p.y = -(cos(p.x)) : p.color = TX_YELLOW; }

        double Tan(Points p) { return (p.COP == true)? p.y = -(tan(p.x)) : p.color = TX_PINK; }

        double CTan(Points p) { return (p.COP == true)? p.y = -(1 / tan(p.x)) : p.color = TX_LIGHTCYAN; }

        double ParabolaPlus(Points p) { return (p.COP == true)? p.y = -((p.x + 5) * (p.x + 5)) : p.color = TX_GREEN; }

        double Change(Points p) { return (p.COP == true)? p.y = -(p.k * p.x) : p.color = TX_PINK; }

        double ChangePlus(Points p) { return (p.COP == true)? p.y = -(p.k * p.x * p.x) : p.color = TX_WHITE; }

        void Inequalities();

        void Control();

        typedef double Variable(Points p);

        void DGraph(Variable* func);

        void DGPlus(Variable* func);
};

//--------------------------------------------------------------------------------------------

void Timeline::Sqrt()
{
    Points p = {0, 0, 1, TX_ORANGE};

    for (p.x = 0; p.x <= 20; p.x += 0.01)
    {
        if (fabs(p.x) <= 0.001) continue;

        p.y = -(sqrt(p.x));

        apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, p.color);
    }
}

//--------------------------------------------------------------------------------------------

void Timeline::Inequalities()
{
    Points p = {-10, -10, 1, 0};

    for(p.y = -10; p.y <= +10; p.y += 0.1)
    {
        for(p.x = -10; p.x <= +10; p.x += 0.1)
        {
            if(p.y > p.x * p.x - 2)
            apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, TX_LIGHTRED);

            if (p.y < -p.x * p.x + 7)
            apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, TX_LIGHTBLUE);

            if(p.x * p.x + p.y * p.y <= 1)
            apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, TX_LIGHTGREEN);
        }
    }
}

void Timeline::DGraph(Variable* func)
{
    Points p = {-20, 0, 1, 0, 1, true};

    for (p.x = -20; p.x <= +20; p.x += 0.01)
    {
        if (fabs(p.x) <= 0.001) continue;

        p.COP = true;
        p.y = func(p);

        p.COP = false;
        p.color = func(p);

        apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, p.color);
    }
}

void Timeline::DGPlus(Variable* func)
{
    Points p = {-20, 0, 1, 0, -10, true};

    for (p.x = -20; p.x <= +20; p.x += 0.01)
    {
        if (fabs(p.x) <= 0.001) continue;

        for (p.k = -10; p.k <= +10; p.k++)
        {
            p.COP = true;
            p.y = func(p);

            p.COP = false;
            p.color = func(p);

            apCircle(p.x * zoom * 25 + x_size / 2, p.y * zoom * 25 + y_size / 2, p.r, p.color);
        }
    }
}

void Timeline::Control()
{
    /*CheckPush q = {0, 0, 5, 55, 1};

    q.x_min = 80, q.x_max = 130;
    if ((Key(VK_F1)) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Parabola);

    q.x_min = 135, q.x_max = 185;
    if ((Key(VK_F2)) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(CubParabola);

    if (Key(VK_F3))
    DGPlus(Change);

    if (Key(VK_F4))
    DGPlus(ChangePlus);

    if (Key(VK_F5))
    DGraph(ParabolaPlus);

    if (Key(VK_F6))
    Inequalities();

    q.x_min = 25, q.x_max = 75;
    if ((Key('Z')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Srtaight);

    q.x_min = 190, q.x_max = 242;
    if ((Key('X')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Sqrt);

    q.x_min = 245, q.x_max = 297;
    if ((Key('C')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Giper);

    q.x_min = 350, q.x_max = 402;
    if ((Key('V')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Sin);

    q.x_min = 405, q.x_max = 457;
    if ((Key('B')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Cos);

    q.x_min = 460, q.x_max = 512;
    if ((Key('N')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(Tan);

    q.x_min = 515, q.x_max = 567;
    if ((Key('M')) || apCheck(q.x_min, q.x_max, q.y_min, q.y_max, q.mode))
    DGraph(CTan);*/
}
