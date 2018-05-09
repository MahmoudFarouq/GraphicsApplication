//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_DIRECTLINE_H
#define GRAPHICSPROJECT_DIRECTLINE_H

#include "Line.h"

class DirectLine : public Line
{
public:
    DirectLine(Point &start, Point &end) : Line(start, end) {}
    DirectLine(){}

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

        if(abs(dx) > abs(dy))
        {
            if(start.getX() > end.getX()){
                swap(start, end);
            }
            double slope = (double)dy/dx;

            int y1 = start.getY(), x1 = start.getX();
            double y;
            for(int x = start.getX(); x < end.getX(); x++)
            {
                y = (x - x1) * slope + y1;
                SetPixel(hdc, x, round(y), RGB(0,0,255));
            }
        }
        else
        {
            if(start.getY() > end.getY()){
                swap(start, end);
            }
            double slope = (double)dx/dy;

            int y1 = start.getY(), x1 = start.getX();
            double x;
            for(int y = start.getY(); y < end.getY(); y++)
            {
                x = (y - y1) * slope + x1;
                SetPixel(hdc, round(x), y, RGB(0,0,255));
            }
        }
    }

    static Shape* generate()
    {
        return new DirectLine();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};
#endif //GRAPHICSPROJECT_DIRECTLINE_H
