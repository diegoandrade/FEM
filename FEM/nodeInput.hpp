//
//  nodeInput.hpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef nodeInput_hpp
#define nodeInput_hpp


#include "Common.h"

class nodeInput
{
    
public:
    double ux , uy;
    double fx, fy;
    int na, nb;
    int idx;
    double ang;
    
    int c1, c2, c3, c4;
    
public:
    
    nodeInput();
    ~nodeInput();
    nodeInput(int INDEX, int NA, int NB, double UX, double UY, double FX, double FY, double ANG);
    // index, node A side, node B side, displacement in x, displacement in y, forces in x, forces in y, angle degrees
    
    nodeInput(int C1, int C2, int C3, int C4);
    //Connectivity 1,2,3,4
    
};


#endif /* nodeInput_hpp */
