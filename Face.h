// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef FACE_H
#define FACE_H

#include <GLFW/glfw3.h>
#include <iostream>

// Forward declaration
class HalfEdge;
// A single face for the DCEL data structure
class Face
{
public:
	// ## Variables ##
	HalfEdge* halfEdge;


	// ## Constructor ##
	Face(HalfEdge* he);

	// ## Functions ##

private:
	// ## Variables ##
	// ## Functions ##


};

// This is the end of the header guard
#endif