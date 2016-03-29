#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string> 
#include <stdlib.h>
#include "HalfEdge.h"
#include "Face.h"
#include "Vertex.h"
#include "obj.h"

using namespace std;

struct Point
{
	float x, y;
};

GLFWwindow *window;
int w, h;
float x, y, z, rY, rX;

double mouseX, mouseY;
const int WINDOW_HEIGHT = 600,
          WINDOW_WIDTH = 800;






void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods)
{
	
	

	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y -= 0.1;
	}
	if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y += 0.1;
	}
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		z -= 0.1;
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		z += 0.1;
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x -= 0.1;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x += 0.1;
	}
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

	
	
}



void mouseClick(GLFWwindow *sender, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
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

	//Functions for changing projection mdatrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, 500.0, 500.0, 0, 1.0, -1.0); 
	float aspect = 1;// ((float)WINDOW_HEIGHT) / WINDOW_WIDTH;
	//gluPerspective(90.0f, aspect, 0.1f, 100.0f);
	float near = 0.01f;
	float far = 10.0f;
	float fov = 90.0f;

	double fH = tan(fov / 360 * 3.1415926535897932384626433832795) * near;
	double fW = fH * aspect;


	glFrustum(-fW, fW, -fH, fH, near, far);

	
	
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
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
	glEnd();  // End of drawing color-cube

}

int main(int argc, char* argv[])
{
	x = 0;
	y = 0;
	z = -3;
	rX = 0;
	rY = 0;

    //Obj thisOne = Obj("cube.obj");
    
	if (!glfwInit())
		return 1;
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);
	glfwSetMouseButtonCallback(window, mouseClick);
	glfwSetCursorPosCallback(window, mousePos);
	
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
