//
// Created by Alaa on ١١/٠١/٢٠٢١.
//

#include "Rectanglee.h"
#include "Line.h"

Rectanglee::Rectanglee(int x1, int y1, int x2, int y2, COLORREF c, HDC hdc) {
    //    x1y1                x4y4
    //    x3y3                 x2y2

    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->Color = c;
    this->hdc = hdc;

}

void Rectanglee::Draw() {
    //    x1y1                x4y4
    //    x3y3                 x2y2
    int x3 = x1, y3 = y2, x4 = x2, y4 = y1;
    Line(x1, y1, x3, y3, hdc, Color, 1).Draw(); //x1y1->x3y3
    Line(x3, y3, x2, y2, hdc, Color, 1).Draw(); //x3y3-?x2y2
    Line(x2, y2, x4, y4, hdc, Color, 1).Draw(); //x2y2->x4y4
    Line(x1, y1, x4, y4, hdc, Color, 1).Draw();// x4y4->x1y1

}
