#ifndef VECTOR_H
#define VECTOR_H

#include "point.hpp"


class Vector{
    public:
        float vx, vy, vz;
        Vector();
        Vector(float vx, float vy, float vz);
        Vector(Point a, Point b);
        void normalize(void);
        void multiply(float x);
        Vector cross(Vector vec);
        
};

#endif
