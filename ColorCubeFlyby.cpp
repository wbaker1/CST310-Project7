// Code modified by Wesley Baker for CST310 Project 7 Submission

// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>
// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.
float cameraX = 2.0f;
float cameraY = -1.0f;
float cameraZ = 5.0f;
float CameraX = 0.0f;
float CameraY = 0.0f;
float CameraZ = 0.0f;

float cameraSpeed = 0.1f;


GLfloat angle = 0.0; // rotation angle

namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint verticesCube1[NUM_VERTICES][3] = {
  {1, 1, 1}, {1, 1, 2}, {1, 2, 1}, {1, 2, 2},
  {2, 1, 1}, {2, 1, 2}, {2, 2, 1}, {2, 2, 2}};
  
GLint verticesCube2[NUM_VERTICES][3] = {
  {-1, -1,-1}, {-1,-1, 0}, {-1, 0, -1}, {-1, 0, 0},
  {0, -1, -1}, {0, -1, 0}, {0, 0, -1}, {0, 0, 0}};
  
GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};
  
GLfloat vertexColors1[NUM_VERTICES][3] = {
  {0.0, 1.0, 0.0}, {0.0, 2.0, 1.0}, {1.0, 1.0, 0.0}, {2.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

GLfloat vertexColors2[NUM_VERTICES][3] = {
  {1.0, 1.0, 0.0}, {0.0, 2.0, 1.0}, {0.0, 1.0, 0.0}, {2.0, 1.0, 1.0},
  {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}};

void draw() {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
  
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
  
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors1[faces[i][j]]);
      glVertex3iv((GLint*)&verticesCube1[faces[i][j]]);
    }
  }
  glEnd();
  
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors1[faces[i][j]]);
      glVertex3iv((GLint*)&verticesCube1[faces[i][j]]);
    }
  }
  glEnd();
  
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors2[faces[i][j]]);
      glVertex3iv((GLint*)&verticesCube2[faces[i][j]]);
    }
  }
  glEnd();
  
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors2[faces[i][j]]);
      glVertex3iv((GLint*)&verticesCube2[faces[i][j]]);
    }
  }
  glEnd();
  
}
}
namespace Plane {
void drawPlane(){

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(5.0, 25.0, -4.5);//Top Left Vertex
    glVertex3f(5.0, 25.0, 3.9);//Bottom Left Vertex
    glVertex3f(5.0, -25.0, 3.9);//Bottom Right Vertex
    glVertex3f(5.0, -25.0, -4.5);//Top Right Vertex
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-5.0, 25.0, -4.5);//Top Left Vertex
    glVertex3f(-5.0, 25.0, 3.9);//Bottom Left Vertex
    glVertex3f(-5.0, -25.0, 3.9);//Bottom Right Vertex
    glVertex3f(-5.0, -25.0, -4.5);//Top Right Vertex
    glEnd();

}
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  Cube::draw();
  Plane::drawPlane();
  glFlush();
  glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {
  static GLfloat u = 0.0;
  u += 0.01;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, CameraX, CameraY, 0.0f, 0.0f, 1.0f, 0.0f);
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

void rotate(int value)
{
    angle += 3.0; // increment the angle by 2 degrees
    if (angle > 360.0)
        {
            angle -= 360.0; // wrap around at 360 degrees
        }
    std::cout<<angle<<"\n";
    glutPostRedisplay();
    glutTimerFunc(125, rotate, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
       
    case 'r': // Make image rotate
    	glutTimerFunc(10, rotate, 0); // start the rotation timer
        break;
    
    case '-': // Zoom Out 
    	cameraZ += cameraSpeed;
    	break;
    
    case '=': // Zoom In
    	cameraZ -= cameraSpeed;
    	break;
    	
    case 'c': // Start rotatating the triangle
    	glutTimerFunc(100, timer, 0); // start the rotation timer
    	break;
    	
    case 'p': 
    	break;
    	
    case 'u': // Move Image Up
        cameraY -= cameraSpeed;
        CameraY -= cameraSpeed;
        break;
        
    case 'd': // Move Image Down
        cameraY += cameraSpeed;
        CameraY += cameraSpeed;
        break;
    }
    
    //std::cout << "Camera X: " << cameraX << std::endl;
    glutPostRedisplay();
    
}
// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutDisplayFunc(display);
  glutTimerFunc(100, timer, 0); // start the rotation timer
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  init();
  glutMainLoop();
}
