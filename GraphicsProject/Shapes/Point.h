//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_POINT_H
#define GRAPHICSPROJECT_POINT_H

#include <iostream>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Point( Point& point)
    {
        this->x = point.x;
        this->y = point.y;
    }

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    void operator=(Point& point)
    {
        this->x = point.x;
        this->y = point.y;
    }

    void set(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    friend ostream &operator<<(ostream& output, Point &point)
    {
        output << "Point{X: " << point.x << ", Y: " << point.y << "}";
        return output;
    }
};

#endif //GRAPHICSPROJECT_POINT_H
