#ifndef CONE_H
#define CONE_H

#include "../utils/point.hpp"
#include <vector>

class Cone{    
    public:
        float radius, height, slices, stacks;
        Cone(float rad, float height, float sli, float stacks);
        std::vector<Point> draw();
};

#endif
