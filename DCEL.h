// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef DCEL_H
#define DCEL_H
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;


// Forward declaration
class HalfEdge;
class Vertex;
class Face;
// Implementation of doublely connected edge list (DCEL) aka half-edge data structure
class DCEL
{
public:
	// ## Constructor ##
	DCEL();
	// ## Variables ##
	vector<Face> faceList;
	vector<Vertex> vertexList;
	vector<HalfEdge> halfEdgeList;
	// ## Functions ##

private:
	// ## Variables ##
	// ## Functions ##


};

// This is the end of the header guard
#endif