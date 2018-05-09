//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_CURVE_H
#define GRAPHICSPROJECT_CURVE_H

#include "../Shapes/Shape.h"

class Curve : public Shape
{
public:
    double* mult(double mat[4][4], double vec[4])
    {
        double* res = new double[4];
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                res[i] += mat[i][j]*vec[j];
            }
        }
        return res;
    }

    double dot(double a[4], double b[4])
    {
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]+ a[3]*b[3];
    }

    double* GetHermitCoeff(double x0, double s0, double x1, double s1)
    {
        static double basis[4][4] = {2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0};
        double v[4] = {x0, s0, x1, s1};
        return mult(basis, v);
    }

    void Draw(HDC& hdc, Point &p0, Point& t0, Point& p1, Point& t1, int numPoints)
    {
        double* xcoeff = GetHermitCoeff(p0.getX(), t0.getX(), p1.getX(), t1.getX());
        double* ycoeff = GetHermitCoeff(p0.getY(), t0.getY(), p1.getY(), t1.getY());
        double dt = 1.0/(numPoints - 1);
        for(double t = 0; t < 1.0; t+=dt)
        {
            auto * vt = new double[4];
            vt[3] = 1;
            for(int i = 2; i >= 0; i--) {
                vt[i] = vt[i+1] * t;
            }
            int x = round(dot(xcoeff, vt));
            int y = round(dot(ycoeff, vt));
            SetPixel(hdc, x, y, RGB(0,0,255));
        }
    }
};

#endif //GRAPHICSPROJECT_CURVE_H
