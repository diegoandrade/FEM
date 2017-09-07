// FEM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "readFile.h"
#include "stiffnessMatrix.h"

readFile read;
stiffnessMatrix kElement;

int main(int argc, const char * argv[]) {

	printf("----------------------------\n");       // you can use printf
	cout << "Welcome to FEM - USF : 2017\n";        // or you also can use cout
	cout << ("----------------------------\n\n\n");

	cout << "\n   Loading File...... \n\n\n\n";
	read.readWorkingFile("workingFile.FEMUSF");

	//Just shows the number of nodes from variable numberOfNodesGlobal on callss readFile
	int numberOfNodes = read.numberOfNodesGlobal;
	printf("Number of Nodes = %d\n", numberOfNodes);

	return 0;
}