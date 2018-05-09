//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_CLIRCLE_H
#define GRAPHICSPROJECT_CLIRCLE_H

#include "../Shapes/Shape.h"
#include "../Shapes/Point.h"

class Circle : public Shape
{
private:
    Point center{};
    Point radius{};  // the point on l mo7et
public:
    Circle(Point &center, Point &radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle()
    {
        this->center.set(0,0);
        this->radius.set(0,0);
    }

    ~Circle()
    {

    }

    void set(Point& center, Point& radius)
    {
        setCenter(center);
        setRadius(radius);
    }

    Point& getCenter() {
        return center;
    }

    void setCenter(Point &center) {
        this->center = center;
    }

    Point& getRadius() {
        return radius;
    }

    void setRadius(Point &radius) {
        this->radius = radius;
    }

    void Draw8Points(HDC& hdc, int xc, int yc, int a, int b, COLORREF color)
    {
        SetPixel(hdc, xc+a, yc+b, color);
        SetPixel(hdc, xc-a, yc+b, color);
        SetPixel(hdc, xc-a, yc-b, color);
        SetPixel(hdc, xc+a, yc-b, color);
        SetPixel(hdc, xc+b, yc+a, color);
        SetPixel(hdc, xc-b, yc+a, color);
        SetPixel(hdc, xc-b, yc-a, color);
        SetPixel(hdc, xc+b, yc-a, color);
    }
};


#endif //GRAPHICSPROJECT_CLIRCLE_H
