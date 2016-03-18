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
    
    //cout << getcwd(NULL, 0);
    
    if(!file.is_open()){
        cout << "Error could not open file" << endl;
    } else {
        //parse the vertices and faces
        
        string line;
        
        while(!file.eof()){
            //file >> word;
             //getline(file, line);
            string var1;
            double var2, var3, var4;
            file >> var1 >> var2 >> var3 >> var4;
            
            if(var1.find('v') != string::npos){
                vertexX.push_back(var2);
                vertexY.push_back(var3);
                vertexZ.push_back(var4);
            }

            if(var1.find('f') != string::npos){
                face1.push_back(var2);
                face2.push_back(var3);
                face3.push_back(var4);
            }

            //cout << var1 << var2 << var3 << var4;
            
        }
        
        file.close();
    }
}