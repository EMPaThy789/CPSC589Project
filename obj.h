//
//  obj.hpp
//  CPSC589Project
//
//  Created by Kiranpreet Bajwa on 2016-03-15.
//  Copyright © 2016 Kiranpreet Bajwa. All rights reserved.
//

#ifndef obj_h
#define obj_h

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

// Forward declaration

// Class for one half edge
class HalfEdge
{
public:
    // ## Constructor ##
    
    // ## Variables ##

    // ## Functions ##
    
    
    
protected:
    // ## Variables ##
    vector < vector< vector<int> > > vertex;        //Keeps track of the vertices of the object
    vector < vector< vector<int> > > face;          //Keeps track of the faces of the object

    
    // ## Functions ##
    
};


#endif /* obj_hpp */
