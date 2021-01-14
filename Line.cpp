//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#include "Line.h"
#include <cmath>

void Line::Draw() {
    if (this->kind == 1) this->mid();
    else if (this->kind == 0) this->DDA();
    else this->LineClliping();
}

void Line::DDA() {
    int dx = edx - stx;
    int dy = edy - sty;
    if (abs(dy) <= abs(dx)) {
        double slope = (dy * 1.0) / dx;
        if (stx > edx) {
            swap(stx, edx);
            swap(sty, edy);
        }
        int x = stx;
        double y = sty;
        SETPIXEL(x, y);
        while (x <= edx) {
            x++;
            y += slope;
            SETPIXEL(x, y);
        }
    } else {
        double slope = (dx * 1.0) / dy;
        if (sty > edy) {
            swap(stx, edx);
            swap(sty, edy);
        }
        double x = stx;
        int y = sty;
        SETPIXEL(x, y);
        while (y <= edy) {
            y++;
            x += slope;
            SETPIXEL(x, y);
        }
    }
}

void Line::mid() {

    int dx = edx - stx;
    int dy = edy - sty;
    double slope = (dy * 1.0) / dx;
    if ((abs(dy) <= abs(dx)) && (slope >= 0)) {
        if (stx > edx) {
            swap(stx, edx);
            swap(sty, edy);
        }
        double d = (edx - stx) - 2 * (edy - sty);
        double change1 = 2 * (edx - stx) - 2 * (edy - sty);
        double change2 = -2 * (edy - sty);
        int x = stx;
        int y = sty;
        SETPIXEL(x, y);
        while (x <= edx) {
            if (d <= 0) {
                y++;
                d += change1;
            } else {
                d += change2;
            }
            x++;
            SETPIXEL(x, y);
        }
    } else if ((abs(dy) > abs(dx)) && (slope > 0)) {
        if (sty > edy) {
            swap(stx, edx);
            swap(sty, edy);
        }
        double d = 2 * (edx - stx) - (edy - sty);
        double change1 = 2 * (edx - stx);
        double change2 = 2 * ((edx - stx) - (edy - sty));
        int x = stx;
        int y = sty;
        SETPIXEL(x, y);
        while (y <= edy) {
            if (d < 0) {
                d += change1;
            } else {
                x++;
                d += change2;
            }
            y++;
            SETPIXEL(x, y);
        }

    } else if ((slope < 0) && (abs(dy) <= abs(dx))) {
        if (stx > edx) {
            swap(stx, edx);
            swap(sty, edy);
        }
        int x = stx;
        int y = sty;
        double d = -(edx - stx) - 2 * (edy - sty);
        double change1 = -2 * (edy - sty);
        double change2 = -2 * ((edx - stx) + (edy - sty));
        SETPIXEL(x, y);
        while (x <= edx) {
            if (d < 0) {
                d += change1;
            } else {
                y--;
                d += change2;
            }
            x++;
            SETPIXEL(x, y);
        }

    } else {
        if (sty > edy) {
            swap(stx, edx);
            swap(sty, edy);
        }
        int x = stx;
        int y = sty;
        double d = 2 * (edx - stx) + (edy - sty);
        double change1 = 2 * (edx - stx);
        double change2 = 2 * ((edx - stx) + (edy - sty));
        SETPIXEL(x, y);
        while (y <= edy) {
            if (d > 0) {
                d += change1;
            } else {
                d += change2;
                x--;
            }
            y++;
            SETPIXEL(x, y);
        }
    }
}

Line::Line(int stx, int sty, int edx, int edy, HDC hdc, COLORREF color, int type) {
    this->hdc = hdc;
    kind = type;
    this->stx = stx, this->sty = sty, this->edx = edx, this->edy = edy;
    this->Color = color;
}


void Line::LineClliping() {

    //right>left
    // xx2>xx1
    //bottom>up
    // yy2>yy1
    OutCode out1 = GetOutCode(stx, sty);
    OutCode out2 = GetOutCode(edx, edy);
    while ((out1.All || out2.All) && !(out1.All & out2.All)) {
        double xi, yi;
        if (out1.All) {
            if (out1.left)
                leftIntersect(stx, sty, edx, edy, xx1, &xi, &yi);
            else if (out1.top)
                rightIntersect(stx, sty, edx, edy, yy1, &xi, &yi);
            else if (out1.right)
                leftIntersect(stx, sty, edx, edy, xx2, &xi, &yi);
            else
                rightIntersect(stx, sty, edx, edy, yy2, &xi, &yi);
            stx = Round(xi);
            sty = Round(yi);
            out1 = GetOutCode(stx, sty);
        } else {
            if (out2.left)
                leftIntersect(stx, sty, edx, edy, xx1, &xi, &yi);
            else if (out2.top)
                rightIntersect(stx, sty, edx, edy, yy1, &xi, &yi);
            else if (out2.right)
                leftIntersect(stx, sty, edx, edy, xx2, &xi, &yi);
            else
                rightIntersect(stx, sty, edx, edy, yy2, &xi, &yi);
            edx = Round(xi);
            edy = Round(yi);
            out2 = GetOutCode(edx, edy);
        }
    }
    if (!out1.All && !out2.All) {
        Line(stx, sty, edx, edy, hdc, Color, 1).Draw();
    }


}


Line::OutCode Line::GetOutCode(double x, double y) {
    OutCode out;
    out.All = 0;
    if (x < xx1)
        out.left = 1;
    else if (x > xx2)
        out.right = 1;
    if (y < yy1)
        out.top = 1;
    else if (y > yy2)
        out.bottom = 1;
    return out;
}

void Line::rightIntersect(double xstart, double ystart, double xend, double yend, int y, double *xi, double *yi) {
    *yi = y;
    *xi = xstart + (y - ystart) * (xend - xstart) / (yend - ystart);
}

void Line::leftIntersect(double xstart, double ystart, double xend, double yend, int x, double *xi, double *yi) {
    *xi = x;
    *yi = ystart + (x - xstart) * (yend - ystart) / (xend - xstart);
}

