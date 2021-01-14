//
// Created by Alaa on ٠٢/٠١/٢٠٢١.
//

#ifndef GUIGRAPHICS_CIRCLE_H
#define GUIGRAPHICS_CIRCLE_H


class Circle : public Shape {
    int xc{}, yc{}, Rad{}, q = -1;

    void Draw() override;

    void cartesian();

    void Draw8Points(int x, int y);

    void MidPoint();

    void MidPointMod();
    void Polar();


public:
    Circle() = default;

    Circle(int x1, int y1, int x2, int y2, HDC hdc, COLORREF color, int type,int q);
};


#endif //GUIGRAPHICS_CIRCLE_H
