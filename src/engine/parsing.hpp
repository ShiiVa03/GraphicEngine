#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>

#include "camera.hpp"

bool parse(char * filename, Camera &camera, std::vector<std::string>& models);

#endif
