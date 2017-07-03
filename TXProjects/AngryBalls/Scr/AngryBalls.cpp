#include "TXLib.h"

//--------------------------------------------------------------------------------------------

struct CBall
{
    double x, y;
    double vx, vy;
    double r;
    int size_x;
    HDC ball;
    COLORREF color;
    COLORREF new_color;
};

//--------------------------------------------------------------------------------------------

void PlayBall (int x_size, int y_size, HDC fon);
void DrawFon (HDC fon);
void DrawBall (CBall* b, int x_size, int y_size);
void ControlBall (CBall* b, int left, int right, int up, int down);
void MoveBall (CBall* b, double dt, int size_x, int size_y);
double Distance (CBall* b, CBall* b2);
double DistanceForBirds (CBall* b, CBall* b2);
void ChangeSprite (CBall* b);
void ChangeColor (CBall* b);
void DrawAllBalls (CBall balls[], int n, int x_size, int y_size);
void ControlAllBalls (CBall balls[], int n);
void MoveAllBalls (CBall balls[], int n, double dt, int size_x, int size_y);
void DistanceAllBalls (CBall* b, CBall* b2, int n);

//--------------------------------------------------------------------------------------------

int main()
{
    int x_size = 0, y_size = 0;

    printf("Введите размер экрана через пробел: ");

    scanf("%d %d", &x_size, &y_size);

    txCreateWindow (x_size, y_size);

    HDC fon = txLoadImage ("Pictures\\Fon.bmp");

    txPlaySound ("Sound2 (AngryBirdsThemeDubStep).wav", SND_LOOP);

    PlayBall (x_size, y_size, fon);

    return 0;
}

//--------------------------------------------------------------------------------------------

void PlayBall (int x_size, int y_size, HDC fon)
{
    txPlaySound ("Sound2 (AngryBirdsThemeDubStep).wav", SND_LOOP);

    HDC ball_first = txLoadImage ("Pictures\\RedBird.bmp");
    HDC ball_second = txLoadImage ("Pictures\\YellowBird.bmp");
    HDC ball_third = txLoadImage ("Pictures\\BlackBird.bmp");

    const int N = 50;

    CBall balls[N] = { {50, 50, 1, 1, 85, 0, ball_first, TX_NULL}, {250, 250, 1, 1, 85, 0, ball_second, TX_NULL}, {450, 450, 1, 1, 85, 0, ball_third, TX_NULL} };

    double dt = 1;

    txBegin();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        DrawFon (fon);

        DrawAllBalls (balls, N, x_size, y_size);

        DistanceForBirds (&balls[0], &balls[1]);
        DistanceForBirds (&balls[0], &balls[2]);
        DistanceForBirds (&balls[1], &balls[2]);

        //DistanceAllBalls (balls, N);

        ControlAllBalls (balls, N);

        MoveAllBalls (balls, N, dt, x_size, y_size);

        txSleep (1);

        if (GetAsyncKeyState (VK_SPACE))
        {
            txClear();
            getch();
        }

        if (GetAsyncKeyState ('Q'))
        {
            txPlaySound (NULL, SND_LOOP);
        }
    }

    txBegin();

    DrawFon (fon);

    txPlaySound (NULL, SND_LOOP);

    txDeleteDC(balls[0].ball);
    txDeleteDC(balls[1].ball);
    txDeleteDC(balls[2].ball);
}

//--------------------------------------------------------------------------------------------

void DrawFon (HDC fon)
{
    txSetFillColor (TX_BLACK);
    txClear ();
    //txTransparentBlt (txDC(), 0, 0, 800, 600, fon, 0, 0);
}

//--------------------------------------------------------------------------------------------

void DrawBall (CBall* b, int x_size, int y_size)
{
    if (b -> ball != 0) txTransparentBlt (txDC(), b -> x, b -> y, 100, 100, b -> ball, b -> size_x, 0);

    else
    {
        if (b -> color == 0)
        {
            txSetColor (b -> color = RGB(random(256), random(256), random(256)), 5);
            txSetFillColor (b -> color);
            txCircle (b -> x = random(x_size), b -> y = random(y_size), b -> r = random(10));

            b -> vx = random(10);
            b -> vy = random(10);

            if (b -> vx == 0) b -> vx += 1;

            if (b -> vy == 0) b -> vy += 1;

            if (b -> r == 0) b -> vx += 5;
        }

        else
        {
            txSetColor (b -> color, 5);
            txSetFillColor (b -> color);
            txCircle (b -> x, b -> y, b -> r);
        }
    }
}

