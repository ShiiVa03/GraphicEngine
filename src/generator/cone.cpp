#include "../utils/vector.hpp"
#include "../utils/point.hpp"
#include "../utils/cylindrical_coord.hpp"
#include "../utils/spherical_coord.hpp"
#include "cone.hpp"

#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES
#include "math.h"

Cone::Cone(float rad, float hei, float sli, float sta){
    radius = rad;
    height = hei;
    slices = sli;
    stacks = sta;
}

std::vector<Point> Cone::draw(){

    float alpha = 2* M_PI / slices;
    float stepUp = height / stacks;
    Point center(0.0f, 0.0f, 0.0f);

    std::vector<Point> points;

    for(int i = 0; i < slices; ++i){
        Point base1(SphericalCoord(alpha * i, 0.0f, radius));
        Point base2(SphericalCoord(alpha * (i+1), 0.0f, radius));
    
        points.push_back(base1);
        points.push_back(center);
        points.push_back(base2);


        for(int j = 0; j < stacks; ++j){
            
            auto currentRadius = (radius * (height - (j*stepUp)))/height;
            auto upperRadius = (radius * (height - ((j+1)*stepUp)))/height;
            
            Point lateral1(CylindricalCoord(alpha * i, stepUp * j, currentRadius));
            Point lateral3(CylindricalCoord(alpha * (i+1), stepUp * j,  currentRadius));

            Point lateral4(CylindricalCoord(alpha * i, stepUp * (j+1), upperRadius));
            Point lateral2(CylindricalCoord(alpha * (i+1), stepUp * (j+1), upperRadius));

            if(j == (stacks - 1)){
                points.push_back(lateral1);
                points.push_back(lateral3);
                points.push_back(Point(0.0f, height, 0.0f));
                            
            }else{
                points.push_back(lateral1);
                points.push_back(lateral3);
                points.push_back(lateral4);

                points.push_back(lateral3);
                points.push_back(lateral2);
                points.push_back(lateral4);
            }

        }
    
    }

    return points;
}