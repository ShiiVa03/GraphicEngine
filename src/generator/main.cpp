#include <math.h>
#include "plane.hpp"
#include <vector>
#include "../utils/point.hpp"
#include <iostream>
#include <string>


int main(int argc, char **argv) {
    float edge = 2;
    float divisions = 3;
    std::vector<Point> points;


    Plane plane(edge, divisions);
    plane.draw();
    for (int i = 0; i < points.size(); ++i) {
        std::cout << std::to_string(points.at(i).x) + std::to_string(points.at(i).y) + std::to_string(points.at(i).z) << std::endl;
    }
    
}
