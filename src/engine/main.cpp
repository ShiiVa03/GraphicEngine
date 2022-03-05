#include "pugixml.hpp"
#include "../utils/point.hpp"
#include "camera.hpp"
#include "model.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Camera camera;
std::vector<std::string> queueModels;
std::unordered_map<std::string, Model> models;

bool entered = false;


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio 
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(camera.fov, ratio, camera.near, camera.far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);

    if (!entered) {
        std::cout << camera.eye.x << "|" << camera.eye.y << "|" << camera.eye.z << "|" << camera.center.x << "|" << camera.center.y << "|" << camera.center.z << camera.up.x << "|" << camera.up.y << "|" << camera.up.z << std::endl;
        std::cout << camera.fov << "|" << camera.near << "|" << camera.far << std::endl;
    }


    // put the geometric transformations here

    // put drawing instructions here
    
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    for (const auto &fileName: queueModels) {
        Model& model = models.at(fileName);

        for (const auto& point : model.vertices) {
            if (!entered) {
                std::cout << point.x << "|" << point.y << "|" << point.z << std::endl;
            }
            glVertex3f(point.x, point.y, point.z);
        }
    }
    glEnd();
    entered = true;

    // End of frame
    glutSwapBuffers();
}



int main(int argc, char** argv) {

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("a.xml");

    if (!result) {
        std::cout << "ERROR" << std::endl;
        return -1;
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

    for (pugi::xml_node toolModel: toolGroup.child("models").children("model")) {
        queueModels.push_back(toolModel.attribute("file").as_string());
    }

    
    long totalVertices;
    float x, y, z;

    for (const auto &file : queueModels) {
        if (!models.contains(file)) {
            std::ifstream stream(file);
            stream >> totalVertices;

            models.emplace((std::make_pair(file, Model(file, 5))));
            Model &model = models.at(file);

            while (stream >> x >> y >> z)
                model.vertices.push_back(Point(x, y, z));
        }
    }


    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glPolygonMode(GL_FRONT, GL_LINE);


    // put here the registration of the keyboard callbacks


    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;


    
    
    


    std::cout << "boas" << std::endl;
}