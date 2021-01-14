//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#include "Ellipsee.h"

void Ellipsee::Draw() {
    if (this->kind)
        this->polar();
    else this->Direct();

}

void Ellipsee::Direct() {

    double AA, BB, x, y;
    x = 0;
    y = B;
    AA = A * A;
    BB = B * B;
    while (x <= A ) {
        SETPIXEL(cx + round(x), cy + round(y));
        SETPIXEL(cx + round(x), cy - round(y));
        SETPIXEL(cx - round(x), cy + round(y));
        SETPIXEL(cx - round(x), cy - round(y));
        x += 0.01;
        y = sqrt((AA * BB - BB * (x * x)) / AA);
    }


}

Ellipsee::Ellipsee(int cx, int cy, int A, int B, HDC hdc, COLORREF Color, int Type) {
    this->cx = cx;
    this->cy = cy;
    this->A = A;
    this->B = B;
    this->hdc = hdc;
    this->kind = Type;
    this->Color = Color;


}

void Ellipsee::polar() {

    double x = 0;
    double y = B;
    double angle = 0;
    double range = A;

    while (angle <= range) {
        SETPIXEL((int) (cx + x + 0.5), (int) (cy + y + 0.5));
        SETPIXEL((int) (cx + x + 0.5), (int) (cy - y + 0.5));
        SETPIXEL((int) (cx - x + 0.5), (int) (cy - y + 0.5));
        SETPIXEL((int) (cx - x + 0.5), (int) (cy + y + 0.5));

        angle += 0.05;
        x = (A * cos(angle));
        y = (B * sin(angle));
    }
}


