#include "TXLib.h"
#include "Vector.hpp"

// „ем больше удар€ютс€, тем больше температура, соответственно больше скорость

const size_t size_x = 1980 - 100, size_y = 1080 - 100;

class Ball
{
    public:
        Ball ();

        void draw ();
        void move ();
        void control ();

        Math::VectorD2& coords ();
        Math::VectorD2& speed ();
        double& mass ();

    private:
        Math::VectorD2 coords_;
        Math::VectorD2 speed_;

        double mass_;

        COLORREF color_;
};

Ball::Ball ():
    coords_ (),
    speed_ (),
    mass_ (),
    color_ ()
{
    coords_[0] = random (0 + mass_, size_x - mass_);
    coords_[1] = random (0 + mass_, size_y - mass_);

    mass_ = random (2, 4);

    color_ = RGB (random (0, 255), random (0, 255), random (0, 255));
}

void Ball::draw ()
{
    txSetColor (color_);
    txSetFillColor (color_);

    txCircle (coords_[0], coords_[1], mass_);
}

void Ball::move ()
{
    coords_ += speed_;

    if (coords_[0] - mass_ < 0)
    {
        coords_[0] = mass_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] - mass_ < 0)
    {
        coords_[1] = mass_;
         speed_[1] = -speed_[1];
    }

    if (coords_[0] + mass_ > size_x)
    {
        coords_[0] = size_x - mass_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] + mass_ > size_y)
    {
        coords_[1] = size_y - mass_;
         speed_[1] = -speed_[1];
    }
}

void Ball::control ()
{
    Math::VectorD2 up, down, left, right;

       up[0] = 0,    up[1] = -0.1;
     down[0] = 0,  down[1] = +0.1;
     left[0] = -0.1,  left[1] = 0;
    right[0] = +0.1, right[1] = 0;

    if (GetAsyncKeyState (VK_UP)) speed_ += up;
    if (GetAsyncKeyState (VK_DOWN)) speed_ += down;
    if (GetAsyncKeyState (VK_LEFT)) speed_ += left;
    if (GetAsyncKeyState (VK_RIGHT)) speed_ += right;
}

Math::VectorD2& Ball::coords ()
{
    return coords_;
}

Math::VectorD2& Ball::speed ()
{
    return speed_;
}

double& Ball::mass ()
{
    return mass_;
}

void Init ();
void ClearWindow (COLORREF color);
void MainWhile (std::vector <Ball>& atoms);
void Crash (Ball& from, Ball& to);
double Distance (Math::VectorD2& from, Math::VectorD2& to);

int main ()
{
    srand (time (NULL));

    const size_t size = 300;

    Init ();

    std::vector <Ball> atoms (size);

    MainWhile (atoms);

    return 0;
}

void Init ()
{
    txCreateWindow (size_x, size_y);
    txTextCursor (false);
}

void ClearWindow (COLORREF color)
{
    txSetColor (color);
    txSetFillColor (color);

    txClear ();
}

void MainWhile (std::vector <Ball>& atoms)
{
    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin ();

        ClearWindow (TX_BLACK);

        for (size_t i = 0; i < atoms.size (); i++)
        {
            atoms[i].control ();
            atoms[i].move ();

            for (size_t j = 0; j < atoms.size (); j++)
            {
                if (i != j) Crash (atoms[i], atoms[j]);
            }

            atoms[i].draw ();
        }

        txEnd ();

        txSleep (10);
    }
}

void Crash (Ball& from, Ball& to) //Hit
{
    static int x = 0;

    double dist = Distance (from.coords (), to.coords ());

    if (dist < from.mass () + to.mass ())
    {
        double eps = (from.mass () + to.mass ()) / from.mass ();

        Math::VectorD2 p1 (from.coords (), to.coords ());
        Math::VectorD2 p2 (p1 / eps);

        Math::VectorD2 normal = !(p1 - p2);
        Math::VectorD2 tangents = ~normal;

        from.speed () *= from.mass ();
          to.speed () *=   to.mass ();

        Math::VectorD2 from_new;
        Math::VectorD2 to_new;

        from_new[0] = from.speed () & tangents;
        from_new[1] = to.speed () & normal;

        to_new[0] = to.speed () & tangents;
        to_new[1] = from.speed () & normal;

        from.speed () = from_new;
        to.speed () = to_new;

        from.speed () /= from.mass ();
        to.speed () /= to.mass ();

        /*Math::VectorD2 centres (from.coords (), to.coords ());

        centres *= ((from.mass () + to.mass ()) / dist);

        to.coords ()[0] = from.coords ()[0] + centres[0];
        to.coords ()[1] = from.coords ()[0] + centres[1];*/
    }
}

double Distance (Math::VectorD2& from, Math::VectorD2& to)
{
    double dist = sqrt (pow ((from[0] - to[0]), 2) + pow ((from.coords ()[1] - to.coords ()[1]), 2));

    return dist;
}
