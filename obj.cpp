//
//  obj.cpp
//  CPSC589Project
//
//  Created by Kiranpreet Bajwa on 2016-03-15.
//  Copyright © 2016 Kiranpreet Bajwa. All rights reserved.
//

#include "obj.h"

using namespace std;

Obj::Obj(string filename){
    ifstream file;
    
    file.open(filename);
    
    if(!file.is_open()){
        cout << "Error could not open file" << endl;
    } else {
        //parse the vertices and faces
    
        file.close();
    }
}