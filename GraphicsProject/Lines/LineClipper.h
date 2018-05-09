//
// Created by mahmo on 5/9/2018.
//

#ifndef GRAPHICSPROJECT_LINECLIPPER_H
#define GRAPHICSPROJECT_LINECLIPPER_H

#include "windows.h"
#include <cmath>
#include "../Shapes/Point.h"
#include "../Lines/Line.h"
#include "../Polygons/MyNthPolygon.h"

union OutCode
{
    unsigned all:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

//CohenSuth
class LineClipper : public Line
{
public:
    LineClipper(Point &start, Point &end) : Line(start, end) {}
    LineClipper() = default;

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
        int xLeft = points[0].getX();
        int yTop  = points[0].getY();
        int xRight   = points[1].getX();
        int yBottom  = points[1].getY();
        double x1 = points[2].getX();
        double y1 = points[2].getY();
        double x2 = points[3].getX();
        double y2 = points[3].getY();
        Rectangle(hdc, xLeft, yTop, xRight, yBottom);
        lineClipping(hdc, x1, y1, x2, y2, xLeft, yTop, xRight, yBottom, RGB(0,0,255));
    }

    static Shape* generate()
    {
        return new LineClipper();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }

private:
    void lineClipping(HDC hdc, double xs, double ys, double xe, double ye, int xLeft, int yTop, int xRight, int yBottom, COLORREF color)
    {
        OutCode out1 = GetOutCode(xs, ys, xLeft, yTop, xRight, yBottom);
        OutCode out2 = GetOutCode(xe, ye, xLeft, yTop, xRight, yBottom);
        while ((out1.all || out2.all) && !(out1.all & out2.all))
        {
            double xi, yi;
            if (out1.all)
            {
                if (out1.left)
                {
                    HIntersect(xs, ys, xe, ye, xLeft, xi, yi);
                }
                else if (out1.right)
                {
                    HIntersect(xs, ys, xe, ye, xRight, xi, yi);
                }
                else if (out1.top)
                {
                    HIntersect(xs, ys, xe, ye, yTop, xi, yi);
                }
                else
                {
                    HIntersect(xs, ys, xe, ye, yBottom, xi, yi);
                }
                xs = xi;
                ys = yi;
                out1 = GetOutCode(xs, ys, xLeft, yTop, xRight, yBottom);
            }
            else
            {
                if (out2.left)
                {
                    VIntersect(xs, ys, xe, ye, xLeft, xi, yi);
                }
                else if (out2.right)
                {
                    VIntersect(xs, ys, xe, ye, xRight, xi, yi);
                }
                else if (out2.top)
                {
                    HIntersect(xs, ys, xe, ye, yTop, xi, yi);
                }
                else
                {
                    HIntersect(xs, ys, xe, ye, yBottom, xi, yi);
                }
                xe = xi;
                ye = yi;
                out2 = GetOutCode(xe, ye, xLeft, yTop, xRight, yBottom);
            }
        }
        if (!out1.all && !out2.all)
        {
            MoveToEx(hdc, (int)xs, (int)ys, nullptr);
            LineTo(hdc, (int)xe, (int)ye);
        }
    }

    void VIntersect(double xs, double ys, double xe, double ye, int xEdge, double& xi, double& yi)
    {
        xi = xEdge;
        yi = ((xEdge - xs)*(ye - ys) / (xe - xs)) + ys;
    }

    void HIntersect(double xs, double ys, double xe, double ye, int yEdge, double& xi, double& yi)
    {
        yi = yEdge;
        xi = ((yEdge - ys)*(xe - xs) / (ye - ys)) + xs;
    }

    OutCode GetOutCode(double x, double y, int xLeft, int yTop, int xRight, int yBottom)
    {
        OutCode result{};
        result.all = 0;
        if (x < xLeft)       result.left = 1;
        else if (x > xRight) result.right = 1;
        if (y > yBottom)     result.bottom = 1;
        else if (y < yTop)   result.top = 1;
        return result;
    }
};


#endif //GRAPHICSPROJECT_LINECLIPPER_H
