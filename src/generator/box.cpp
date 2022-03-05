#include "box.hpp"
#include "plane.hpp"

Box::Box(float s, float div){
    size = s;
    divisions = div;
}

std::vector<Point> Box::draw(){
    std::vector<Point> points;

    Plane plane(size, divisions); //no need to create a plane for each face, we use the same one and change the origin point

    float vectorSize = size / divisions;

    //following top-down, left-right approach like before
    //upper face
    plane.drawPlane(points, Point(0.0f, size, 0.0f), Vector(vectorSize, 0.0f , 0.0f), Vector(0.0f, 0.0f, vectorSize));
    
    //back face
    plane.drawPlane(points, Point(0.0f, size, 0.0f), Vector(0.0f, 0.0f, vectorSize), Vector(0.0f, -vectorSize, 0.0f));

    //left face
    plane.drawPlane(points, Point(0.0f, size, size), Vector(vectorSize, 0.0f, 0.0f), Vector(0.0f, -vectorSize, 0.0f));

    //rigth face
    plane.drawPlane(points, Point(size, size, 0.0f), Vector(-vectorSize, 0.0f, 0.0f), Vector(0.0f, -vectorSize, 0.0f));

    //front face(need to start bottom-up to verify right hand rule)
    plane.drawPlane(points, Point(size, 0.0f, 0.0f), Vector(0.0f, 0.0f, vectorSize), Vector(0.0f, vectorSize, 0.0f));

    //bottom face
    plane.drawPlane(points, Point(0.0f, 0.0f, size), Vector(vectorSize, 0.0f, 0.0f), Vector(0.0f, 0.0f, -vectorSize));

    return points;



}