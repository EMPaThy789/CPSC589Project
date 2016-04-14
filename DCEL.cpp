/**
DCEL.cpp

doubly linked edge list
main data structure for storing mesh infomation
also where subdivision occurs

@author
Lanqin Yuan
Kiranpreet Bajwa
Aleks Djuric
*/

#include "DCEL.h"
#include "math.h"
using namespace std;


// Implementation of doublely connected edge list (DCEL) aka half-edge data structure

// constructor
DCEL::DCEL()
{

}

// Methods go here
void DCEL::readOBJ(string fileName)
{
	//ifstream file;

	//file.open(fileName);
    
    ifstream file(fileName.c_str());

	//cout << getcwd(NULL, 0);

	if (!file.is_open()){
		cout << "Error could not open file" << endl;
	}
	else {
		//parse the vertices and faces

		DCEL dcel = DCEL();

		string line;

		int vertexIndex = 0;

		map <pair<unsigned int, unsigned int>, HalfEdge*> Edges;

		while (!file.eof())
		{
			//file >> word;
			//getline(file, line);
			string var1;
			double var2, var3, var4;
			file >> var1 >> var2 >> var3 >> var4;

			
			if (var1[0] == 'v')
			{
				// read normals for vertex
				if (var1[1] == 'n')
				{
					Vertex* v = vertexList[vertexIndex];
					// set normals
					v->nx = -1;
					v->ny = -1;
					v->nz = -1;
					vertexIndex++;
				}
				else 
				// read vertex data
				{

					// read into DCEL structure
					Vertex* v = (Vertex*)malloc(sizeof(struct Vertex));
					v->x = var2;
					v->y = var3;
					v->z = var4;
                    
                    v->nx = -1;
                    v->ny = -1;
                    v->nz = -1;
					vertexList.push_back(v);
				}
			}
			
			
			
			// assumption is made that mesh is entirely triagular
			if (var1[0] == 'f')
			{
				int reverseFaceBoolean = 0;
				Face* f = (Face*)malloc(sizeof(struct Face));
				HalfEdge* he1 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
				HalfEdge* he2 = (HalfEdge*)malloc(sizeof(struct HalfEdge));;
				HalfEdge* he3 = (HalfEdge*)malloc(sizeof(struct HalfEdge));;
				
				
				//TODO fix this shit
				if (Edges[make_pair(var2, var3)] != NULL || Edges[make_pair(var3, var4)] != NULL || Edges[make_pair(var4, var2)] != NULL)
				{
					reverseFaceBoolean = 1;
				}

				// vertex numbers
				double vn1, vn2, vn3;

				// if face is in reverse
				if (reverseFaceBoolean == 1)
				{
					vn1 = var4;
					vn2 = var3;
					vn3 = var2;
				}
				else
				{
					vn1 = var2;
					vn2 = var3;
					vn3 = var4;
				}



				Vertex* v1 = vertexList.at(vn1 - 1);
				Vertex* v2 = vertexList.at(vn2 - 1);
				Vertex* v3 = vertexList.at(vn3 - 1);


				he1->face = f;
				he2->face = f;
				he3->face = f;

				v1->halfEdge = he1;
				v2->halfEdge = he2;
				v3->halfEdge = he3;

				he1->next = he2;
				he2->next = he3;
				he3->next = he1;

				he1->vertex = v1;
				he2->vertex = v2;
				he3->vertex = v3;



				if (Edges[make_pair(vn1, vn2)] == NULL)
				{
					Edges[make_pair(vn1, vn2)] = he1;
				}
				if (Edges[make_pair(vn2, vn3)] == NULL)
				{
					Edges[make_pair(vn2, vn3)] = he2;
				}
				if (Edges[make_pair(vn3, vn1)] == NULL)
				{
					Edges[make_pair(vn3, vn1)] = he3;
				}


				if (Edges[make_pair(vn2, vn1)] != NULL)
				{
					he1->pair = Edges[make_pair(vn2, vn1)];
					Edges[make_pair(vn2, vn1)]->pair = he1;
				} 
				else if(Edges[make_pair(vn1, vn2)] != NULL)
				{
					he1->pair = Edges[make_pair(vn1, vn2)];
					Edges[make_pair(vn1, vn2)]->pair = he1;
				}

				if (Edges[make_pair(vn3, vn2)] != NULL)
				{
					he2->pair = Edges[make_pair(vn3, vn2)];
					Edges[make_pair(vn3, vn2)]->pair = he2;
				} else
				if (Edges[make_pair(vn2, vn3)] != NULL)
				{
					he2->pair = Edges[make_pair(vn2, vn3)];
					Edges[make_pair(vn2, vn3)]->pair = he2;
				}


				if (Edges[make_pair(vn1, vn3)] != NULL)
				{
					he3->pair = Edges[make_pair(vn1, vn3)];
					Edges[make_pair(vn1, vn3)]->pair = he3;
				} else
				if (Edges[make_pair(vn3, vn1)] != NULL)
				{
					he3->pair = Edges[make_pair(vn3, vn1)];
					Edges[make_pair(vn3, vn1)]->pair = he3;
				}
				
				f->halfEdge = he1;
				faceList.push_back(f);
				halfEdgeList.push_back(he1);
				halfEdgeList.push_back(he2);
				halfEdgeList.push_back(he3);
			}
			cout << var1 << var2 << var3 << var4 << "\n";
		}
		file.close();
        
        cout << "Faces: " << faceList.size() << endl;
        cout << "Half edges: " << halfEdgeList.size() << endl;
        cout << "Vertices: " << vertexList.size() << endl;
	}
}

