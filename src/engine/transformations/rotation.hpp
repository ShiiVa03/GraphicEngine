#ifndef ROTATION_H
#define ROTATION_H

class Rotation {
public:
    float alpha, axis_x, axis_y, axis_z;
    Rotation(float alpha, float axis_x, float axis_y, float axis_z);
    Rotation();
};

#endif
