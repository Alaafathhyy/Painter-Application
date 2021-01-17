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

     for(double x=A;x >= 0;x-=0.02) {
         double y  = abs(B * sqrt(1 - ((x * x) / (A * A))));
        SETPIXEL(xc + round(x), yc + round(y));
        SETPIXEL(xc + round(x), yc - round(y));
        SETPIXEL(xc - round(x), yc + round(y));
        SETPIXEL(xc - round(x), yc - round(y));
    }

}


Ellipsee::Ellipsee(int xc, int yc, int A, int B, HDC hdc, COLORREF Color, int Type) {
    this->xc = xc;
    this->yc = yc;
    this->A = A;
    this->B = B;
    this->hdc = hdc;
    this->kind = Type;
    this->Color = Color;


}

void Ellipsee::polar() {

    double x = 0;
    double y = B;
    double range = A;

    for (double angle = 0; angle <= range; angle += 0.05) {
        SETPIXEL((int) (xc + x), (int) (yc + y));
        SETPIXEL((int) (xc + x), (int) (yc - y));
        SETPIXEL((int) (xc - x), (int) (yc - y));
        SETPIXEL((int) (xc - x), (int) (yc + y));
        x = (A * cos(angle));
        y = (B * sin(angle));
    }
}


