#include "../utils/point.hpp"
#include "../utils/spherical_coord.hpp"
#include "parsing.hpp"
#include "camera.hpp"
#include "model.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static Camera camera;
static std::vector<std::string> models;
static std::unordered_map<std::string, std::vector<Point>> models_vertices;

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
    /*
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
*/
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    for (const auto &fileName: models) {
        std::vector<Point> &vertices = models_vertices.at(fileName);

        for (const auto& point : vertices) {
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

bool initContext(char * filename) {
    
    if (!parse(filename, camera, models))
        return false;

    long total_vertices;
    float x, y, z;

    for (const auto& file : models) {
        if (!models_vertices.contains(file)) {
            std::ifstream stream(file);
            stream >> total_vertices;

            models_vertices.emplace(file, std::vector<Point>());
            std::vector<Point>& vertices = models_vertices.at(file);
            vertices.reserve(total_vertices);

            while (stream >> x >> y >> z)
                vertices.emplace_back(x, y, z);
        }
    }

    return true;
}


int main(int argc, char ** argv) {

    if (argc != 2 || !initContext(argv[1]))
        return -1;


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