#include "pugixml.hpp"
#include "../utils/point.hpp"
#include "camera.hpp"
#include "model.hpp"
#include "group.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>

void parseModel(Model &model, pugi::xml_node toolModel) {
    model.init(toolModel.attribute("file").as_string());
}

void parseGroup(Group &parent_group, pugi::xml_node toolParentGroup) {

    for (pugi::xml_node toolModel : toolParentGroup.child("models").children("model")) {
        Model model;

        parseModel(model, toolModel);
        parent_group.add_model(model);
    }

    for (pugi::xml_node tool : toolParentGroup.child("transform").children()) {
        enum Transformation transformation = transformationStringToEnum(tool.name());
        pugi::xml_attribute  time_attr;
        

        switch (transformation)
        {
        case Transformation::TRANSLATION:
            time_attr = tool.attribute("time");

            if (time_attr.empty())
                parent_group.add_translation(Translation(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float()));
            else {
                std::vector<Point> points;
                for (pugi::xml_node toolPoint : tool.children("point")) {
                    points.emplace_back(Point(toolPoint.attribute("x").as_float(), toolPoint.attribute("y").as_float(), toolPoint.attribute("z").as_float()));
                }

                parent_group.add_translation(Translation(time_attr.as_float(), tool.attribute("align").as_bool(), points));
            }
            break;
        case Transformation::ROTATION:
            parent_group.add_rotation(Rotation(tool.attribute("time").as_float(), tool.attribute("angle").as_float(), tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float()));
            break;
        case Transformation::SCALE:
            parent_group.add_scale(Scale(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float()));
            break;
        }
    }



    for (pugi::xml_node toolGroup : toolParentGroup.children("group")) {
        Group group;

        parseGroup(group, toolGroup);
        parent_group.add_group(group);
    }
}

void parseCamera(Camera& camera, pugi::xml_node toolCamera) {
    pugi::xml_node tool;

    tool = toolCamera.child("position");
    Point eye(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("lookAt");
    Point center(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("up");
    Vector up(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("z").as_float());

    tool = toolCamera.child("projection");
    double fov = tool.attribute("fov").as_double();
    double near = tool.attribute("near").as_double();
    double far = tool.attribute("far").as_double();


    camera.init(eye, center, up, fov, near, far);
}

bool parse(char * filename, Camera &camera, Group& group) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);

    if (!result) {
        return false;
    }

    pugi::xml_node toolWorld = doc.child("world");

    if (!toolWorld)
        throw std::invalid_argument("World not found in .xml");


    pugi::xml_node toolCamera = toolWorld.child("camera");

    if (!toolCamera)
        throw std::invalid_argument("Camera not found in .xml's World");

    parseCamera(camera, toolCamera);


    pugi::xml_node toolGroup = toolWorld.child("group");

    if (!toolGroup)
        throw std::invalid_argument("Group not found in .xml's World");

    parseGroup(group, toolGroup);

    return true;
}