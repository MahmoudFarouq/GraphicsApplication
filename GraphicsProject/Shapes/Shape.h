//
// Created by mahmo on 5/7/2018.
//
#include <iostream>
#include "Point.h"

using namespace std;

#ifndef GRAPHICSPROJECT_SHAPE_H
#define GRAPHICSPROJECT_SHAPE_H

#include "windows.h"

class Shape
{
public:
    virtual void writeToFile(string fileName) = 0;
    virtual void readFromFile(string fileName) = 0;
    virtual void draw(HDC& hdc, Point* points) = 0;
    virtual string toString() = 0;

    double getSlope(Point& start, Point& end)
    {
        return (double)(end.getY()-start.getY())/(end.getX()-start.getX());
    }

    static void swap(Point& first, Point& second)
    {
        Point temp = first;
        first = second;
        second = temp;
    }

    int round(double x)
    {
        return static_cast<int>(x+0.5);
    }
};

#endif //GRAPHICSPROJECT_SHAPE_H