// actually draw the mesh
void DCEL::drawMesh()
{
    Face* f;

	glBegin(GL_TRIANGLES);
    for (int i = 0; i < faceList.size(); i++){
		Vertex* v[3];

        f = faceList[i];
        //cout<< faceList.size() << " THIs is the size " << endl;
		HalfEdge* he = f->halfEdge;

		for (int i = 0; i < 3; i++)
		{
            //cout<< "HERE " << he->vertex;
			v[i] = he->vertex;
			he = he->next;
		}
		glColor3f(0.22f, 1.0f, 0.08f);     // red
		glNormal3f(v[0]->nx, v[0]->ny, v[0]->nz);
		glVertex3f(v[0]->x, v[0]->y, v[0]->z);


		glNormal3f(v[1]->nx, v[1]->ny, v[1]->nz);
		glVertex3f(v[1]->x, v[1]->y, v[1]->z);

		glNormal3f(v[2]->nx, v[2]->ny, v[2]->nz);
		glVertex3f(v[2]->x, v[2]->y, v[2]->z);


	}
	glEnd();
}

//Finding the neighbours
vector<Vertex> DCEL::findNeighbours(Vertex v) {
	vector <Vertex> neigh;
	HalfEdge* e = v.halfEdge->pair;

	// last halfEdge to visit
	HalfEdge * endEdge = e;


	do
	{
		Vertex neighbour = *e->vertex;
		neigh.push_back(neighbour);
		e = e->next->pair;
	} while (e != endEdge);
	return neigh;
}

//Finding the neighbours
int DCEL::countNeighbours(Vertex v)
{
	int neigh = 0;
	HalfEdge* e = v.halfEdge->pair;

	// last halfEdge to visit
	HalfEdge* endEdge = e;



	do
	{
 		neigh = neigh + 1;
		e = e->next->pair;
	} while (e != endEdge);
	//cout << neigh;

	return neigh;
}


float DCEL::getAlpha(int valence){
	double cosTerm = (1.0 / 4.0) * cos((2.0 * PI / valence));
	double innerTerm = pow((3.0 / 8.0) + cosTerm, 2);
	float alpha = (float)((1.0 / valence) * ((5.0 / 8.0) - innerTerm));
	return alpha;
}


