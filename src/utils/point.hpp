#ifndef POINT_H
#define POINT_H

#include "vector.hpp"
#include "../utils/spherical_point.hpp"

class Point{
    public:
        float x, y, z;
	Point(){};
        Point(float x, float y, float z);
        void addVector(Vector vec);
        Point toCartesian(SphericalPoint sp);
        
};

#endif
