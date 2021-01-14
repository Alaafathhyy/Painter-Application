//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#ifndef GUIGRAPHICS_ELLIPSEE_H
#define GUIGRAPHICS_ELLIPSEE_H

#include "Shape.h"

class Ellipsee : public Shape {
    int cx{};
    int cy{};
    int A = 0;
    int B = 0;

    void Draw() override;

    void Direct();

    void polar();

public:
    Ellipsee(int cx, int cy, int A, int B, HDC hdc, COLORREF Color, int Type);

    Ellipsee()=default;
};


#endif //GUIGRAPHICS_ELLIPSEE_H
