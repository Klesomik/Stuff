#include <cstdio>
#include <cstdarg>
#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"

void adCreateWindow (int width, int height, const char* header);
void adTextOut (int x, int y, const char* label, ...);

void adCreateWindow (int width, int height, const char* header)
{
    txCreateWindow (width, height);

    SetWindowText (txWindow (), header);
}

void adTextOut (int x, int y, const char* label, ...)
{
    int size = 100;

    char* buffer = new char[size];

    va_list args;

    va_start (args, label);

    while (vsprintf (buffer, label, args) == size)
    {
        size *= 2;

        delete[] buffer;
                 buffer = new char[size];
    }

    va_end (args);

    txTextOut (x, y, buffer);
}
