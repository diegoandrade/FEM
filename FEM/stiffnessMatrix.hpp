//
//  stiffnessMatrix.hpp
//  FEM
//
//  Created by Diego Andrade on 9/2/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef stiffnessMatrix_hpp
#define stiffnessMatrix_hpp

#include "Common.h"
#include "nodeInput.hpp"

// For now everything is in-lbf

class stiffnessMatrix
{
    
protected:
    
    double nRow,nColumn;
    
    double dat[9];
    
public:
    
    
    double A;
    double E;
    double L;
    
    double kElement[4][4];
    double** GLOBAL_K;
    
    stiffnessMatrix** globalStiffnessMatrix;
    
    nodeInput* connectivity;
    
    stiffnessMatrix();
    ~stiffnessMatrix();
    
    inline stiffnessMatrix(double n, double m) {
        nRow=n;
        nColumn=m;
    }
    
    inline stiffnessMatrix(double sq) {
        nRow=sq;
        nColumn=sq;
    }

    void elementStiffnessMatrix (double A, double L, double E, double ang);
    
    void Set(int row,int column,const double &a);
    
    void SetMtx(int row,int column,const double &a);
    
    void printMtrx (string name);
    
    void printMtrx (double Mx[4][4], char * name);
    
    void printMtrx (double** Mx, int n,  char* name);
    
    void globalMatrix(int numberOfNodes, stiffnessMatrix kelement, nodeInput conn);

    //double gradToRad (double ang);
    
    
};



#endif /* stiffnessMatrix_hpp */
