#include "../utils/point.hpp"
#include "bezierpatches.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "torus.hpp"
#include "cone.hpp"
#include "box.hpp"

#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

void writeToFile(std::vector<Point>& points, std::string filename){
    std::ofstream file(filename);
    file << points.size() << std::endl;
    
    for(auto const& point : points){
        file << point.x << " " << point.y << " " << point.z <<std::endl;
    }

    file.close();

}

int main(int argc, char **argv) {

    if(argc < 2) {
        std::cout << "Necessita de pelo menos dois argumentos" << std::endl;
        return 1;
    }
    std::vector<Point> points;
    std::string figure(argv[1]);
    std::string file;

    if(!figure.compare("plane")){
        if(argc == 5){
            float size = atof(argv[2]);
            float divisions = atof(argv[3]);
            file = argv[4];

            Plane plane(size, divisions);
            points = plane.draw();
                                
        }else{
            std::cout << "Plane necessita de 3 argumentos" << std::endl;
        }
    }else if(!figure.compare("box")){
        if(argc == 5){
            float size = atof(argv[2]);
            float divisions = atof(argv[3]);
            file = argv[4];

            Box box(size, divisions);
            points = box.draw();
                                
        }else{
            std::cout << "Box necessita de 3 argumentos" << std::endl;
        }
    }else if(!figure.compare("cone")){ 
        if(argc == 7){
            
            float radius = atof(argv[2]);
            float height = atof(argv[3]);
            float slices = atof(argv[4]);
            float stacks = atof(argv[5]);
            file = argv[6];

            Cone cone(radius, height, slices, stacks);
            points = cone.draw();
            
        }else{
            std::cout << "Cone necessita de 5 argumentos" << std::endl;
        }
    }else if(!figure.compare("sphere")){
        if(argc == 6){

            float radius = atof(argv[2]);
            float slices = atof(argv[3]);
            float stacks = atof(argv[4]);
            file = argv[5];

            Sphere sphere(radius, slices, stacks);
            points = sphere.draw();
        }else{
            std::cout << "Sphere necessita de 4 argumentos" << std::endl;
        }

    }
    else if (!figure.compare("torus")) {
        if (argc == 7) {

            float radius_outer = atof(argv[2]);
            float radius_inner = atof(argv[3]);
            float slices = atof(argv[4]);
            float stacks = atof(argv[5]);
            file = argv[6];

            Torus torus(radius_outer, radius_inner, slices, stacks);
            points = torus.draw();
        }
        else {
            std::cout << "Torus necessita de 5 argumentos" << std::endl;
        }

    }
    else if(!figure.compare("bezier")){
        if(argc == 5){

            char * filein = argv[2];
            int level = atoi(argv[3]);
            file = argv[4];

            Bezier bezier(level);
            bezier.parse(filein);

            points = bezier.draw();

        }else{
            std::cout << "Bezier necessita de 3 argumentos" << std::endl;
        }

    }else{
        std::cout << "Comando nao disponivel" << std::endl;
    }
    
    if(!points.empty())
        writeToFile(points, file);

    return 0;
    
}

