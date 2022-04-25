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
#include <tuple>

#include "catmull_rom.hpp"
#include "../utils/vector.hpp"
#include "../utils/point.hpp"
#include "../utils/spherical_coord.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

static Camera camera;
static Group main_group;
static std::unordered_map<std::string, std::tuple<GLuint, long>> models_vertices;

static GLenum current_mode = GL_FILL;

static GLuint * buffers;

static bool show_axis = true;
static bool show_aim = true;

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
    float time;
    int time_milis;

    for (auto const& transformation : group.ordered_transformations) {
        switch (transformation)
        {
        case Transformation::TRANSLATION:
            time = group.translation.time;

            if (time > 0) {
                time_milis = time * 1000; // miliseconds

                if (show_axis) {
                    glBegin(GL_LINE_LOOP);
                    for (int i = 0; i < 100; ++i) {
                        auto [pos, deriv] = getGlobalCatmullRomPoint(group.translation.points, ((float)i) / 100.0f);
                        glVertex3f(pos.x, pos.y, pos.z);
                    }
                    glEnd();
                }


                auto [pos, deriv] = getGlobalCatmullRomPoint(group.translation.points, ((float) (glutGet(GLUT_ELAPSED_TIME) % time_milis)) / time_milis);

                glTranslatef(pos.x, pos.y, pos.z);

                if (group.translation.align) {
                    float m[16];
                    static Vector vec_y(0, 1, 0);
                    
                    deriv.normalize();

                    Vector vec_z = deriv.cross(vec_y);
                    vec_z.normalize();

                    vec_y = vec_z.cross(deriv);
                    vec_y.normalize();

                    buildRotMatrix(deriv, vec_y, vec_z, m);
                    glMultMatrixf(m);
                }
            }
            else
                glTranslatef(group.translation.x, group.translation.y, group.translation.z);
            break;
        case Transformation::ROTATION:
            time = group.rotation.time;

            if (time > 0) {
                time_milis = time * 1000; // miliseconds
                glRotatef((((float)(glutGet(GLUT_ELAPSED_TIME) % time_milis)) / time_milis) * 360 - 180, group.rotation.axis_x, group.rotation.axis_y, group.rotation.axis_z);
            }
            else
                glRotatef(group.rotation.alpha, group.rotation.axis_x, group.rotation.axis_y, group.rotation.axis_z);
            break;
        case Transformation::SCALE:
            glScalef(group.scale.x, group.scale.y, group.scale.z);
            break;
        }
    }


    for (const auto& model : group.models) {
        auto [buffer, total_vertices] = models_vertices.at(model.file);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, total_vertices);

    }


    for (auto const& sub_group : group.groups) {
        glPushMatrix();
        renderGroup(sub_group);
        glPopMatrix();
    }

}

void updateCamera(void) {
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.vx, camera.up.vy, camera.up.vz);
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
    if (show_aim) {
        glColor3f(0.8f, 0.2f, 1.0f);
        glPushMatrix();
        Vector vec(Point(), camera.center);
        glTranslatef(vec.vx, vec.vy, vec.vz);
        glutSolidSphere(.05, 10, 10);
        glPopMatrix();
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

            GLuint buffer;
            glGenBuffers(1, &buffer);

            models_vertices.emplace(model.file, std::make_tuple(buffer, total_vertices));

            std::vector<Point> vertices;
            vertices.reserve(total_vertices);

            while (stream >> x >> y >> z)
                vertices.emplace_back(x, y, z);
            
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, 3 * total_vertices * sizeof(float), vertices.data(), GL_STATIC_DRAW);
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

void clickResumeWindow(int button, int state, int x, int y);

void keyboardKeysFunc(unsigned char key, int x, int y) {

    float step_var = 0.2f;
    Vector vec(camera.eye, camera.center);
    vec.normalize();

    switch (key) {
    case 27:
        glutMotionFunc(NULL);
        glutPassiveMotionFunc(NULL);
        glutSpecialFunc(NULL);
        glutKeyboardFunc(NULL);
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        glutMouseFunc(clickResumeWindow);
        break;

    case 'z':
        switch (current_mode) {
        case GL_FILL: current_mode = GL_LINE; break;
        case GL_LINE: current_mode = GL_POINT; break;
        default: current_mode = GL_FILL;
        }

        glPolygonMode(GL_FRONT, current_mode);
        break;

    case 'x':
        show_axis = !show_axis;
        break;

    case 'c':
        show_aim = !show_aim;
        break;

    case 'w':
        vec.multiply(step_var);
        camera.eye.addVector(vec);
        camera.center.addVector(vec);
        break;

    case 's':
        vec.multiply(-step_var);
        camera.eye.addVector(vec);
        camera.center.addVector(vec);
        break;

    case 'd':
        vec.multiply(step_var);
        vec = vec.cross(camera.up);
        camera.eye.addVector(vec);
        camera.center.addVector(vec);
        break;

    case 'a':
        vec.multiply(-step_var);
        vec = vec.cross(camera.up);
        camera.eye.addVector(vec);
        camera.center.addVector(vec);
        break;
    }


    glutPostRedisplay();
}

