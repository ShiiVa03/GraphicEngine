#include "spherical_coord.hpp"
#include "vector.hpp"
#include "point.hpp"

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

Point Point::toCartesian(SphericalCoord sp){
    float x = sp.radius * cos(sp.beta) * sin(sp.alpha);
    float y = sp.radius * sin(sp.beta);
    float z = sp.radius * cos(sp.beta) * cos(sp.alpha);

    return Point(x,y,z);

}

Point Point::toCartesianNoBeta(float alpha, float radius, float height){
    float x = radius * sin(alpha);
    float y = height;
    float z = radius * cos(alpha);

    return Point(x,y,z);

}