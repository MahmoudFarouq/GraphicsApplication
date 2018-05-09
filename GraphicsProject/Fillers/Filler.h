//
// Created by mahmo on 5/9/2018.
//

#ifndef GRAPHICSPROJECT_FILLER_H
#define GRAPHICSPROJECT_FILLER_H

#include <vector>
#include <climits>
#include <cmath>
#include "../Shapes/Point.h"

#define MAXENTRIES 600

struct Entry
{
    int maxX = INT_MIN;
    int minX = INT_MAX;
};
class Filler
{
public:
    static void ConvexFill(HDC& hdc, vector<Point*> &points, COLORREF color)
    {
        int n = points.size();
        auto * table = new Entry[MAXENTRIES];
        for(int i = 0; i < n; i++)
        {
            Point v1 = *points[i];
            Point v2 = *points[(i+1)%n];
            _ScanEdge(v1, v2, table);
        }
        DrawScanLines(hdc, table, color);
        delete table;
    }

private:
    static void _ScanEdge(Point &v1, Point& v2, Entry* table)
    {
        if(v1.getY() == v2.getY())
            return;
        if(v1.getY() > v2.getY())
            Shape::swap(v1, v2);

        double slope = (double)(v2.getX()-v1.getX())/(v2.getY()-v1.getY());
        double x = v1.getX();
        int y = v1.getY();
        while (y < v2.getY())
        {
            if(table[y].maxX < x){table[y].maxX = static_cast<int>(floor(x));}
            if(table[y].minX > x){table[y].minX = static_cast<int>(ceil(x));}
            y++;
            x += slope;
        }
    }

    static void DrawScanLines(HDC& hdc, Entry* table, COLORREF color)
    {
        int t = 0;
        for(int y = 0; y < MAXENTRIES; y++)
        {
            if(table[y].minX < table[y].maxX)
            {
                for(int x = table[y].minX; x <= table[y].maxX; x++)
                {
                    SetPixel(hdc, x, y, color);
                }
            }
        }
    }

};

#endif //GRAPHICSPROJECT_FILLER_H
