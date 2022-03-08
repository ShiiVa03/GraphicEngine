#include "pugixml.hpp"
#include "../utils/point.hpp"
#include "camera.hpp"
#include "model.hpp"

#include <vector>
#include <iostream>

bool parse(char * filename, Camera &camera, std::vector<std::string>& models) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);

    if (!result) {
        std::cout << "ERROR" << std::endl;
        return false;
    }

    pugi::xml_node toolWorld = doc.child("world");

    pugi::xml_node toolCamera = toolWorld.child("camera");

    pugi::xml_node tool;

    tool = toolCamera.child("position");
    Point eye(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("lookAt");
    Point center(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("up");
    Point up(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("projection");
    double fov = tool.attribute("fov").as_double();
    double near = tool.attribute("near").as_double();
    double far = tool.attribute("far").as_double();


    camera.init(eye, center, up, fov, near, far);



    pugi::xml_node toolGroup = toolWorld.child("group");

    for (pugi::xml_node toolModel : toolGroup.child("models").children("model")) {
        models.push_back(toolModel.attribute("file").as_string());
    }

    return true;
}