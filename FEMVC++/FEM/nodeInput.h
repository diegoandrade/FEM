#pragma once
//
//  nodeInput.hpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef nodeInput_hpp
#define nodeInput_hpp


#include "stdafx.h"

class nodeInput
{

public:
	double ux, uy;
	double l;
	double fx, fy;
	int na, nb;
	int idx;
	double ang;

	int c1, c2, c3, c4;

public:

	nodeInput();
	~nodeInput();
	nodeInput(int INDEX, int NA, int NB, double L, double FX, double FY, double ANG);
	// index, node A side, node B side, displacement in x, displacement in y, forces in x, forces in y, angle degrees

	nodeInput(int C1, int C2, int C3, int C4);
	//Connectivity 1,2,3,4
	int findBiggestElement(nodeInput A);
};


#endif /* nodeInput_hpp */