Vertex* DCEL::newVertexVertex(Vertex* oldVert, int n)
{
	
	float alpha = 0.0;
	Vertex* vNew = (Vertex*)malloc(sizeof(struct Vertex));
	if (selectedPoints.end() != find(selectedPoints.begin(),selectedPoints.end(),oldVert))
	{
		vNew -> x = oldVert->x;
		vNew -> y = oldVert->y;
		vNew -> z = oldVert->z;
		tempSelectedPoints.push_back(vNew);
		return vNew;
	}
	
	vector <Vertex> neighbour = findNeighbours(*oldVert);

	
	alpha = getAlpha(n);

	vNew->x = (1.0 - n * alpha) * oldVert->x;
	vNew->y = (1.0 - n * alpha) * oldVert->y;
	vNew->z = (1.0 - n * alpha) * oldVert->z;

	Vertex sum;
	sum.x = 0;
	sum.y = 0;
	sum.z = 0;

	for (int i = 0; i < n; i++){

		sum.x = sum.x + neighbour[i].x;
		sum.y = sum.y + neighbour[i].y;
		sum.z = sum.z + neighbour[i].z;
	}

	sum.x = alpha * sum.x;
	sum.y = alpha * sum.y;
	sum.z = alpha * sum.z;

	vNew->x = vNew->x + sum.x;
	vNew->y = vNew->y + sum.y;
	vNew->z = vNew->z + sum.z;
    
    vNew->nx = -1;
    vNew->ny = -1;
    vNew->nz = -1;

	return vNew;
}


void DCEL::insertVertexVertices()
{
	vector<Vertex*> newVertexList;
	for (int i = 0; i < vertexList.size(); i++)
	{
		/*vertexList[i]->x = newVertexVertex(*vertexList[i], countNeighbours(*vertexList[i])).x;
		vertexList[i]->y = newVertexVertex(*vertexList[i], countNeighbours(*vertexList[i])).y;
		vertexList[i]->z = newVertexVertex(*vertexList[i], countNeighbours(*vertexList[i])).z;*/
		Vertex* v = newVertexVertex(vertexList[i], countNeighbours(*vertexList[i]));
		tempVertexList.push_back(v);
		movedVertexVertices[vertexList[i]] = v;
	}
	/*
	for (int i = 0; i < vertexList.size(); i++)
	{
		free(vertexList[i]);
	}
	vertexList.clear();

	for (int i = 0; i < newVertexList.size(); i++)
	{
		vertexList.push_back(newVertexList[i]);
	}*/
}

void DCEL::subdivide()
{
	for (int i = 0; i < tempVertexList.size(); i++) {
		free(tempVertexList[i]);
	}
	for (int i = 0; i < tempFaceList.size(); i++) {
		free(tempFaceList[i]);
	}
	for (int i = 0; i < tempHalfEdgeList.size(); i++) {
		free(tempHalfEdgeList[i]);
	}
		
	tempVertexList.clear();
	tempFaceList.clear();
	tempHalfEdgeList.clear();

	splitHalfEdges.clear();
	movedVertexVertices.clear();


	insertVertexVertices();
	for (int i = 0; i < faceList.size(); i++)
	{
		subdivideFace(faceList[i]);
	}

	// free memory

	
	vertexList.clear();
	faceList.clear();
	halfEdgeList.clear();

	faceList.swap(tempFaceList);
	halfEdgeList.swap(tempHalfEdgeList);
	vertexList.swap(tempVertexList);

	cout << "done";
    
    cout << "Faces: " << faceList.size() << endl;
    cout << "Half edges: " << halfEdgeList.size() << endl;
    cout << "Vertices: " << vertexList.size() << endl;
}

// finds vertices used to make new edge vertex for a given half edge
vector<Vertex*> DCEL::findEdgeNeighbours(HalfEdge he)
{
	vector<Vertex*> edgeNeighbours;
	HalfEdge* e = &he;

	// 3/8 v1
	edgeNeighbours.push_back(e->vertex);	

	// 3/8 v2
	e = e->next;
	edgeNeighbours.push_back(e->vertex);

	// 1/8 v3
	e = e->next;
	edgeNeighbours.push_back(e->vertex);


	// 1/8 v4
	e = he.pair;
	e = e->next; 
	e = e->next;
	edgeNeighbours.push_back(e->vertex);

	// index 0 and 1 are 3/8 vertices, index 2 and 3 are 1/8 vertices
	return edgeNeighbours;
}


