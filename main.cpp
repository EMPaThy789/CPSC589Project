/**
main.cpp
main entrypoint into program

@author
Lanqin Yuan
Kiranpreet Bajwa 
Aleks Djuric
*/
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string> 
#include <stdlib.h>
#include "DCEL.h"
#include <OPENGL/gl.h> //@TODO: Change OPENGL to GL before handing in.
#include <OPENGL/glu.h>

using namespace std;

struct Point
{
	float x, y;
};

GLFWwindow *window;
int w, h;
float x, y, z, rY, rX, lx = 0,ly = 0,lz =0;
int wireframe = 0;
double mouseX, mouseY;
const int WINDOW_HEIGHT = 600,
          WINDOW_WIDTH = 800;
           Vertex* somePoint;

DCEL dcel;





void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods)
{
	// backward and forward translation
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		z -= 0.1;
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		z += 0.1;
	}
	
		//LIGHT CONTROLS
	if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		lx -= 0.4;
	}
	if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		lx += 0.4;
	}
	if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		ly -= 0.4;
	}
	if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		ly += 0.4;
	}
	
	if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		lz -= 0.4;
	}if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		lz += 0.4;
	}
	
	/* these seem a bit rekt atm so dont use
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x -= 0.1;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x += 0.1;
	}
	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y -= 0.1;
	}
	if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y += 0.1;
	}*/
	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS))
	{
		dcel.subdivide();
	}

	// rotation
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		rY -= 2;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		rY += 2;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		rX -= 2;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		rX += 2;
	}

	if (key == GLFW_KEY_M && (action == GLFW_PRESS) )
	{
		if (wireframe)
			wireframe = 0;
		else 
			wireframe = 1;
	}
		
		
	if (key == GLFW_KEY_KP_7 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->x -= 1;
	}
	if (key == GLFW_KEY_KP_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->x +=1;
	}
	if (key == GLFW_KEY_KP_8 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->y -= 1;
	}
	if (key == GLFW_KEY_KP_5 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->y +=1;
	}
		if (key == GLFW_KEY_KP_9 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->z -= 1;
	}
	if (key == GLFW_KEY_KP_6 && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		somePoint->z +=1;
	}
	
	
}



void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
  
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){               
        
        GLint viewport[4]; 
        glGetIntegerv( GL_VIEWPORT, viewport ); 
        GLdouble modelview[16]; 
        glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); 
        GLdouble projection[16]; 
        glGetDoublev( GL_PROJECTION_MATRIX, projection );
        GLfloat winX, winY, winZ; 
        
        //GLdouble worldX, worldY, worldZ;
        winX = (float)mouseX;
        winY = (float)viewport[3] - (float)mouseY;
        glReadPixels(mouseX, int(winY),1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);
        
        
        GLdouble vX, vY, vZ;  
         
        //World coordinates from the given screen coordinates
     //   gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
               
               cout << "WINX IS: " << winX << endl;
               cout << "WINY is: " << winY << endl;
               cout << "WINZ is : " << winZ << endl;

               
               for(int i=0; i < dcel.vertexList.size();i++){
			   gluProject(dcel.vertexList[i]->x, dcel.vertexList[i]->y, dcel.vertexList[i]->z,
							modelview,projection,viewport, &vX, &vY, &vZ);

			   
			   if((winX - vX) <= 5 && (winX - vX) >= -5 ){
					if((winY -vY) <= 5 && (winY -vY) >= -5){
						cout << "Found Point: " << endl;
				cout << "vX : " << vX << endl;
			   cout << "vY : " << vY << endl;
			   cout << "Vertex Z : " << dcel.vertexList[i]->z << endl;
			   cout << "vZ : :" << vZ << endl;
			   somePoint = dcel.vertexList[i];
			   break;
					}
			   }
			   
			   }
    }
}


void mousePos(GLFWwindow *sender, double x, double y)
{
	mouseX = x;
	mouseY = y;
}

void render()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, 0.0f); 
	//glTranslatef(-0.5f, 2.0f, 0.5f);
	glTranslatef(x, y, z);
	glRotatef(rY, 0.0f, 1.0f, 0.0f);
	glRotatef(rX, 1.0f, 0.0f, 0.0f);
	//glScalef(0.5f, 0.5f, 0.5f);
    
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_position[] = { static_cast<GLfloat>(0.0+lx), static_cast<GLfloat>(-1.0+ly), static_cast<GLfloat>(-1.0+lz), 0.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);


	//Functions for changing projection mdatrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, 500.0, 500.0, 0, 1.0, -1.0); 
	float aspect = ((float)WINDOW_WIDTH) / WINDOW_HEIGHT;
	//gluPerspective(90.0f, aspect, 0.1f, 100.0f);
	float near = 0.01f;
	float far = 30.0f;
	float fov = 90.0f;

	double fH = tan(fov / 360 * 3.1415926535897932384626433832795) * near;
	double fW = fH * aspect;
	if(wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glFrustum(-fW, fW, -fH, fH, near, far);

	dcel.drawMesh();
	
	/*glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube*/

}

int main(int argc, char* argv[])
{
	x = 0;
	y = 0;
	z = -10;
	rX = 0;
	rY = 0;
	


	if (!glfwInit())
		return 1;
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);
	glfwSetMouseButtonCallback(window, mouseClick);
	glfwSetCursorPosCallback(window, mousePos);

    string s = "";
    cout << "Please enter file name" << endl;
    cin >> s;
	dcel.readOBJ(s);
	
	while (!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
