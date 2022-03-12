#include "../utils/point.hpp"
#include "../utils/spherical_coord.hpp"
#include "parsing.hpp"
#include "camera.hpp"
#include "model.hpp"
#include "group.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static Camera camera;
static Group main_group;
static std::unordered_map<std::string, std::vector<Point>> models_vertices;

static GLenum current_mode = GL_FILL;

bool show_axis = true;

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

void renderGroup(const Group& group) {
    for (auto const& transformation : group.ordered_transformations) {
        switch (transformation)
        {
        case Transformation::TRANSLATION:
            glTranslatef(group.translation.x, group.translation.y, group.translation.z);
            break;
        case Transformation::ROTATION:
            glRotatef(group.rotation.alpha, group.rotation.axis_x, group.rotation.axis_y, group.rotation.axis_z);
            break;
        case Transformation::SCALE:
            glScalef(group.scale.x, group.scale.y, group.scale.z);
            break;
        }
    }


    glBegin(GL_TRIANGLES);
    for (const auto& model : group.models) {
        std::vector<Point>& vertices = models_vertices.at(model.file);

        for (const auto& point : vertices)
            glVertex3f(point.x, point.y, point.z);

    }
    glEnd();


    for (auto const& sub_group : group.groups) {
        glPushMatrix();
        renderGroup(sub_group);
        glPopMatrix();
    }

}

void updateCamera(void) {
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    updateCamera();


    if (show_axis) {
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
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    renderGroup(main_group);

    // End of frame
    glutSwapBuffers();
}

void loadModels(const Group& group) {
    long total_vertices;
    float x, y, z;

    for (const auto& model : group.models) {
        if (!models_vertices.contains(model.file)) {
            std::ifstream stream(model.file);

            if (!stream)
                throw std::invalid_argument(model.file + " can't be opened");

            stream >> total_vertices;

            models_vertices.emplace(model.file, std::vector<Point>());
            std::vector<Point>& vertices = models_vertices.at(model.file);
            vertices.reserve(total_vertices);

            while (stream >> x >> y >> z)
                vertices.emplace_back(x, y, z);
        }
    }

    for (const auto& sub_group : group.groups)
        loadModels(sub_group);
}

bool initContext(char * filename) {
    
    if (!parse(filename, camera, main_group))
        return false;

    loadModels(main_group);

    return true;
}


// write function to process keyboard events


void specialKeysFunc(int key_code, int x, int y) {
    SphericalCoord eye_camera = SphericalCoord(camera.eye);
    
    float alpha_var = M_PI_4 / 20.0f;
    float beta_var = M_PI_4 / 20.0f;
    float radius_var = 0.5f;


    switch (key_code) {
    case GLUT_KEY_UP:
        if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
            eye_camera.radius = fmaxf(radius_var, eye_camera.radius - radius_var);
        else {
            // Beta angle changes perspective if it hits -PI/2 or PI/2. This code avoids that
            eye_camera.beta = fminf(eye_camera.beta + beta_var, M_PI_2 - beta_var);
        }
        break;
    case GLUT_KEY_DOWN:
        if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
            eye_camera.radius += radius_var;
        else {
            // Beta angle changes perspective if it hits -PI/2 or PI/2. This code avoids that
            eye_camera.beta = fmaxf(eye_camera.beta - beta_var, -M_PI_2 + beta_var);
        }
        break;
    case GLUT_KEY_RIGHT: eye_camera.alpha += alpha_var; break;
    case GLUT_KEY_LEFT: eye_camera.alpha -= alpha_var; break;
    default: return;
    }

    
    eye_camera.beta = fminf(fmaxf(eye_camera.beta, -M_PI_2 + beta_var), M_PI_2 - beta_var);

    camera.eye = Point(eye_camera);
    
    updateCamera();

    glutPostRedisplay();
}

void keyboardKeysFunc(unsigned char key, int x, int y) {


    if (key == 'z') {
        switch (current_mode) {
        case GL_FILL: current_mode = GL_LINE; break;
        case GL_LINE: current_mode = GL_POINT; break;
        default: current_mode = GL_FILL;
        }

        glPolygonMode(GL_FRONT, current_mode);
    }
    else if (key == 'x') {
        show_axis = !show_axis;
    }


    glutPostRedisplay();
}


int main(int argc, char ** argv) {

    if (argc != 2) {
        std::cout << "Error: Engine requires .xml path" << std::endl;
        return -1;
    }
    
    try {
        if (!initContext(argv[1])) {
            std::cout << "Error: Provided .xml file is corrupted or not found" << std::endl;
            return -1;
        }
    } catch (std::invalid_argument const& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return -1;
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
    glPolygonMode(GL_FRONT, GL_FILL);


    // put here the registration of the keyboard callbacks
    glutSpecialFunc(specialKeysFunc);
    glutKeyboardFunc(keyboardKeysFunc);


    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}