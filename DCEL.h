// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef DCEL_H
#define DCEL_H
#include <GLFW/glfw3.h>
#include "Face.h";
#include "HalfEdge.h";
#include "Vertex.h";
#include <vector>


// Forward declaration
class HalfEdge;
class Vertex;
class Face;
// Implementation of doublely connected edge list (DCEL) aka half-edge data structure
class DCEL
{
public:
	// ## Variables ##
	std::vector<Face> faceList;
	std::vector<Vertex> vertexList;
	std::vector<HalfEdge> halfEdgeList;
	// ## Constructor ##
	DCEL();
	// ## Functions ##

private:
	// ## Variables ##
	// ## Functions ##


};

// This is the end of the header guard
#endif