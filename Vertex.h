// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef VERTEX_H
#define VERTEX_H

#include <GLFW/glfw3.h>
#include <iostream>

// Forward declaration
class HalfEdge;

// A single vertex for the DCEL data structure
class Vertex
{
public:
	// ## Variables ##

	// position
	float x, y, z;
	// normal
	float nX, nY, nZ;
	HalfEdge* halfEdge;


	// ## Constructor ##
	Vertex(float x, float y, float z, HalfEdge* he, float nx, float ny, float nz);

	// ## Functions ##

private:
	// ## Variables ##
	// ## Functions ##


};

// This is the end of the header guard
#endif