// creates a new edge vertex for a given half edge
Vertex* DCEL::newEdgeVertex(HalfEdge* he)
{
	pair<HalfEdge*, HalfEdge*> pairEdges = splitHalfEdges[he->pair];
	vector<Vertex*> edgeNeighbours = findEdgeNeighbours(*he);
	Vertex* v;
	HalfEdge* tempNext = he->next;

	// create new half edges
	HalfEdge* newHe1 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
	HalfEdge* newHe2 = (HalfEdge*)malloc(sizeof(struct HalfEdge));

	// if the edge has not been split before
	if (pairEdges.first == NULL)
	{
		// make new vertex and assign value
		v = (Vertex*)malloc(sizeof(struct Vertex));
		// keep the next of old halfedge about to be split

		if(selectedEdges.end() == find(selectedEdges.begin(),selectedEdges.end(),he))
		{
			
			v->x = 3.0 / 8.0 * (edgeNeighbours[0]->x + edgeNeighbours[1]->x) + 1.0 / 8.0 * (edgeNeighbours[2]->x + edgeNeighbours[3]->x);
			v->y = 3.0 / 8.0 * (edgeNeighbours[0]->y + edgeNeighbours[1]->y) + 1.0 / 8.0 * (edgeNeighbours[2]->y + edgeNeighbours[3]->y);
			v->z = 3.0 / 8.0 * (edgeNeighbours[0]->z + edgeNeighbours[1]->z) + 1.0 / 8.0 * (edgeNeighbours[2]->z + edgeNeighbours[3]->z);
		}
		else
		{
			v->x = 0.5 * (edgeNeighbours[0]->x + edgeNeighbours[1]->x);
			v->y = 0.5 * (edgeNeighbours[0]->y + edgeNeighbours[1]->y);
			v->z = 0.5 * (edgeNeighbours[0]->z + edgeNeighbours[1]->z);
			tempSelectedPoints.push_back(v);
		}
        v->nx = -1;
        v->ny = -1;
        v->nz = -1;
		// add newly created vertex to list
		tempVertexList.push_back(v);
	}
	else
	// if the edge has already been split on the other side
	{
		// use existing vertex and set the pairs to the new half edges
		v = pairEdges.second->vertex;
		
		// set pairs for halfedges if edge has already been split
		pairEdges.first->pair = newHe2;
		newHe2->pair = pairEdges.first;

		pairEdges.second->pair = newHe1;
		newHe1->pair = pairEdges.second;
	}

	

	// link new halfedge to new edge vertex
	if (movedVertexVertices[he->vertex] != NULL)
	{
		// temp links on halfedges for things to work, will be overwritten later.
		newHe1->next = newHe2;
		newHe1->vertex = movedVertexVertices[he->vertex];

		newHe2->next = movedVertexVertices[tempNext->vertex]->halfEdge;
		newHe2->vertex = v;

		// set vertex to point at new half edge
		movedVertexVertices[he->vertex]->halfEdge = newHe1;
		v->halfEdge = newHe2;
	}
	else
	{
		cout << "something bad happened";
	}

	// add to new list
	tempHalfEdgeList.push_back(newHe1);
	tempHalfEdgeList.push_back(newHe2);
	
	splitHalfEdges[he] = make_pair(newHe1,newHe2);

	return v;
}

