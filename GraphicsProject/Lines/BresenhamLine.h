//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_BRESENHAMLINE_H
#define GRAPHICSPROJECT_BRESENHAMLINE_H

#include "Line.h"

class BresenhamLine : public Line
{
public:
    BresenhamLine(Point &start, Point &end) : Line(start, end) {}
    BresenhamLine() = default;

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
        if(start.getX() > end.getX())
            swap(start, end);

        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        double slope = abs((double)dy/dx);
        int yInc = 1;
        if(dy < 0){
            yInc = -1;
            dy *= yInc;
        }

        int x = start.getX();
        int y = start.getY();

        if(slope < 1 && slope > 0)
        {
            int d = dx - 2*dy;
            int change1 = 2*(dx-dy);
            int change2 = -2*dy;

            while(x != end.getX()) {
                if (d < 0) {
                    d += change1;
                    y+=yInc;
                } else {
                    d += change2;
                }
                x++;
                SetPixel(hdc, x, y, RGB(0,0,255));
            }
        }
        else if(slope > 1)
        {
            int d = 2*dx - dy;
            int change1 = 2*(dx-dy);
            int change2 = 2*dx;

            while(x != end.getX()) {
                if (d > 0) {
                    d += change1;
                    x++;
                } else {
                    d += change2;
                }
                y+=yInc;
                SetPixel(hdc, x, y, RGB(0, 0, 255));
            }
        }
    }

    static Shape* generate()
    {
        return new BresenhamLine();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};
#endif //GRAPHICSPROJECT_BRESENHAMLINE_H
