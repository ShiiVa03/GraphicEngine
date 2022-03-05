#ifndef MODEL_H
#define MODEL_H

#include "../utils/point.hpp"
#include <string>
#include <vector>

class Model{
    public:
        std::string file;
        std::vector<Point> vertices;
        Model(std::string file, long totalVertices);
        
};

#endif
