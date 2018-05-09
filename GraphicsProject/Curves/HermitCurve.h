//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_HERMITCURVE_H
#define GRAPHICSPROJECT_HERMITCURVE_H

#include "Curve.h"

class HermitCurve : public Curve
{
public:
    HermitCurve() = default;

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
        Point p0 = points[0],
                t0 = points[1],
                p1 = points[2],
                t1 = points[3];

        Draw(hdc, p0, t0, p1, t1, numPoints);
    }

    static Shape* generate()
    {
        return new HermitCurve();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }
};
#endif //GRAPHICSPROJECT_HERMITCURVE_H
