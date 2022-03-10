#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>

#include "camera.hpp"
#include "group.hpp"

bool parse(char * filename, Camera &camera, Group& group);

#endif
