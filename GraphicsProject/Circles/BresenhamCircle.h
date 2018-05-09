//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_BRESENHAMCIRCLE_H
#define GRAPHICSPROJECT_BRESENHAMCIRCLE_H

#include "Circle.h"

class BresenhamCircle : public Circle
{
public:
    BresenhamCircle(Point &center, Point &radius) : Circle(center, radius) {}
    BresenhamCircle(){}

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
        int x = 0, y = r;
        int d = 1-r;
        int c1 = 3, c2 = 5-2*r;
        Draw8Points(hdc, xc, yc, x, y, RGB(0,0,255));
        while (x < y)
        {
            if(d < 0){
                d  += c1;
                c2 += 2;
            } else{
                d  += c2;
                c2 += 4;
                y--;
            }
            c1 += 2;
            x++;
            Draw8Points(hdc, xc, yc, x, y, RGB(0,0,255));
        }
    }

    static Shape* generate()
    {
        return new BresenhamCircle();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};


#endif //GRAPHICSPROJECT_BRESENHAMCIRCLE_H
