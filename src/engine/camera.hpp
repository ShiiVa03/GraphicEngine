#ifndef CAMERA_H
#define CAMERA_H

#include "../utils/point.hpp"


class Camera{
    public:
        Point eye, center, up;
        double fov, near, far;
        Camera();
        void init(Point eye, Point center, Point up, double fov, double near, double far);
        
};

#endif