void specialKeysFunc(int key_code, int x, int y) {
    Vector recenter_vec = Vector(camera.center, Point());

    Point camera_eye(camera.eye);
    camera_eye.addVector(recenter_vec);

    SphericalCoord eye_camera_sc = SphericalCoord(camera_eye);
    
    float alpha_var = M_PI_4 / 20.0f;
    float beta_var = M_PI_4 / 20.0f;
    float radius_var = 0.5f;


    switch (key_code) {
    case GLUT_KEY_UP:
        if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {

            if (eye_camera_sc.radius > radius_var)
                eye_camera_sc.radius -= radius_var;

        }
        else {

                // Beta angle changes perspective if it hits -PI/2 or PI/2. This code avoids that
            if (eye_camera_sc.beta < M_PI_2 - beta_var)
                eye_camera_sc.beta += beta_var;

        }
        break;
    case GLUT_KEY_DOWN:
        if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
            eye_camera_sc.radius += radius_var;
        else {
            // Beta angle changes perspective if it hits -PI/2 or PI/2. This code avoids that
            if (eye_camera_sc.beta > -M_PI_2 + beta_var)
                eye_camera_sc.beta -= beta_var;
        }
        break;
    case GLUT_KEY_RIGHT: eye_camera_sc.alpha += alpha_var; break;
    case GLUT_KEY_LEFT: eye_camera_sc.alpha -= alpha_var; break;
    default: return;
    }

    camera.eye = Point(eye_camera_sc);

    recenter_vec.multiply(-1);
    camera.eye.addVector(recenter_vec);
    
    updateCamera();

    glutPostRedisplay();
}

void mouseFunc(int x, int y) {
    int size_width = glutGet(GLUT_WINDOW_WIDTH);
    int size_height = glutGet(GLUT_WINDOW_HEIGHT);

    int center_width = size_width / 2;
    int center_height = size_height / 2;

    if (x == center_width && y == center_height)
        return;

    float alpha = M_PI_2 * (((float)(x - center_width)) / (float)size_width);
    float beta = M_PI_2 * (((float)(y - center_height)) / (float)size_height);



    Point camera_fake_center = camera.center;
    Vector vec_recenter(camera.eye, Point());
    camera_fake_center.addVector(vec_recenter);


    SphericalCoord center_sc(camera_fake_center);

    center_sc.alpha -= alpha;
    center_sc.beta -= beta;

    if (center_sc.beta >= M_PI_2 || center_sc.beta <= -M_PI_2)
        center_sc.beta += beta;

    camera.center = Point(center_sc);
    vec_recenter.multiply(-1);
    camera.center.addVector(vec_recenter);

    glutWarpPointer(center_width, center_height);
    glutPostRedisplay();
}


void updateInputCallbacks(void) {
    // put here the registration of the keyboard callbacks
    glutSpecialFunc(specialKeysFunc);
    glutKeyboardFunc(keyboardKeysFunc);

    // put here the registration of the mouse callbacks
    glutMotionFunc(mouseFunc);
    glutPassiveMotionFunc(mouseFunc);

    // Remove mouse cursor
    glutSetCursor(GLUT_CURSOR_NONE);
}

void clickResumeWindow(int button, int state, int x, int y) {
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON) {
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
        updateInputCallbacks();
        glutMouseFunc(NULL);
    }
}






int main(int argc, char ** argv) {

    if (argc != 2) {
        std::cout << "Error: Engine requires .xml path" << std::endl;
        return -1;
    }
    

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif
    glEnableClientState(GL_VERTEX_ARRAY);


    try {
        if (!initContext(argv[1])) {
            std::cout << "Error: Provided .xml file is corrupted or not found" << std::endl;
            return -1;
        }
    } catch (std::invalid_argument const& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return -1;
    }


    

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glPolygonMode(GL_FRONT, GL_FILL);


    updateInputCallbacks();
    
    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
