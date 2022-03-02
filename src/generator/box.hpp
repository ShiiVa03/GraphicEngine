#ifndef BOX_H
#define BOX_H

#include "../utils/point.hpp"
#include <vector>

class Box{    
    public:
        float size, divisions;
        Box(float size, float divisions);
        std::vector<Point> draw();        
};

#endif
