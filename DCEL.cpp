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
					v->nx = var3;
					v->ny = var3;
					v->nz = var3;
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
					vertexList.push_back(v);
				}
			}
			
			

			map <pair<unsigned int, unsigned int>, HalfEdge*> Edges;
						
			// assumption is made that mesh is entirely triagular
			if (var1[0] == 'f')
			{
				Face* f = (Face*)malloc(sizeof(struct Face));
				HalfEdge* he1 = (HalfEdge*)malloc(sizeof(struct HalfEdge));
				HalfEdge* he2 = (HalfEdge*)malloc(sizeof(struct HalfEdge));;
				HalfEdge* he3 = (HalfEdge*)malloc(sizeof(struct HalfEdge));;

				Vertex* v1 = vertexList.at(var2 - 1);
				Vertex* v2 = vertexList.at(var3 - 1);
				Vertex* v3 = vertexList.at(var4 - 1);

				HalfEdge* he[3];

				

				he1->next = he2;
				he2->next = he3;
				he3->next = he1;

				he1->face = f;
				he2->face = f;
				he3->face = f;

				he1->vertex = v1;
				he2->vertex = v2;
				he3->vertex = v3;

				if (Edges[make_pair(var2, var3)] == NULL)
					Edges[make_pair(var2, var3)] = he1;
				else
					he1->pair = Edges[make_pair(var2, var3)];

				if (Edges[make_pair(var3, var4)] == NULL)
					Edges[make_pair(var3, var4)] = he2;
				else
					he2->pair = Edges[make_pair(var3, var4)];

				if (Edges[make_pair(var4, var2)] == NULL)
					Edges[make_pair(var4, var2)] = he3;
				else
					he3->pair = Edges[make_pair(var4, var2)];

				f->halfEdge = he1;
				faceList.push_back(f);
				halfEdgeList.push_back(he1);
				halfEdgeList.push_back(he2);
				halfEdgeList.push_back(he3);
			}
			cout << var1 << var2 << var3 << var4 << "\n";
		}
		file.close();
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

		glColor3f(1.0f, 0.0f, 0.0f);     // red
		glNormal3f(v[0]->nx, v[0]->ny, v[0]->nz);
		glVertex3f(v[0]->x, v[0]->y, v[0]->z);
		glNormal3f(v[1]->nx, v[1]->ny, v[1]->nz);
		glVertex3f(v[1]->x, v[1]->y, v[1]->z);
		glNormal3f(v[2]->nx, v[2]->ny, v[2]->nz);
		glVertex3f(v[2]->x, v[2]->y, v[2]->z);


	}
	glEnd();
}
