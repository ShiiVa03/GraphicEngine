#ifndef SPHERICAL_POINT_H
#define SPHERICAL_POINT_H

#include "vector.hpp"

class SphericalPoint{
    public:
        float alpha, beta, radius;
	    SphericalPoint(){};
        SphericalPoint(float alpha, float beta, float radius);
        
};

#endif
