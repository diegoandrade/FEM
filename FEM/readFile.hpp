//
//  readFile.hpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef readFile_hpp
#define readFile_hpp

#include "Common.h"
#include "nodeInput.hpp"
#include "stiffnessMatrix.hpp"

class readFile{
    
public:
    int numberOfElements;
    int numberOfNodes;
    int numberOfConnections;
    double E; //modulus of elasticity
    double A; //area

    
    readFile();
    ~readFile();
    
    nodeInput* nodes;
    nodeInput* conn;
    stiffnessMatrix* kelement;
    
    int interiorCounter;
    
    void readWorkingFile(const char* file);
    


};

#endif /* readFile_hpp */
