//
// Created by mahmo on 5/7/2018.
//

#include "../Shapes/Shape.h"
#include "../Shapes/Point.h"

#ifndef GRAPHICSPROJECT_LINE_H
#define GRAPHICSPROJECT_LINE_H

class Line : public Shape
{
private:
    Point start;
    Point end;
public:
    Line(Point &start, Point &end)
    {
        setStart(start);
        setEnd(end);
    }

    Line()
    {
        this->start.set(0,0);
        this->end.set(0,0);
    }

    ~Line()
    {}

    Point& getStart() {
        return start;
    }

    void setStart(Point &start) {
        this->start = start;
    }

    Point& getEnd() {
        return end;
    }

    void setEnd(Point &end) {
        this->end = end;
    }
};

#endif //GRAPHICSPROJECT_LINE_H
