#include <math.h>
#include "plane.hpp"
#include "box.hpp"
#include <vector>
#include "../utils/point.hpp"
#include <iostream>
#include <string>

#include <GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float color1 = 0.0f;
float color2 = 0.0f;
float color3 = 0.0f;
int j = 1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    float edge = 2;
    float divisions = 3;
    std::vector<Point> points;

    std::cout << "BOAS" << std::endl;


    Box box(edge, divisions);
    points = box.draw();

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    // put the geometric transformations here


    // put drawing instructions here
            
            // X axis in red
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-100.0f, 0.0f, 0.0f);
            glVertex3f( 100.0f, 0.0f, 0.0f);
            // Y Axis in Green
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, -100.0f, 0.0f);
            glVertex3f(0.0f, 100.0f, 0.0f);
            // Z Axis in Blue
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, -100.0f);
            glVertex3f(0.0f, 0.0f,  100.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
            for(int i = 0; i < points.size(); ++i){
                if(j % 2 == 0){
                    if(color1 < 1.0f){
                        color1 += 0.6f;
                        color2 += 0.2f;
                        color3 += 0.1f;
                    }else{
                        color1 -= 0.7f;
                        color2 -= 0.4f;
                        color3 -= 0.2f;
                    }
                    glColor3f(color1, color2, color3);
                }
                
                glVertex3f(points[i].x, points[i].y,points[i].z);
                j++;
            }

             glEnd();

	// End of frame
	glutSwapBuffers();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	
// put here the registration of the keyboard callbacks


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

/*
int main(int argc, char **argv) {
    float edge = 2;
    float divisions = 3;
    std::vector<Point> points;

    std::cout << "BOAS" << std::endl;


    Plane plane(edge, divisions);
    points = plane.draw();
 
    for (int i = 0; i < points.size(); ++i) {
        std::cout << "Pontos : X --> " + std::to_string(points.at(i).x) + " Y ---> "+ std::to_string(points.at(i).y) + " Z ----> " + std::to_string(points.at(i).z) << std::endl;
    }

    return 0;
    
}
*/