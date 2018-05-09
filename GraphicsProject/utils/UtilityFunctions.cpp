//
// Created by mahmo on 5/7/2018.
//
#include <windows.h>
#include <map>
#include <stack>
#include <fstream>
#include "Enums.h"

#include "../Shapes/Shape.h"
#include "../Circles/QuadraticCircle.h"
#include "../Circles/PolarCircle.h"
#include "../Circles/BresenhamCircle.h"

#include "../Lines/DirectLine.h"
#include "../Lines/DDALine.h"
#include "../Lines/BresenhamLine.h"

#include "../Curves/BezierCurve.h"
#include "../Curves/HermitCurve.h"
#include "../Polygons/MyNthPolygon.h"
#include "../Lines/LineClipper.h"
#include "../Polygons/PolygonClipper.h"


namespace UtilityFunctions
{
    map<int, Shape*> myMap;
    bool initialized = false;

    void initialize()
    {
        myMap[CIRCLE_BRESENHAM] = BresenhamCircle::generate();
        myMap[CIRCLE_QUADRATIC] = QuadraticCircle::generate();
        myMap[CIRCLE_POLAR]     = PolarCircle::generate();

        myMap[LINE_CLIPPER]     = LineClipper::generate();
        myMap[LINE_DIRECT]      = DirectLine::generate();
        myMap[LINE_DDA]         = DDALine::generate();
        myMap[LINE_BRESENHAM]   = BresenhamLine::generate();

        myMap[CURVE_HERMIT]     = HermitCurve::generate();
        myMap[CURVE_BEZIER]     = BezierCurve::generate();

        myMap[POLYGON_CLIPPER]  = PolygonClipper::generate();
        for(int i = 3; i <= 10; i++)
            myMap[POLYGON_3_points-3+i] = MyNthPolygon::generate(i);

        initialized = true;
    }

    void createMenus(HMENU& hmenu)
    {
        HMENU file  = CreateMenu();
        HMENU line  = CreateMenu();
        HMENU circle  = CreateMenu();
        HMENU curve  = CreateMenu();
        HMENU polygon  = CreateMenu();
        HMENU fill  = CreateMenu();
        HMENU clip  = CreateMenu();

        // append to main menu
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)file    ,"File");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)line    ,"Line");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)circle  ,"Circle");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)curve   ,"Curve");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)polygon ,"Polygon");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)fill    ,"Fill");
        AppendMenu(hmenu, MF_POPUP, (UINT_PTR)clip    ,"Clip");

        // append to File menu
        AppendMenu(file, MF_POPUP, SAVE , "Save");
        AppendMenu(file, MF_POPUP, LOAD , "Load");
        AppendMenu(file, MF_POPUP, CLOSE, "Close");

        // append to Line menu
        AppendMenu(line, MF_POPUP, LINE_DIRECT   , "DirectLine");
        AppendMenu(line, MF_POPUP, LINE_DDA      , "DDALine");
        AppendMenu(line, MF_POPUP, LINE_BRESENHAM, "LineBresenham");
        AppendMenu(line, MF_POPUP, LINE_CLIPPER   , "LineClip");

        // append to Circle menu
        AppendMenu(circle, MF_POPUP, CIRCLE_QUADRATIC, "QuadraticCircle");
        AppendMenu(circle, MF_POPUP, CIRCLE_POLAR    , "PolarCircle");
        AppendMenu(circle, MF_POPUP, CIRCLE_BRESENHAM, "BresenhamCircle");

        // append to Curve menu
        AppendMenu(curve, MF_POPUP, CURVE_BEZIER, "BezierCurve");
        AppendMenu(curve, MF_POPUP, CURVE_HERMIT, "HermitCurve");

        // append to Polygon menu
        AppendMenu(polygon, MF_POPUP, POLYGON_3_points,  "Polygon 3 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_4_points,  "Polygon 4 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_5_points,  "Polygon 5 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_6_points,  "Polygon 6 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_7_points,  "Polygon 7 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_8_points,  "Polygon 8 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_9_points,  "Polygon 9 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_10_points, "Polygon 10 Points");
        AppendMenu(polygon, MF_POPUP, POLYGON_CLIPPER, "PolygonClip");

        // append to Fill menu
        AppendMenu(fill, MF_POPUP, FILL_CONVEXFILL, "ConvexFill");
        AppendMenu(fill, MF_POPUP, FILL_GENERAL , "GeneralFill");

    }

    void GeneralFill(HDC& hdc,int x,int y,COLORREF Cb,COLORREF Cf = RGB(255,0,0))
    {
        stack<Point*> S;
        S.push(new Point(x,y));
        while(!S.empty())
        {
            Point* v = S.top(); S.pop();
            int vx = v->getX();
            int vy = v->getY();
            COLORREF c = GetPixel(hdc, vx,vy);
            if(c == Cb || c == Cf)
                continue;
            SetPixel(hdc,vx,vy,Cf);
            S.push(new Point(vx+1,vy));
            S.push(new Point(vx-1,vy));
            S.push(new Point(vx,vy+1));
            S.push(new Point(vx,vy-1));
        }
    }

    void selectionResult(HDC& hdc, int wParam, Shape* &currentShape, int &neededPoints)
    {
        if(!initialized)
            initialize();

        switch(wParam)
        {
            case SAVE:
            case LOAD:
            case CLOSE:
                break;

            case CURVE_HERMIT:
            case CURVE_BEZIER:
                neededPoints = 4;
                break;

            case POLYGON_3_points ... POLYGON_10_points:
                neededPoints = wParam-POLYGON_3_points+3;
                break;

            case LINE_DIRECT ... CIRCLE_BRESENHAM:
                neededPoints = 2;
                break;

            case FILL_CONVEXFILL:
                try {
                    dynamic_cast<MyNthPolygon*>(currentShape)->fill(hdc);
                    wParam = POLYGON_3_points-3+neededPoints;
                    // TODO: REMOVE THE DELETE
                    delete myMap[wParam];
                    myMap[wParam] = MyNthPolygon::generate(neededPoints);
                }catch (exception &ex){
                    cout << ex.what() << endl;
                }
                break;
            case FILL_GENERAL:
                neededPoints = 1;
                return;

            case LINE_CLIPPER:
                neededPoints = 4;
                break;
            case POLYGON_CLIPPER:
                neededPoints = 6;
                break;
            default:
                return;
        }
        currentShape = myMap[wParam];
    }
}

