//
//  readFile.hpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef readFile_hpp
#define readFile_hpp

#include "stdafx.h"
#include "nodeInput.h"
#include "stiffnessMatrix.h"

class readFile {

public:
	int numberOfElements;
	int numberOfNodesGlobal;
	int numberOfConnections;
	double E; //modulus of elasticity
	double A; //area
	double L; //length


	readFile();
	~readFile();

	nodeInput* elements;
	nodeInput* conn;
	stiffnessMatrix* kelement;

	int interiorCounter;

	void readWorkingFile(const char* file);

	double** readWorkFile(const char* file);


};

#endif /* readFile_hpp */