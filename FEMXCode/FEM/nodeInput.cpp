//
//  nodeInput.cpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "nodeInput.hpp"

nodeInput::nodeInput()
{
    
}

nodeInput::~nodeInput()
{
    
}

nodeInput:: nodeInput(int INDEX, int NA, int NB, double L, double FX, double FY, double ANG)
{
    this->idx = INDEX;
    this->na = NA;
    this->nb = NB;
    this->l = L;
    this->fx = FX;
    this->fy = FY;
    this->ang = ANG;
}

nodeInput::nodeInput(int C1, int C2, int C3, int C4)
{
    this->c1 = C1;
    this->c2 = C2;
    this->c3 = C3;
    this->c4 = C4;

}

int nodeInput::findBiggestElement(nodeInput A)
{
    int temp =0;
    
    if (A.na<A.nb)
        temp=A.nb;
    else temp=A.na;
    
    return temp;
}
