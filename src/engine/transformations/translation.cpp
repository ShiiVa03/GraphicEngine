#include "translation.hpp"

Translation::Translation(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
};

Translation::Translation() : Translation(0, 0, 0) {

};