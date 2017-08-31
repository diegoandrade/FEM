//
//  readFile.hpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef readFile_hpp
#define readFile_hpp

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

class readFile{
protected:
    int numberOfElements;
    int numberOfNodes;
    int numberOfConnections;
    double E; //modulus of elasticity
    double A; //area
    
public:
    
    readFile();
    ~readFile();
    
    void read();


};

#endif /* readFile_hpp */
