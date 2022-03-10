#ifndef POINT_H
#define POINT_H

#include "vector.hpp"

class SphericalCoord;
class CylindricalCoord;

class Point{
    public:
        float x, y, z;
        Point(float a = 0, float b = 0, float c = 0);
        Point(SphericalCoord sc);
        Point(CylindricalCoord cc);
        void addVector(Vector vec);
};

#endif
