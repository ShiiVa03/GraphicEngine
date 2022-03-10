#include "../utils/vector.hpp"
#include "../utils/point.hpp"
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
        Point base1 = base1.toCartesian(SphericalCoord(alpha * i, 0.0f, radius));
        Point base2 = base2.toCartesian(SphericalCoord(alpha * (i+1), 0.0f, radius));
    
        points.push_back(base1);
        points.push_back(center);
        points.push_back(base2);


        for(int j = 0; j < stacks; ++j){
            
            auto currentRadius = (radius * (height - (j*stepUp)))/height;
            auto upperRadius = (radius * (height - ((j+1)*stepUp)))/height;
            
            Point lateral1 = lateral1.toCartesianNoBeta(alpha * i, currentRadius, stepUp * j);
            Point lateral3 = lateral3.toCartesianNoBeta(alpha * (i+1), currentRadius, stepUp * j);

            Point lateral4 = lateral4.toCartesianNoBeta(alpha * i, upperRadius, stepUp * (j+1));
            Point lateral2 = lateral2.toCartesianNoBeta(alpha * (i+1), upperRadius, stepUp * (j+1));

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