//--------------------------------------------------------------------------------------------

void ControlBall (CBall* b, int left, int right, int up, int down)
{
    int up_speed = 1;

    if (GetAsyncKeyState (VK_SHIFT)) up_speed = 10;

    if (GetAsyncKeyState (left))  b -> vx -= up_speed;
    if (GetAsyncKeyState (right)) b -> vx += up_speed;
    if (GetAsyncKeyState (up))    b -> vy -= up_speed;
    if (GetAsyncKeyState (down))  b -> vy += up_speed;
}

//--------------------------------------------------------------------------------------------

void MoveBall (CBall* b, double dt, int x_size, int y_size)
{
    b -> x += b -> vx * dt;
    b -> y += b -> vy * dt;

    if (b -> x > x_size - b -> r)
    {
        if (b -> ball != 0) ChangeSprite (b);

        else ChangeColor (b);

        b -> vx = - b -> vx;
        b -> x = x_size - b -> r;
    }

    if (b -> y > y_size - b -> r)
    {
        if (b -> ball != 0) ChangeSprite (b);

        else ChangeColor (b);

        b -> vy = - b -> vy;
        b -> y = y_size - b -> r;
    }

    if (b -> x < b -> r / 100)
    {
        if (b -> ball != 0) ChangeSprite (b);

        else ChangeColor (b);

        b -> vx = - b -> vx;
        b -> x = b -> r / 100;
    }

    if (b -> y < b -> r / 100)
    {
        if (b -> ball != 0) ChangeSprite (b);

        else ChangeColor (b);

        b -> vy = - b -> vy;
        b -> y = b -> r / 100;
    }
}

//--------------------------------------------------------------------------------------------

void DrawAllBalls (CBall balls[], int n, int x_size, int y_size)
{
    for (int i = 0; i < n; i++)
    {
        assert(0 <= i && i < n);

        DrawBall (&balls[i], x_size, y_size);
    }
}

//--------------------------------------------------------------------------------------------

void MoveAllBalls (CBall balls[], int n, double dt, int x_size, int y_size)
{
    for (int i = 0; i < n; i++)
    {
        assert(0 <= i && i < n);

        MoveBall (&balls[i], dt, x_size, y_size);
    }
}

//--------------------------------------------------------------------------------------------

void ControlAllBalls (CBall balls[], int n)
{
    int i = 0;

    ControlBall (&balls[0], VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN);
    ControlBall (&balls[1], 'A', 'D', 'W', 'S');
    ControlBall (&balls[2], 'F', 'H', 'T', 'G');

    for (i = 3; i < n; i++) ControlBall (&balls[i], 'J', 'L', 'I', 'K');
}

//--------------------------------------------------------------------------------------------

/*void DistanceAllBalls (CBall* b, CBall* b2, int n)
{
    double d10 = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < n; j++)
        {
            d10 = Distance (b[i], b[j]);

            if (d10 <= b[i] -> r / 2 + b[j] -> r / 2)
            {
                b += b2;

                b2 = 0;
            }
        }
    }
}*/

//--------------------------------------------------------------------------------------------

double Distance (CBall* b, CBall* b2)
{
    double dist = sqrt((b -> x - b2 -> x) * (b -> x - b2 -> x) + (b -> y - b2 -> y) * (b -> y - b2 -> y));
    double d12 = dist;

    return d12;
}

//--------------------------------------------------------------------------------------------

double DistanceForBirds (CBall* b, CBall* b2)
{
    double d12 = Distance (b, b2);

    if (d12 <= b -> r / 2 + b2 -> r / 2)
    {
        double temp_x = 0;
        double temp_y = 0;

        temp_x = b -> vx;
        b -> vx = b2 -> vx;
        b2 -> vx = temp_x;

        temp_y = b -> vy;
        b -> vy = b2 -> vy;
        b2 -> vy = temp_y;
    }

    return d12;
}

//--------------------------------------------------------------------------------------------

void ChangeSprite (CBall* b)
{
    if (b -> size_x < 500) b -> size_x += 100;

    if (b -> size_x == 500) b -> size_x = 0;
}

//--------------------------------------------------------------------------------------------

void ChangeColor (CBall* b)
{
    if (b -> new_color == 0) b -> new_color = RGB(random(256), random(256), random(256));

    else
    {
        COLORREF t = b -> color;

        b -> color = b -> new_color;

        b -> new_color = t;
    }
}
