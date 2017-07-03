#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "TXLib.h"

class Game
{
    public:
        Game (int size_x, int size_y);

        void spawn ();

        void up ();
        void down ();
        void left ();
        void right ();

        void render ();

        void dump ();

        std::vector <std::vector <int>>& data ();
        int& score ();

    private:
        std::vector <std::vector <int>> data_;

        int score_;
};

Game::Game (int size_x, int size_y):
    data_ (size_x, std::vector <int> (size_y)),
    score_ (0)
{
    srand (time (NULL));
}

void Game::spawn ()
{
    int x = rand () % data_.size ();
    int y = rand () % data_[0].size ();

    int value = 2 * ((rand () % 2) + 1);

    if (data_[x][y] == 0)
        data_[x][y] = value;
}

void Game::up ()
{
    for (int j = 0; j < data_[0].size (); j++)
    {
        for (int i = 0; i < (int) data_.size (); i++)
        {
            for (int t = i; t >= 1;)
            {
                if ((data_[t - 1][j] == data_[t][j]) || (data_[t - 1][j] == 0))
                {
                    data_[t - 1][j] += data_[t][j];

                    data_[t][j] = 0;

                    t--;
                }

                else
                    break;
            }
        }
    }
}

void Game::down ()
{
    for (int j = 0; j < data_[0].size (); j++)
    {
        for (int i = (int) data_.size () - 1; i >= 0; i--)
        {
            for (int t = i; t < data_.size () - 1;)
            {
                if ((data_[t + 1][j] == data_[t][j]) || (data_[t + 1][j] == 0))
                {
                    data_[t + 1][j] += data_[t][j];

                    data_[t][j] = 0;

                    t++;
                }

                else
                    break;
            }
        }
    }
}

void Game::left ()
{
    for (int i = 0; i < data_.size (); i++)
    {
        for (int j = 0; j < data_[0].size (); j++)
        {
            for (int t = j; t >= 1;)
            {
                if ((data_[i][t - 1] == data_[i][t]) || (data_[i][t - 1] == 0))
                {
                    data_[i][t - 1] += data_[i][t];

                    data_[i][t] = 0;

                    t--;
                }

                else
                    break;
            }
        }
    }
}

void Game::right ()
{
    for (int i = 0; i < data_.size (); i++)
    {
        for (int j = (int) data_[0].size () - 1; j >= 0; j--)
        {
            for (int t = j; t < data_[0].size () - 1;)
            {
                if ((data_[i][t + 1] == data_[i][t]) || (data_[i][t + 1] == 0))
                {
                    data_[i][t + 1] += data_[i][t];

                    data_[i][t] = 0;

                    t++;
                }

                else
                    break;
            }
        }
    }
}

void Game::render ()
{
}

void Game::dump ()
{
    for (int i = 0; i < data_.size (); i++)
    {
        for (int j = 0; j < data_[i].size (); j++)
            std::cout << data_[i][j] << ' ';

        std::cout << '\n';
    }
}

std::vector <std::vector <int>>& Game::data ()
{
    return data_;
}

int& Game::score ()
{
    return score_;
}

int main ()
{
    txCreateWindow (800, 600);

    Game data (4, 4);

    while (true)
    {
        data.spawn ();

        system ("cls");
        data.dump ();

        for (bool flag = false; !flag;)
        {
            if (GetAsyncKeyState (VK_UP))
                { data.up (); flag = true; }

            else if (GetAsyncKeyState (VK_DOWN))
                { data.down (); flag = true; }

            else if (GetAsyncKeyState (VK_LEFT))
                { data.left (); flag = true; }

            else if (GetAsyncKeyState (VK_RIGHT))
                { data.right (); flag = true; }
        }

        txSleep (150);
    }

    return 0;
}
