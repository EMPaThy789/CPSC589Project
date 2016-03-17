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
#include <fstream>

using namespace std;

// Forward declaration

// Class for parsing the object file
class Obj
{
public:
    // ## Constructor ##
    
    // ## Variables ##

    // ## Functions ##
    Obj(string Filename);
    
    
protected:
    // ## Variables ##
    vector < vector< vector<int> > > vertex;        //Keeps track of the vertices of the object
    vector < vector< vector<int> > > face;          //Keeps track of the faces of the object

    
    // ## Functions ##
    
};


#endif /* obj_hpp */
