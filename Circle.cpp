//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#include "Circle.h"
#include <cmath>
#include <iostream>
#include "Line.h"

using namespace std;

void Circle::Draw8Points(int x, int y) {
    SETPIXEL(xc + x, yc + y);
    SETPIXEL(xc - x, yc + y);
    SETPIXEL(xc - x, yc - y);
    SETPIXEL(xc + x, yc - y);
    SETPIXEL(xc + y, yc + x);
    SETPIXEL(xc - y, yc + x);
    SETPIXEL(xc - y, yc - x);
    SETPIXEL(xc + y, yc - x);
    if (q == 2)Line(xc, yc, xc + y, yc - x, hdc, Color, 1).Draw();
    else if (q == 1)Line(xc, yc, xc + x, yc - y, hdc, Color, 1).Draw();
    else if (q == 4)Line(xc, yc, xc + x, yc + y, hdc, Color, 1).Draw();
    else if (q == 3)Line(xc, yc, xc + y, yc + x, hdc, Color, 1).Draw();
    else if (q == 6)Line(xc, yc, xc - y, yc + x, hdc, Color, 1).Draw();
    else if (q == 5)Line(xc, yc, xc - x, yc + y, hdc, Color, 1).Draw();
    else if (q == 8)Line(xc, yc, xc - x, yc - y, hdc, Color, 1).Draw();
    else Line(xc, yc, xc - y, yc - x, hdc, Color, 1).Draw();

}

Circle::Circle(int x1, int y1, int x2, int y2, HDC hdc, COLORREF c, int type, int q) {
    kind = type;
    Color = c;
    this->hdc = hdc;
    xc = x1, yc = y1;
    int dx = x2 - x1, dy = y2 - y1;
    Rad = (int) sqrt(dx * dx + dy * dy);
    this->q = q;
}

void Circle::Draw() {
    switch (kind) {
        case 0: {
            this->cartesian();
        }
        case 1: {
            this->Polar();
        }
        case 2: {
            this->MidPoint();
        }
        case 3: {
            this->MidPointMod();
        }
    }
}

void Circle::MidPoint() {
    int y = Rad;
    int x = 0;
    Draw8Points(x, y);
    int d = 1 - Rad;
    int change1 = 5 - 2 * Rad;;
    int change2 = 3;
    while (x < y) {
        if (d >= 0) {
            d += change1;
            change1 += 4;
            y--;
        } else {
            d += change2;
            change1 += 2;
        }
        change2 += 2;
        x++;
        Draw8Points(x, y);
    }

}

void Circle::MidPointMod() {

    int x = 0, y = Rad;
    int d = 1 - Rad;
    int c1 = 3, c2 = 5 - 2 * Rad;
    Draw8Points(x, y);
    while (x < y) {
        if (d < 0) {
            d += c1;
            c2 += 2;
        } else {
            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        x++;
        Draw8Points(x, y);
    }
}


void Circle::Polar() {
    double x = 0, y = Rad;
    double dtheta = 1.0 / Rad;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    //Draw8Points(xc, yc);
    while (x <y-1) {
        double y1 = x * sdtheta + y * cdtheta;
        x = x * sdtheta + y * cdtheta;
        y = y1;
        Draw8Points(round(x), round(y));
    }

}

void Circle::cartesian() {
    int x = 0;
    int y = Rad;
    while (x <y) {
        x++;
        y = Round(sqrt(Rad * Rad - y * y));
        Draw8Points(x, y);
    }

}

