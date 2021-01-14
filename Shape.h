//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//


#ifndef GUIGRAPHICS_SHAPE_H
#define GUIGRAPHICS_SHAPE_H

#include <windows.h>


class Shape {

public:
    virtual void Draw() = 0;

    static int xx1, yy1, xx2, yy2;

    void SETPIXEL(int x, int y) {
        if (xx1 > xx2)
            swap(xx1, xx2);
        if (yy1 > yy2)
            swap(yy1, yy2);
        if (xx1 <= x && x <= xx2 && yy1 <= y && y <= yy2)
            SetPixel(hdc, x, y, Color);
    }

protected:
    static int Round(double x) {
        return (int) (x + 0.5);
    }

    int min(int x, int y) {
        return (x < y ? x : y);
    }

    int max(int x, int y) {
        return (x > y ? x : y);
    }

    void swap(int &x, int &y) {
        int temp = x;
        x = y;
        y = temp;
    }

    COLORREF Color = RGB(0, 0, 0);
    HDC hdc;
    int kind;
};



#endif //GUIGRAPHICS_SHAPE_H
