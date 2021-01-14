//
// Created by Alaa on ١١/٠١/٢٠٢١.
//

#ifndef GUIGRAPHICS_RECTANGLEE_H
#define GUIGRAPHICS_RECTANGLEE_H

#include "Shape.h"

class Rectanglee : public Shape {
public:
    int x1{}, y1{}, x2{}, y2{};
    //    x1y1                x4y4
    //    x3y3                 x2y2

    void Draw() override;
    Rectanglee()=default;
    Rectanglee(int x1, int y1, int x2, int y2, COLORREF c, HDC hdc);
};


#endif //GUIGRAPHICS_RECTANGLEE_H
