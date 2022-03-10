#include "../utils/point.hpp"
#include "../utils/spherical_coord.hpp"
#include "sphere.hpp"

#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES
#include "math.h"

Sphere::Sphere(float r, float sl, float st){
    radius = r;
    slices = sl;
    stacks = st;
}

std::vector<Point> Sphere::draw(){

    auto alpha = 2*M_PI / slices;
    auto beta = M_PI / stacks;

    Point centerHigh(0, radius, 0);
    Point centerDown(0,-radius, 0);

    std::vector<Point> points;

    //draw base and then proceed to "lateral"
    for(int i = 0; i < slices; ++i){
        //top base only need one triangle since the other would be in the same points
        Point p1(SphericalCoord(alpha * i, M_PI / 2 - beta, radius));
        Point p2(SphericalCoord(alpha * (i + 1), M_PI / 2 - beta, radius));

        points.push_back(p1);
        points.push_back(p2);
        points.push_back(centerHigh);

        for(int j = 1; j < stacks; ++j){
            //starting up-down
            Point pointDownL(SphericalCoord(alpha * i, M_PI / 2 - beta * (j + 1), radius));
            Point pointDownR(SphericalCoord(alpha * (i + 1), M_PI / 2 - beta * (j + 1), radius));
            Point pointL(SphericalCoord(alpha * i, M_PI / 2 - beta * j, radius));
            Point pointR(SphericalCoord(alpha * (i + 1), M_PI / 2 - beta * j, radius));
            
            //last stack is bottom base
            if(j == stacks - 1){
                points.push_back(centerDown);
                points.push_back(pointR);
                points.push_back(pointL);
            }else{
                points.push_back(pointDownL);
                points.push_back(pointDownR);
                points.push_back(pointL);

                points.push_back(pointDownR);
                points.push_back(pointR);
                points.push_back(pointL);
            }        
        }
    }

    return points;

}