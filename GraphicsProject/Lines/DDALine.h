//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_DDALINE_H
#define GRAPHICSPROJECT_DDALINE_H

#include "Line.h"

class DDALine : public Line
{
public:
    DDALine(Point &start, Point &end) : Line(start, end) {}
    DDALine(){}

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
        setStart(points[0]);
        setEnd(points[1]);
        Point start = getStart();
        Point end   = getEnd();

        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();

        if(abs(dx) >= abs(dy))
        {
            int xInc = dx > 0 ? 1:-1;
            double y = start.getY();
            double yInc = (double)dy/dx*xInc;
            for(int x = start.getX(); x != end.getX(); x += xInc, y += yInc)
            {
                SetPixel(hdc, x, round(y), RGB(0,0,255));
            }
        }
        else
        {
            int yInc = dy > 0? 1:-1;
            double x = start.getX();
            double xInc = (double)dx/dy*yInc;
            for(int y = start.getY(); y != end.getY(); y += yInc, x += xInc)
            {
                SetPixel(hdc, round(x), y, RGB(0,0,255));
            }
        }
    }

    static Shape* generate()
    {
        return new DDALine();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};
#endif //GRAPHICSPROJECT_DDALINE_H
