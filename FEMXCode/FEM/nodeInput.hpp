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
    double l;
    double fx, fy; //forces
    int na, nb;
    int idx;
    double ang; //angle
    int c1, c2, c3, c4; //connectivity
    
public:
    
    nodeInput();
    ~nodeInput();
   
    // Index, node A side, node B side, displacement in x, displacement in y, forces in x, forces in y, angle degrees
    nodeInput(int INDEX, int NA, int NB, double L, double FX, double FY, double ANG);
    
    // Force Vector Definition
    nodeInput(double FX, double FY);
    
    // Connectivity 1,2,3,4
    nodeInput(int C1, int C2, int C3, int C4);
    
    int findBiggestElement(nodeInput A);
};


#endif /* nodeInput_hpp */
