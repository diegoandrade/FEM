//
//  Common.h
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef Common_h
#define Common_h

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

//use to sort arrays
#include <set>

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG

using namespace std;

#define PI 4*atan(1)

typedef struct {
    float x, y, z;
} point_t; // Point3d, Vector3d;

//This is the node data structure
struct node {
    
    int idx; //unique id
    
    int C1; //connectivity
    int C2;
    int C3;
    int C4;
    
    float x; //position in the real space
    float y; //position in the real space
    
};

#endif /* Common_h */
