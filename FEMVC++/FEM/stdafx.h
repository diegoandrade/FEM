// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <tchar.h>
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
#include <iomanip>
#include <cstdlib>



#include "FEMdef.h"

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




// TODO: reference additional headers your program requires here
