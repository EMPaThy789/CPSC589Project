/**
DCEL.h

doubly linked edge list header file
main data structure for storing mesh infomation
also where subdivision occurs


@author
Lanqin Yuan
Kiranpreet Bajwa
Aleks Djuric
*/

#ifndef DCEL_H
#define DCEL_H
#define PI 3.14159265
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
	HalfEdge* pair;   // oppositely oriented adjacent half-edge 
	HalfEdge* next;   // next half-edge around the face
	Vertex* vertex;   // vertex at the end of the half-edge
	Face* face;	      // face the half-edge borders
};
struct Vertex
{
	// one of the half-edges emantating from the vertex
	HalfEdge* halfEdge;
	// position
	float x;
	float y;
	float z;
	// normals
	float nx;
	float ny;
	float nz;

};
struct Face
{
	// one of the half-edges bordering the face
	HalfEdge* halfEdge;  
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

	void subdivide();

private:
	// ## Variables ##
	std::vector<Face*> tempFaceList;
	std::vector<Vertex*> tempVertexList;
	std::vector<HalfEdge*> tempHalfEdgeList;
	std::map<HalfEdge*,std::pair<HalfEdge*,HalfEdge*> > splitHalfEdges;
	std::map<Vertex*, Vertex*> movedVertexVertices;
	// ## Functions ##
	float getAlpha(int valence);
	std::vector<Vertex> findNeighbours(Vertex v);
	int countNeighbours(Vertex v);
	Vertex* newVertexVertex(Vertex oldVert, int n);
	void insertVertexVertices();

	Vertex* newEdgeVertex(HalfEdge *he);
	void subdivideFace(Face* f);

	std::vector<Vertex*> findEdgeNeighbours(HalfEdge he);

};

// This is the end of the header guard
#endif
