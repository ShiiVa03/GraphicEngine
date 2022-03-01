#include "point.hpp"
#include "vector.hpp"

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