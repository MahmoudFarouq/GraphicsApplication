//
// Created by mahmo on 5/9/2018.
//

#ifndef GRAPHICSPROJECT_POLYGONCLIPPER_H
#define GRAPHICSPROJECT_POLYGONCLIPPER_H

#include <windows.h>
#include <vector>
#include <cmath>
#include "../Shapes/Shape.h"

using namespace std;

struct vertex
{
    double x,y;
    explicit vertex(int x1=0,int y1=0)
    {
        x=x1;
        y=y1;
    }
};

typedef vector<vertex> VertexList;
typedef bool (*IsInFunc)(vertex& v,int edge);
typedef vertex (*IntersectFunc)(vertex& v1,vertex& v2,int edge);

class PolygonClipper : Shape
{
public:
    PolygonClipper() = default;

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
        int n = 4;
        int xLeft = points[0].getX();
        int yTop  = points[0].getY();
        int xRight   = points[1].getX();
        int yBottom  = points[1].getY();
        Rectangle(hdc, xLeft, yTop, xRight, yBottom);
        PolygonClip(hdc, points+2, n,xLeft, yTop, xRight, yBottom);
    }

    static Shape* generate()
    {
        return new PolygonClipper();
    }

    string toString() override
    {
        cout << "hi from here" << endl;
        return "";
    }

private:
    void PolygonClip(HDC hdc,Point *p,int n,int xleft,int ytop,int xright,int ybottom)
    {
        VertexList vlist;
        for(int i=0; i<n; i++)
            vlist.emplace_back(vertex(p[i].getX(),p[i].getY()));
        vlist=ClipWithEdge(vlist,xleft,InLeft,VIntersect);
        vlist=ClipWithEdge(vlist,ytop, InTop, HIntersect);
        vlist=ClipWithEdge(vlist,xright,InRight,VIntersect);
        vlist=ClipWithEdge(vlist,ybottom,InBottom,HIntersect);
        vertex v1=vlist[vlist.size()-1];
        for (auto v2 : vlist) {
            MoveToEx(hdc, round(v1.x), round(v1.y), nullptr);
            LineTo(hdc, round(v2.x), round(v2.y));
            v1=v2;
        }
    }
    static VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect)
    {
        VertexList OutList;
        vertex v1=p[p.size()-1];
        bool v1_in=In(v1,edge);
        for (auto v2 : p) {
            bool v2_in=In(v2,edge);
            if(!v1_in && v2_in)
            {
                OutList.push_back(Intersect(v1,v2,edge));
                OutList.push_back(v2);
            }
            else if(v1_in && v2_in) OutList.push_back(v2);
            else if(v1_in) OutList.push_back(Intersect(v1,v2,edge));
            v1=v2;
            v1_in=v2_in;
        }
        return OutList;
    }
    static bool InLeft(vertex& v,int edge)
    {
        return v.x>=edge;
    }
    static bool InRight(vertex& v,int edge)
    {
        return v.x<=edge;
    }
    static bool InTop(vertex& v,int edge)
    {
        return v.y>=edge;
    }
    static bool InBottom(vertex& v,int edge)
    {
        return v.y<=edge;
    }
    static vertex VIntersect(vertex& v1,vertex& v2,int xedge)
    {
        vertex res;
        res.x=xedge;
        res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
        return res;
    }
    static vertex HIntersect(vertex& v1,vertex& v2,int yedge)
    {
        vertex res;
        res.y=yedge;
        res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
        return res;
    }
};

#endif //GRAPHICSPROJECT_POLYGONCLIPPER_H
