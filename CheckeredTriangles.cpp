// Code modified by Wesley Baker for CST310 Project 7 Submission

// This application is a trivial illustration of texture mapping.  It draws
// several triangles, each with a texture mapped on to it.  The same texture
// is used for each triangle, but the mappings vary quite a bit so it looks as
// if each triangle has a different texture.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

#include<iostream>

// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}

GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

float cameraX = 2.0f;
float cameraY = -1.0f;
float cameraZ = 5.0f;
float CameraX = 0.0f;
float CameraY = 0.0f;
float CameraZ = 0.0f;

float cameraSpeed = 0.1f;


GLfloat angle = 0.0; // rotation angle

// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, GLfloat(width)/height, 1, 40);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                    // level 0
               3,                    // use only R, G, and B components
               2, 2,                 // texture has 2x2 texels
               0,                    // no border
               GL_RGB,               // texels are in RGB format
               GL_UNSIGNED_BYTE,     // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, CameraX, CameraY, 0.0f, 0.0f, 1.0f, 0.0f); 
  // rotate the texture
  glTranslatef(0.5, 0.5, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, -0.5, 0.0);
 
  	glEnable(GL_TEXTURE_2D);
 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    
  	glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);    glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0);    glVertex2f(0, 0);

    glTexCoord2f(4, 8);        glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(0, 0);
    glTexCoord2f(8, 0.0);      glVertex2f(3, 0);

    glTexCoord2f(5, 5);        glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
  	glEnd();
  //glFlush();
    glutSwapBuffers();
}

void rotateTriangle(int value)
{
    angle += 3.0; // increment the angle by 2 degrees
    if (angle > 360.0)
        {
            angle -= 360.0; // wrap around at 360 degrees
        }
    std::cout<<angle<<"\n";
    glutPostRedisplay();
    glutTimerFunc(125, rotateTriangle, 0);
}

void stopRotation(int value)
{
    angle = 0.0; // increment the angle by 2 degrees
    glutPostRedisplay();
    glutTimerFunc(125, stopRotation, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'l': // Move Image Left
        cameraX += cameraSpeed;
        CameraX += cameraSpeed;
        break;
        
    case 'r': // Move Image Right
        cameraX -= cameraSpeed;
        CameraX -= cameraSpeed;
        break;
    
    case '-': // Zoom Out 
    	cameraZ += cameraSpeed;
    	break;
    
    case '=': // Zoom In
    	cameraZ -= cameraSpeed;
    	break;
    	
    case 'c': // Start rotatating the triangle
    	glutTimerFunc(10, rotateTriangle, 0); // start the rotation timer
    	break;
    	
    case 'p': // Stop rotatating the triangle ***NOTE THIS ONLY WORKS ONCE THEN YOU CANNOT ROTATE 
    											//AGAIN UNTIL STOPPING THE PROGRAM***
    	glutTimerFunc(10, stopRotation, 0); // start the rotation timer
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

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv)
    {
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
      glutInitWindowSize(520, 390);
      glutCreateWindow("Textured Triangles");
       
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glLoadIdentity();
      glutDisplayFunc(display);
      glutKeyboardFunc(keyboard);  
      glutReshapeFunc(reshape);
      glutMainLoop();
      return 0;
    }
