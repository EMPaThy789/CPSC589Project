//
//  loopDiv.cpp
//  CPSC589Project
//
//  Created by Kiranpreet Bajwa on 2016-03-29.
//  Copyright © 2016 Kiranpreet Bajwa. All rights reserved.
//

#include "loopDiv.h"
#include "DCEL.h"
#include <math.h>

using namespace std;
#define PI 3.14159265

//Steps of subdividing

//1. Copy the vertices
    //In class he mentioned that we could potientially skip this step.

//2. Find the neighbours and alpha if dealing with extra-ordinary vertex
    //Ordinary vertex has valence 6 and alpha is 1/4 (from the notes)


float getAlpha(int valence){
    float cosTerm = (1/4) * cos( (2*PI/valence));
    float innerTerm = pow((3/8) + cosTerm, 2);
    float alpha = (1/6) * ((5/8) + innerTerm);
    return alpha;
}

Vertex newVert(Vertex oldVert, int n){
    
    float alpha = 0.0;
    Vertex vNew;
    vector <Vertex> neighbour = neighbours(oldVert);
    
    if(n > 6){
        alpha = getAlpha(n);
    } else {
        alpha = 1/4;
    }
    
    vNew.x = (1 - n * alpha) * oldVert.x;
    vNew.y = (1 - n * alpha) * oldVert.y;
    vNew.z = (1 - n * alpha) * oldVert.z;
    
    Vertex sum;
    
    for(int i=0; i< n; i++){
        
        sum.x = sum.x + neighbour[i].x;
        sum.x = sum.y + neighbour[i].y;
        sum.x = sum.z + neighbour[i].z;
    }
    
    sum.x = alpha * sum.x;
    sum.y = alpha * sum.y;
    sum.z = alpha * sum.z;
    
    vNew.x = vNew.x + sum.x;
    vNew.y = vNew.y + sum.y;
    vNew.z = vNew.z + sum.z;
    
    return vNew;
}

//3. For all edges, insert u (new vertex)

//4. For all faces, find the new and old vertices, add the new faces to f' (?), add the new edges to vi
//and add the old vertices to the edges.