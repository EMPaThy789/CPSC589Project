#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string> 
#include <stdlib.h>

using namespace std;

struct Point
{
	float x, y;
};

GLFWwindow *window;
int w, h;
double mouseX, mouseY;


int order = 3;

vector<Point> controlPointList;
double knotSequence[5000];
int numberOfKnots = 0;
int geometryToggle = 0;
Point *selectedControlPoint;
int selectedIndex = -1;
double inc = 0.01;
double geoInc = 0;





// delta index function
int deltaFunction(double u, int k)
{
	for (int i = 0; i < numberOfKnots + k - 2; i++)
	{
		if (u >= knotSequence[i] && u < knotSequence[i + 1])
			return i;
	}
	return -1;
}


Point efficentBasis(int k, double u)
{
	int d = deltaFunction(u, k);

	Point c[k-1];
	for (int i = 0; i <= k - 1; i++)
	{
		// make sure the program doesnt crash
		if (d - i < controlPointList.size())
		{
			c[i] = controlPointList[d - i];
		}
	}

	for (int r = k; r >= 2; r--)
	{
		

		int i = d;
		for (int s = 0; s <= r - 2; s++)
		{
			double omega = (u - knotSequence[i]) / (knotSequence[i + r - 1] - knotSequence[i]);
			c[s].x = omega * c[s].x + (1 - omega) * c[s + 1].x;
			c[s].y = omega * c[s].y + (1 - omega) * c[s + 1].y;

			i--;
		}
	}
	return c[0];
}

Point efficentBasisDrawGeo(int k, double u)
{
	int d = deltaFunction(u, k);

	Point c[1000];
	for (int i = 0; i <= k - 1; i++)
	{
		// make sure the program doesnt crash
		if (d - i < controlPointList.size())
		{
			c[i] = controlPointList[d - i];
		}
	}

	for (int r = k; r >= 2; r--)
	{
		if (geometryToggle)
		{
			glColor3f(0.0f, 1.0f, 0.5f);
			glBegin(GL_LINE_STRIP);
		}

		int i = d;
		for (int s = 0; s <= r - 2; s++)
		{
			double omega = (u - knotSequence[i]) / (knotSequence[i + r - 1] - knotSequence[i]);
			c[s].x = omega * c[s].x + (1 - omega) * c[s + 1].x;
			c[s].y = omega * c[s].y + (1 - omega) * c[s + 1].y;

			if (geometryToggle)
				glVertex2d(c[s].x, c[s].y);

			i--;
		}
		if (geometryToggle)
			glEnd();
	}


	glPointSize(10.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POINTS);
	glVertex2d(c[0].x, c[0].y);
	glEnd();
	return c[0];
}


double bsplineBasis(int i, int k, double u)
{
	if (k == 1)
	{
		if (knotSequence[i] <= u && u < knotSequence[i + 1])
			return 1;
		return 0;
	}

	return 
		bsplineBasis(i, k - 1, u) * ((u - knotSequence[i]) / (knotSequence[i + k - 1])) + 
		bsplineBasis(i + 1, k - 1, u) * (knotSequence[i + k] - u) / ((knotSequence[i + k] - knotSequence[i + 1]));
}

void updateKnotSequence()
{
	if (controlPointList.size() - order + 2 > 0)
	{
		numberOfKnots = order + controlPointList.size();
		double stepSize =(controlPointList.size() - order + 1);
		cout << (controlPointList.size() - order + 2);
		
		int z = 0;
		for (int i = 0; i < order; i++)
		{
			knotSequence[z] = 0;
			z++;
		}

		for (int i = 0; i < numberOfKnots - 2 * order; i++)
		{
			knotSequence[z] = (1 / stepSize) * (i + 1);
			z++;
		}

		for (int i = 0; i < order; i++)
		{
			knotSequence[z] = 1;
			z++;
		}
	}
}

void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		geoInc -= inc;
		if (geoInc < 0)
			geoInc = 0;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		geoInc += inc;
		if (geoInc > 1)
			geoInc = 1;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		order++;
		updateKnotSequence();
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		order--;
		updateKnotSequence();
	}

	if (key == GLFW_KEY_X && (action == GLFW_PRESS))
	{
		for (int i = 0; i < numberOfKnots; i++)
		{

			cout << knotSequence[i] << '\n';
		}
	}
	
	if (key == GLFW_KEY_T && (action == GLFW_PRESS))
	{
		if (geometryToggle)
			geometryToggle = 0;
		else
			geometryToggle = 1;
	}

	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS))
	{
		selectedControlPoint = NULL;
		int i;
		for (i = 0; i < controlPointList.size(); i++)
		{
			double x = controlPointList[i].x;
			double y = controlPointList[i].y;
			cout << x << ' ' << y << '\n';
		}
	}
	
	// delete control point if one is selected
	if (key == GLFW_KEY_DELETE && (action == GLFW_PRESS) && selectedIndex != -1)
	{
		controlPointList.erase(controlPointList.begin() + selectedIndex);
		updateKnotSequence();
		selectedControlPoint = NULL;
	}
	
}



void mouseClick(GLFWwindow *sender, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// no control point selected
		if (selectedControlPoint == NULL)
		{
			// add new control point
			Point p;
			p.x = mouseX;
			p.y = mouseY;
			controlPointList.push_back(p);
			cout << mouseX << ' ' << mouseY << '\n';
			updateKnotSequence();
		}
		else
		{
			// move control points if one is selected
			(*selectedControlPoint).x = mouseX;
			(*selectedControlPoint).y = mouseY;
		}
	}


	// selecting control points
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		for (int i = 0; i < controlPointList.size(); i++)
		{
			double x = controlPointList[i].x;
			double y = controlPointList[i].y;
			if (40 > (x - mouseX) * (x - mouseX) + (y - mouseY) * (y - mouseY))
			{
				selectedControlPoint = &controlPointList[i];
				selectedIndex = i;
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
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 0.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	//Functions for changing projection mdatrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500.0, 500.0, 0, 1.0, -1.0);
	//gluPerspective (fov, aspect ratio, near plane, far plane)
	//glFrustum

	glPointSize(10.0);
	// draw control points
	for (int i = 0; i < controlPointList.size(); i++)
	{
		if (&controlPointList[i] == selectedControlPoint)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else
		{
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		glBegin(GL_POINTS);
		glVertex2d(controlPointList[i].x, controlPointList[i].y);
		glEnd();
	}

	// draw bspline curve

	if (controlPointList.size() >= order)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 1.0f, 1.0f);


		for (double i = 0; i <= 1; i += inc)
		{
			Point p = efficentBasis(order, i);
			glVertex2d(p.x, p.y);
		}
		glEnd();

		if (geometryToggle)
			efficentBasisDrawGeo(order, geoInc);
	}



	// drawing line through control points
	if (geometryToggle)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 1.0f, 0.0f);
		for (int i = 0; i < controlPointList.size(); i++)
		{
			double x = controlPointList[i].x;
			double y = controlPointList[i].y;
			glVertex2d(x, y);
		}
		glEnd();
	}


}

int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		order = atoi(argv[1]);
		inc = atof(argv[2]);
		cout << order << ' ' << inc << '\n';
	}

	if (!glfwInit())
		return 1;

	window = glfwCreateWindow(500, 500, "My Window", NULL, NULL);
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
