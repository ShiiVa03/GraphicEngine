#include "model.hpp"
#include "../utils/point.hpp"
#include <string>
#include <vector>

Model::Model(std::string file, long totalVertices){
    this->file = file;
    this->vertices.reserve(totalVertices);
};

