//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#ifndef GUIGRAPHICS_LINE_H
#define GUIGRAPHICS_LINE_H

#include <windows.h>
#include "Shape.h"

class Line : public Shape {
public:
    int stx{}, sty{}, edx{}, edy{};

    void Draw() override;

    void DDA();

    void mid();

    Line() = default;

    union OutCode {
        unsigned All: 4;
        struct {
            unsigned left: 1, top: 1, right: 1, bottom: 1;
        };
    };



    OutCode GetOutCode(double x, double y);
    void rightIntersect(double xstart,double ystart,double xend,double yend,int y,double *xi,double *yi);
    void leftIntersect(double xstart,double ystart,double xend,double yend,int x,double *xi,double *yi);

    void LineClliping();

public:
    Line(int x1, int y1, int x2, int y2, HDC hdc, COLORREF color, int type);

};


#endif //GUIGRAPHICS_LINE_H
