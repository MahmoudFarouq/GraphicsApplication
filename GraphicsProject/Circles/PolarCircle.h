//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_POLARCIRCLE_H
#define GRAPHICSPROJECT_POLARCIRCLE_H


#include <cmath>
#include "Circle.h"

class PolarCircle : public Circle
{
public:
    PolarCircle(Point &center, Point &radius) : Circle(center, radius) {}
    PolarCircle(){}

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

        int r2 = (xc-a)*(xc-a) + (yc-b)*(yc-b);
        auto r = static_cast<int>(sqrt(r2));
        int x = r, y = 0;
        double theta=0, dtheta = 1.0/r;
        Draw8Points(hdc,xc,yc,x,y, RGB(0,0,255));
        while(x>y)
        {
            theta += dtheta;
            x=round(r*cos(theta));
            y=round(r*sin(theta));
            Draw8Points(hdc,xc,yc,x,y, RGB(0,0,255));
        }
    }

    static Shape* generate()
    {
        return new PolarCircle();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};

#endif //GRAPHICSPROJECT_POLARCIRCLE_H
