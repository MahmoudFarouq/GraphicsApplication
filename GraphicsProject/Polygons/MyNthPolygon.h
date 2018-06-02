//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_POLYGON_H
#define GRAPHICSPROJECT_POLYGON_H

#include "vector"
#include "../Shapes/Point.h"
#include "../Shapes/Shape.h"
#include "../Lines/DDALine.h"
#include "../Fillers/Filler.h"

using namespace std;

class MyNthPolygon : public Shape
{
private:
    int numOfPoints{};
    bool filled = false;
public:
    vector<Point*> points{};

    explicit MyNthPolygon(vector<Point*> &points)
    {
        this->points = points;
        numOfPoints = points.size();
        this->numOfPoints = 0;
    }

    explicit MyNthPolygon(int numOfPoints)
    {
        this->numOfPoints = numOfPoints;
    }

    int getNumOfPoints() const {
        return numOfPoints;
    }

    void draw(HDC& hdc, Point* points) override
    {
        for(int i = 0; i < numOfPoints; i++){
            this->points.push_back(&points[i]);
        }
        auto * lineDrawer = new DDALine();
        for(int i = 0; i < this->points.size(); i++)
        {
            Point p[2] = {*this->points[i], *this->points[(i+1)%numOfPoints]};
            lineDrawer->draw(hdc, p);
        }
    }

    void fill(HDC& hdc)
    {
        if(filled) {
            cout << "Already Filled" << endl;
            return;
        }
        filled = true;
        Filler::ConvexFill(hdc, points, RGB(0,0,255));
    }

    void readFromFile(string fileName) override
    {
        cout << "reading from file" << endl;
    }

    void writeToFile(string fileName) override
    {
        cout << "writing from file" << endl;
    }

    static Shape* generate(int numOfPoints)
    {
        return new MyNthPolygon(numOfPoints);
    }

    string toString() override
    {
        return "hi from here";
    }
};

#endif //GRAPHICSPROJECT_POLYGON_H
