#include "..//..//TXLib.h"

void Init (std::vector <std::pair <int, int>>& coords);
void DrawField (const int field_size);
void SetCells (std::vector <std::vector <bool>>& data);
void CheckNew (std::vector <std::vector <bool>>& data);
void Recount (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords);
void DrawSells (std::vector <std::vector <bool>>& data);
void DayOfLife (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords);
void Play (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords);

int main ()
{
    const int table_size = 12;

    std::vector <std::vector <bool>> data (table_size, std::vector <bool> (table_size));
    std::vector <std::pair <int, int>> coords (8);

    Init (coords);

    DrawField (table_size);

    SetCells (data);

    Play (data, coords);

    return 0;
}

void Init (std::vector <std::pair <int, int>>& coords)
{
    txCreateWindow (600, 600);
    txTextCursor (false);

    coords = { { -1, -1 },
               { -1, +0 },
               { -1, +1 },
               { +0, +1 },
               { +1, +1 },
               { +1, +0 },
               { +1, -1 },
               { +0, -1 }  };
}

void DrawField (const int field_size)
{
    txSetColor (TX_GRAY);

    for (int x = 0; x <= 600; x += 50)
        txLine (x, 0, x, 600);

    for (int y = 0; y <= 600; y += 50)
        txLine (0, y, 600, y);
}

void SetCells (std::vector <std::vector <bool>>& data)
{
    while (!GetAsyncKeyState (VK_SHIFT))
        CheckNew (data);
}

void CheckNew (std::vector <std::vector <bool>>& data)
{
    if (txMouseButtons () == 1)
    {
        int x = txMouseX (), y = txMouseY ();

        COLORREF color = !data[y / 50][x / 50]? TX_YELLOW : TX_BLACK;

        txSetColor (color);
        txSetFillColor (color);

        txRectangle (x - x % 50 + 2, y - y % 50 + 2, x - x % 50 + 50 - 1, y - y % 50 + 50 - 1);

        data[y / 50][x / 50] = !data[y / 50][x / 50];

        txSleep (125);
    }
}

void Recount (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords)
{
    std::vector <std::vector <bool>> tmp (12, std::vector <bool> (12));

    for (int i = 0; i < data.size (); i++)
    {
        for (int j = 0; j < data[i].size (); j++)
        {
            int counter = 0;

            for (int t = 0; t < coords.size (); t++)
            {
                int move_x = i + coords[t].first,
                    move_y = j + coords[t].second;

                if (move_x >= 0 && move_x < data.size () && move_y >= 0 && move_y < data[0].size () && data[move_x][move_y])
                    counter++;
            }

            if (counter == 3 && !data[i][j])
                tmp[i][j] = true;

            else if (counter != 2 && counter != 3 && data[i][j])
                tmp[i][j] = false;

            else
                tmp[i][j] = data[i][j];
        }
    }

    std::swap (data, tmp);
}

void DrawSells (std::vector <std::vector <bool>>& data)
{
    for (int i = 0; i < data.size (); i++)
    {
        for (int j = 0; j < data[i].size (); j++)
        {
            COLORREF color = data[i][j]? TX_YELLOW : TX_BLACK;

            txSetColor (color);
            txSetFillColor (color);

            txRectangle (j * 50 + 2, i * 50 + 2, j * 50 + 50 - 1, i * 50 + 50 - 1);
        }
    }
}

void DayOfLife (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords)
{
    txBegin ();

    CheckNew (data);

    Recount (data, coords);

    DrawSells (data);

    txSleep (125);

    txEnd ();
}

void Play (std::vector <std::vector <bool>>& data, std::vector <std::pair <int, int>>& coords)
{
    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        if (GetAsyncKeyState (VK_SPACE))
        {
            txSleep (125);

            while (!GetAsyncKeyState (VK_SPACE))
            {
                if (GetAsyncKeyState (VK_RIGHT))
                    DayOfLife (data, coords);

                CheckNew (data);
            }
        }

        DayOfLife (data, coords);
    }
}
