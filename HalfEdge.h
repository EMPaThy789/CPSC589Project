// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <GLFW/glfw3.h>

// Forward declaration
class Vertex;
class Face;

// Class for one half edge
class HalfEdge
{
public:
	// ## Constructor ##
	HalfEdge(Vertex* v, Face* f, HalfEdge n, HalfEdge p);

	// ## Variables ##
	Vertex* vertex;     // vertex at beginning
	Face* face;         // face at the left
	HalfEdge* next;     // next half edge
	HalfEdge* pair;     // opposite half edge
	// ## Functions ##
	


private:
	// ## Variables ##

	// ## Functions ##

};

// This is the end of the header guard
#endif