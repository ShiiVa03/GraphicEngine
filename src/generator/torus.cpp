#include "../utils/point.hpp"
#include "../utils/vector.hpp"
#include "../utils/spherical_coord.hpp"
#include "torus.hpp"

#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES
#include "math.h"

Torus::Torus(float radius_outer, float radius_inner, float slices, float stacks){
    this->radius_outer = radius_outer;
    this->radius_inner = radius_inner;
    this->slices = slices;
    this->stacks = stacks;
}

std::vector<Point> Torus::draw(){

    float radius_center = (radius_outer + radius_inner) / 2;

    float radius_ring = (radius_outer - radius_inner) / 2;

    float slice_size = 2 * M_PI / slices;
    float stack_size = 2 * M_PI / stacks;

    std::vector<Point> points;


    for (int i = 0; i < slices; ++i) {
        SphericalCoord sc1(i * slice_size, 0, radius_ring);
        SphericalCoord sc2((i + 1) * slice_size, 0, radius_ring);

        Vector vec1(Point(0, 0, 0), Point(SphericalCoord(i * slice_size, 0, radius_center)));
        Vector vec2(Point(0, 0, 0), Point(SphericalCoord((i + 1) * slice_size, 0, radius_center)));


        for (int j = 0; j < stacks; ++j) {
            Point p_bottom_left(sc1);
            Point p_bottom_right(sc2);
            sc1.beta += stack_size;
            sc2.beta += stack_size;
            Point p_top_left(sc1);
            Point p_top_right(sc2);

            p_bottom_left.addVector(vec1);
            p_top_left.addVector(vec1);
            p_bottom_right.addVector(vec2);
            p_top_right.addVector(vec2);

            points.push_back(p_bottom_left);
            points.push_back(p_bottom_right);
            points.push_back(p_top_right);
            points.push_back(p_bottom_left);
            points.push_back(p_top_right);
            points.push_back(p_top_left);
        }

    }

    return points;

}