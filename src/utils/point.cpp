#include "point.hpp"
#include "vector.hpp"
#include "spherical_point.hpp"

#include <math.h> 

Point::Point(float a, float b, float c){
    x = a;
    y = b;
    z = c;
};

void Point::addVector(Vector vec){
    x += vec.vx;
    y += vec.vy;
    z += vec.vz;

}

Point Point::toCartesian(SphericalPoint sp){
    float x = sp.radius * cos(sp.beta) * sin(sp.alpha);
    float y = sp.radius * sin(sp.beta);
    float z = sp.radius * cos(sp.beta) * cos(sp.alpha);

    return Point(x,y,z);

}