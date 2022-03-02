#include "plane.hpp"
#include "../utils/point.hpp"
#include <vector>
#include "../utils/vector.hpp"

Plane::Plane(float s, float d){
    size = s;
    divisions = d;
}

// we choose to pass an origin point instead of doing the required math inside this function 
//because this function can be used to draw the box and there is no need to rewrite code

void Plane::drawPlane(std::vector<Point>& points, Point origin, Vector horizontalVec, Vector verticalVec){
    
    //starting a top-down, left-right approach since that is how computers draw in screen

    Point refp0 = Point(origin.x, origin.y, origin.z);
    Point refp1 = Point(refp0.x, refp0.y, refp0.z);
    refp1.addVector(horizontalVec);
    Point refp2 = Point(refp0.x, refp0.y, refp0.z);
    refp2.addVector(verticalVec);
    Point refp3 = Point(refp2.x, refp2.y, refp2.z); // maybe use the reference point instead of the second point?
    refp3.addVector(horizontalVec);

    for(int i = 0; i < divisions; ++i){
        Point p0 = Point(refp0.x, refp0.y, refp0.z);
        Point p1 = Point(refp1.x, refp1.y, refp1.z);
        Point p2 = Point(refp2.x, refp2.y, refp2.z);
        Point p3 = Point(refp3.x, refp3.y, refp3.z);

        for(int j = 0; j < divisions; ++j){
            

            //first triangle(up)
            points.push_back(p0);
            points.push_back(p3);
            points.push_back(p1);

            //second triangle(down)
            points.push_back(p0);
            points.push_back(p2);
            points.push_back(p3);

            //translate points horizontally
            p0.addVector(horizontalVec);
            p1.addVector(horizontalVec);
            p2.addVector(horizontalVec);
            p3.addVector(horizontalVec);

        }

        //translate ref points vertically down
        refp0.addVector(verticalVec);
        refp1.addVector(verticalVec);
        refp2.addVector(verticalVec);
        refp3.addVector(verticalVec);
    }
}

std::vector<Point> Plane::draw(){
    std::vector<Point> points;

    float vectorSize = size / divisions;
    float half = size / 2;

    drawPlane(points, Point(-half, 0, -half), Vector(vectorSize, 0, 0), Vector(0, 0, vectorSize));

    return points;

}