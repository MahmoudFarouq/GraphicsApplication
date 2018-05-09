//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_BEZIERCURVE_H
#define GRAPHICSPROJECT_BEZIERCURVE_H

#include "Curve.h"

class BezierCurve : public Curve
{
public:
    BezierCurve() = default;

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
        int numPoints = 200;
        Point   p0 = points[0],
                t0(3*(points[1].getX()-p0.getX()), 3*(points[1].getY()-p0.getY())),
                p1 = points[2],
                t1(3*(points[3].getX()-p1.getX()), 3*(points[3].getY()-p1.getY()));
        Draw(hdc, p0, t0, p1, t1, numPoints);
    }

    static Shape* generate()
    {
        return new BezierCurve();
    }

    string toString() override {
        cout << "hi from here" << endl;
        return "";
    }
};

#endif //GRAPHICSPROJECT_BEZIERCURVE_H
