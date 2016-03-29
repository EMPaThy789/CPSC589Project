// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef DCEL_H
#define DCEL_H
#include <GLFW/glfw3.h>
#include <vector>
#include <stdlib.h> 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>


struct Vertex;
struct Face;
struct HalfEdge
{
	Vertex* vertex;   // vertex at the end of the half-edge
	HalfEdge* pair;   // oppositely oriented adjacent half-edge 
	Face* face;	      // face the half-edge borders
	HalfEdge* next;   // next half-edge around the face
};
struct Vertex
{
	float x;
	float y;
	float z;

	HalfEdge* halfEdge;  // one of the half-edges emantating from the vertex
};
struct Face
{

	HalfEdge* halfEdge;  // one of the half-edges bordering the face
};


// Forward declaration
class HalfEdge;
class Vertex;
class Face;
// Implementation of doublely connected edge list (DCEL) aka half-edge data structure
class DCEL
{
public:
	// ## Variables ##
	std::vector<Face*> faceList;
	std::vector<Vertex*> vertexList;
	std::vector<HalfEdge*> halfEdgeList;
	// ## Constructor ##
	DCEL();
	// ## Functions ##
	void readOBJ(std::string fileName);
	void drawMesh();

private:
	// ## Variables ##
	// ## Functions ##

};

// This is the end of the header guard
#endif