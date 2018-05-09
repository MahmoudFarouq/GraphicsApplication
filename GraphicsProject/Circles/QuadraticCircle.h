//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_QUADRATICCIRCLE_H
#define GRAPHICSPROJECT_QUADRATICCIRCLE_H

#include <cmath>
#include "Circle.h"

class QuadraticCircle : public Circle
{
public:
    QuadraticCircle(Point &center, Point &radius) : Circle(center, radius) {}
    QuadraticCircle(){}

    void readFromFile(string fileName) override
    {
        cout << "reading from file" << endl;
    }

    void writeToFile(string fileName) override
    {
        cout << "writing from file" << endl;
    }

    void draw(HDC& hdc, Point* points) override
    {
        int xc = points[0].getX();
        int yc = points[0].getY();
        int a  = points[1].getX();
        int b  = points[1].getY();

        int x = 0, y = 0;
        int r2 = (xc-a)*(xc-a) + (yc-b)*(yc-b);
        auto r = static_cast<int>(sqrt(r2));
        while (x < r)
        {
            Draw8Points(hdc, xc, yc, x, y, RGB(0,0,1));
            x++;
            y = round(sqrt(r2-x*x));
        }
    }

    static Shape* generate()
    {
        return new QuadraticCircle();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};
#endif //GRAPHICSPROJECT_QUADRATICCIRCLE_H
