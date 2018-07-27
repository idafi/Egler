#pragma once

// - - - - - -
// Integer-based rect
// - - - - - -

struct PixelRect
{
    int X, Y, Width, Height;
    
    PixelRect(int x, int y, int w, int h)
    {
        X = x;
        Y = y;
        Width = w;
        Height = h;
    }
};