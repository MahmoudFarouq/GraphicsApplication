//
// Created by mahmo on 5/7/2018.
//

#ifndef GRAPHICSPROJECT_ENUMS_H
#define GRAPHICSPROJECT_ENUMS_H

enum MENU {

    myFILE,
    SAVE,
    LOAD,
    CLOSE,

    LINE,
    LINE_DIRECT,
    LINE_DDA,
    LINE_BRESENHAM,

    CIRCLE,
    CIRCLE_QUADRATIC,
    CIRCLE_POLAR,
    CIRCLE_BRESENHAM,

    CURVE,
    CURVE_BEZIER,
    CURVE_HERMIT,

    POLYGON,
    POLYGON_3_points,
    POLYGON_4_points,
    POLYGON_5_points,
    POLYGON_6_points,
    POLYGON_7_points,
    POLYGON_8_points,
    POLYGON_9_points,
    POLYGON_10_points,

    FILL,
    FILL_CONVEXFILL,
    FILL_GENERAL,

    CLIP,
    LINE_CLIPPER,
    POLYGON_CLIPPER
};


#endif //GRAPHICSPROJECT_ENUMS_H
