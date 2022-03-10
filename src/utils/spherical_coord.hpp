#ifndef SPHERICAL_COORD_H
#define SPHERICAL_COORD_H

#include "vector.hpp"

class SphericalCoord{
    public:
        float alpha, beta, radius;
	    SphericalCoord(){};
        SphericalCoord(float alpha, float beta, float radius);
        
};

#endif
