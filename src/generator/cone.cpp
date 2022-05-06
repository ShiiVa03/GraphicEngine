#include "../utils/vector.hpp"
#include "../utils/point2D.hpp"
#include "../utils/point.hpp"
#include "../utils/cylindrical_coord.hpp"
#include "../utils/spherical_coord.hpp"
#include "cone.hpp"

#include <tuple>
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

std::tuple<std::vector<Point>, std::vector<Vector>, std::vector<Point2D>> Cone::draw(){

    float alpha = 2* M_PI / slices;
    float stepUp = height / stacks;
    Point center(0.0f, 0.0f, 0.0f);

    std::vector<Point> points;
    std::vector<Vector> normals;
    std::vector<Point2D> textures;

    for(int i = 0; i < slices; ++i){
        Point base1(SphericalCoord(alpha * i, 0.0f, radius));
        Point base2(SphericalCoord(alpha * (i+1), 0.0f, radius));
    
        points.push_back(base1);
        points.push_back(center);
        points.push_back(base2);

        normals.push_back(Vector(0, -1, 0));
        normals.push_back(Vector(0, -1, 0));
        normals.push_back(Vector(0, -1, 0));


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

                normals.push_back(Vector(sinf(alpha * i), stepUp, cosf(alpha * i)));
                normals.push_back(Vector(sinf(alpha * (i + 1)), stepUp, cosf(alpha * i)));
                normals.push_back(Vector(sinf(alpha * i), stepUp, cosf(alpha * i)));

                            
            }else{
                points.push_back(lateral1);
                points.push_back(lateral3);
                points.push_back(lateral4);

                normals.push_back(Vector(sinf(alpha * i), stepUp, cosf(alpha * i)));
                normals.push_back(Vector(sinf(alpha * (i + 1)), stepUp, cosf(alpha * i)));
                normals.push_back(Vector(sinf(alpha * i), stepUp, cosf(alpha * i)));

                points.push_back(lateral3);
                points.push_back(lateral2);
                points.push_back(lateral4);

                normals.push_back(Vector(sinf(alpha * (i + 1)), stepUp, cosf(alpha * (i + 1))));
                normals.push_back(Vector(sinf(alpha * (i + 1)), stepUp, cosf(alpha * i)));
                normals.push_back(Vector(sinf(alpha * i), stepUp, cosf(alpha * i)));
            }

        }
    
    }

    return std::make_tuple(std::move(points), std::move(normals), std::move(textures));
}