//
//  main.cpp
//  FEM
//  Solver v0.01
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//


#include "readFile.hpp"
#include "stiffnessMatrix.hpp"

readFile read;
stiffnessMatrix kElement;



int main(int argc, const char * argv[]) {
   
    
    printf("argc = %d\n",argc);
    printf("Let's see what is in argv[]\n");
    
   // if (argv[0] == "-t")
   // {
   //     std::cout << "\nThis is a Truss\n";
   // }
    
    read.readWorkingFile("workingFile.FEMUSF");
    
    // Initialize kElement Matrix
    double ke[4][4];
    
    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            ke[i][j]=0.0;
        }
    }
    
    int numberOfNodes = read.numberOfNodes;
    printf("Number of Nodes = %d\n",numberOfNodes);
    
    
    
    
    
    /*for (i=0;i<argc; i++)
    {
        printf("argv[%d] = %s", i , argv[i]);
    }*/
    
    
  
    
    return 0;
}
