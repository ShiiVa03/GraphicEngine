#ifndef PLANE_H
#define PLANE_H
#include "../utils/vector.hpp"
#include "../utils/point.hpp"
#include <vector>
class Plane{    
    public:
        float size, divisions;
        Plane(float size, float divisions);
        void drawPlane(std::vector<Point>& points, Point origin, Vector horizontalVec, Vector verticalVec);
        std::vector<Point> draw();        
};

#endif