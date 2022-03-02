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
    plane.drawPlane(points, Point(0, size, 0), Vector(vectorSize, 0 , 0), Vector(0, 0, vectorSize));
    
    //back face
    plane.drawPlane(points, Point(0, size, 0), Vector(0, 0, vectorSize), Vector(0, -vectorSize, 0));

    //left face
    plane.drawPlane(points, Point(0, size, size), Vector(vectorSize, 0, 0), Vector(0, -vectorSize, 0));

    //rigth face
    plane.drawPlane(points, Point(size, size, 0), Vector(-vectorSize, 0, 0), Vector(0, -vectorSize, 0));

    //front face(need to start bottom-up to verify right hand rule)
    plane.drawPlane(points, Point(size, 0, 0), Vector(0, 0, vectorSize), Vector(0, vectorSize, 0));

    //bottom face
    plane.drawPlane(points, Point(0, 0, size), Vector(vectorSize, 0, 0), Vector(0, 0, -vectorSize));

    return points;



}