void DCEL::subdivideFace(Face* f)
{
	// split all edges in the face into edge verticies 
	HalfEdge* currentHe = f->halfEdge;

	Vertex* ev1 = newEdgeVertex(currentHe);
	// original vertex 1
	Vertex* v1 = movedVertexVertices[currentHe->vertex];
	currentHe = currentHe->next;

	Vertex* ev2 = newEdgeVertex(currentHe);
	// original vertex 2
	Vertex* v2 = movedVertexVertices[currentHe->vertex];
	currentHe = currentHe->next;

	Vertex* ev3 = newEdgeVertex(currentHe);
	// original vertex 3
	Vertex* v3 = movedVertexVertices[currentHe->vertex];
	currentHe = currentHe->next;

	// make edges point to each other at corners
	ev1->halfEdge->next = v2->halfEdge;
	ev2->halfEdge->next = v3->halfEdge;
	ev3->halfEdge->next = v1->halfEdge;


	// create new faces
	Face* newFace1 = (Face*)malloc(sizeof(struct Face));
	Face* newFace2 = (Face*)malloc(sizeof(struct Face));
	Face* newFace3 = (Face*)malloc(sizeof(struct Face));

	// create new half edges for the new face
	HalfEdge* newHe1 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
	HalfEdge* newHe2 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
	HalfEdge* newHe3 = (HalfEdge*)malloc(sizeof(struct HalfEdge));

	// link half edges together
	ev1->halfEdge->next->next = newHe1;
	newHe1->next = ev1->halfEdge;

	ev2->halfEdge->next->next = newHe2;
	newHe2->next = ev2->halfEdge;

	ev3->halfEdge->next->next = newHe3;
	newHe3->next = ev3->halfEdge;

	newHe1->vertex = ev2;// ev1->halfEdge->next->vertex;
	newHe2->vertex = ev3;//ev2->halfEdge->next->vertex;
	newHe3->vertex = ev1;//ev3->halfEdge->next->vertex;

	newFace1->halfEdge = newHe1;
	newFace2->halfEdge = newHe2;
	newFace3->halfEdge = newHe3;

	// set halfedges to new faces
	HalfEdge* he1 = newHe1;
	HalfEdge* he2 = newHe2;
	HalfEdge* he3 = newHe3;
	for (int i = 0; i < 3; i++)
	{
		he1->face = newFace1;
		he2->face = newFace2;
		he3->face = newFace3;

		he1 = he1->next;
		he2 = he2->next;
		he3 = he3->next;
	}


	Face* newFace4 = (Face*)malloc(sizeof(struct Face));

	HalfEdge* newHe4 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
	HalfEdge* newHe5 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
	HalfEdge* newHe6 = (HalfEdge*)malloc(sizeof(struct HalfEdge));

	newFace4->halfEdge = newHe4;

	// assign faces
	newHe4->face = newFace4;
	newHe5->face = newFace4;
	newHe6->face = newFace4;

	newHe4->next = newHe5;
	newHe5->next = newHe6;
	newHe6->next = newHe4;
	// assign pairs
	newHe4->pair = newHe1;
	newHe1->pair = newHe4;

	newHe5->pair = newHe2;
	newHe2->pair = newHe5;

	newHe6->pair = newHe3;
	newHe3->pair = newHe6;

	newHe4->vertex = newHe4->pair->next->vertex;
	newHe5->vertex = newHe5->pair->next->vertex;
	newHe6->vertex = newHe6->pair->next->vertex;


	// insert to facelist and edgelist
	tempFaceList.push_back(newFace1);
	tempFaceList.push_back(newFace2);
	tempFaceList.push_back(newFace3);
	tempFaceList.push_back(newFace4);

	tempHalfEdgeList.push_back(newHe1);
	tempHalfEdgeList.push_back(newHe2);
	tempHalfEdgeList.push_back(newHe3);
	tempHalfEdgeList.push_back(newHe4);
	tempHalfEdgeList.push_back(newHe5);
	tempHalfEdgeList.push_back(newHe6);

	// free mem


}

void DCEL::output()
{
	map<Vertex*, int> vertexNum;

	ofstream myfile("output.obj");
	if (myfile.is_open())
	{
		for (int i = 0; i < vertexList.size(); i++)
		{
			myfile << "v " << vertexList[i]->x << " " << vertexList[i]->y << " " << vertexList[i]->z << endl;
			vertexNum[vertexList[i]] = i + 1;
		}

		for (int i = 0; i < faceList.size(); i++)
		{
			int v1 = vertexNum[faceList[i]->halfEdge->vertex];
			int v2 = vertexNum[faceList[i]->halfEdge->next->vertex];
			int v3 = vertexNum[faceList[i]->halfEdge->next->next->vertex];
			myfile << "f " << v1 << " " << v2 << " " << v3 << endl;
		}
		cout << "output done" << endl;
		myfile.close();
	}
	else cout << "Unable to open file";
}

void DCEL::findIgnoreEdges(Vertex* v) 
{
	HalfEdge* e = v->halfEdge->pair;

	// last halfEdge to visit
	HalfEdge * endEdge = e;

	do
	{		
		// if edge is not already in selected edges
		if( selectedEdges.end() == find(selectedEdges.begin(),selectedEdges.end(),e))
		{	
			// if point is selected
			if(selectedPoints.end() != find(selectedPoints.begin(),selectedPoints.end(),e->vertex))
			{
				selectedEdges.push_back(e);
				selectedEdges.push_back(e->pair);
			}
		}
		e = e->next->pair;
	} while (e != endEdge);
}
