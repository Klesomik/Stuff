struct Ball
{
    Ball ();

    void control ();
    void move ();
    void render ();

    Math::VectorD2 coords, speed;

    double radius, mass;

    COLORREF color;
};

Ball::Ball ():
    coords (),
    speed  (),
    radius (),
    mass   (),
    color  ()
{
    radius = random (2, 50);
    mass   = random (2, 50);
    color  = RGB (random (0, 255), random (0, 255), random (0, 255));
    coords = { random (0 + radius, txGetExtentX () - radius), random (0 + radius, txGetExtentY () - radius) };
    speed  = { random (0, 5), random (0, 5) };
}

void Ball::control ()
{
}

void Ball::move ()
{
    coords += speed;
}

void Ball::render ()
{
    txSetColor (color);
    txSetFillColor (color);

    txCircle (coords[0], coords[1], radius);
}
