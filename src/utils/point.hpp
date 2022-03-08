#ifndef POINT_H
#define POINT_H

#include "../utils/spherical_coord.hpp"
#include "vector.hpp"

class Point{
    public:
        float x, y, z;
	Point(){};
        Point(float x, float y, float z);
        void addVector(Vector vec);
        Point toCartesian(SphericalCoord sp);
        Point toCartesianNoBeta(float alpha, float radius, float height);
};

#endif
