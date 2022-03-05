#include <math.h>
#include "plane.hpp"
#include "box.hpp"
#include <vector>
#include "../utils/point.hpp"
#include <iostream>
#include <string>
#include <fstream>

/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif






float color1 = 0.0f;
float color2 = 0.0f;
float color3 = 0.0f;
int j = 1;


static float angle_x = 0.0f;
static float angle_y = 0.0f;
static float angle_z = 0.0f;
static int current_mode = GL_FILL;

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
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

bool entered = false;

void renderScene(void) {

    float edge = 2;
    float divisions = 3;
    std::vector<Point> points;

    std::cout << "BOAS" << std::endl;

    Plane plane(edge, divisions);
    points = plane.draw();

    for (int i = 0; i < points.size(); ++i) {
        std::cout << std::to_string(points.at(i).x) + " " + std::to_string(points.at(i).y) + " " + std::to_string(points.at(i).z) << std::endl;
    }


    Box box(edge, divisions);
    points = box.draw();

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);

    // put the geometric transformations here

    glRotatef(angle_x, 1.0f, 0.0f, 0.0f); // angle is in degrees
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f); // angle is in degrees
    glRotatef(angle_z, 0.0f, 0.0f, 1.0f); // angle is in degrees


    // put drawing instructions here

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

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < points.size(); ++i) {
        if (!entered) {
            //std::cout << points[i].x << " " << points[i].y << " " << points[i].z << std::endl;
        }
        glVertex3f(points[i].x, points[i].y, points[i].z);
        j++;
    }
    //if (!entered)
        //std::cout << points.size() << std::endl;
    entered = true;

    glEnd();

    // End of frame
    glutSwapBuffers();
}


void keyboardKeysFunc(unsigned char key, int x, int y) {


    switch (key) {
    case 'q':
        angle_x += 5; break;
    case 'a':
        angle_x -= 5; break;
    case 'w':
        angle_y += 5; break;
    case 's':
        angle_y -= 5; break;
    case 'e':
        angle_z += 5; break;
    case 'd':
        angle_z -= 5; break;

    case 'z':
        switch (current_mode) {
        case GL_FILL: current_mode = GL_LINE; break;
        case GL_LINE: current_mode = GL_POINT; break;
        default: current_mode = GL_FILL;
        }

        glPolygonMode(GL_FRONT, current_mode);
    }


    glutPostRedisplay();
}



int main(int argc, char** argv) {

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
    glutKeyboardFunc(keyboardKeysFunc);


    // put here the registration of the keyboard callbacks


    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
*/

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
            std::cout << "Plane necessita de 4 argumentos" << std::endl;
        }
    }else if(!figure.compare("box")){
        if(argc == 5){
            float size = atof(argv[2]);
            float divisions = atof(argv[3]);
            file = argv[4];

            Box box(size, divisions);
            points = box.draw();
                                
        }else{
            std::cout << "Box necessita de 4 argumentos" << std::endl;
        }
    }else{
        std::cout << "Comando nao disponivel" << std::endl;
    }
    
    if(!points.empty())
        writeToFile(points, file);

    return 0;
    
}

