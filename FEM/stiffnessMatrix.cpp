//
//  stiffnessMatrix.cpp
//  FEM
//
//  Created by Diego Andrade on 9/2/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "stiffnessMatrix.hpp"

stiffnessMatrix::stiffnessMatrix()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            kElement[i][j]=0.0;
        }
    }
}

stiffnessMatrix::~stiffnessMatrix()
{
    
}

void stiffnessMatrix::elementStiffnessMatrix(double A, double L, double E, double ang)
{
    
    kElement[0][0] = pow(cos(ang),2);
    kElement[0][1] = sin(ang)*cos(ang);
    kElement[0][2] = - pow(cos(ang),2);
    kElement[0][3] = - sin(ang)*cos(ang);
   
    kElement[1][0] = sin(ang)*cos(ang);
    kElement[1][1] = pow(sin(ang),2);
    kElement[1][2] = - sin(ang)*cos(ang);
    kElement[1][3] = - pow(sin(ang),2);

    kElement[2][0] = - pow(cos(ang),2);
    kElement[2][1] = - sin(ang)*cos(ang);
    kElement[2][2] = pow(cos(ang),2);
    kElement[2][3] = sin(ang)*cos(ang);
    
    kElement[3][0] = - sin(ang)*cos(ang);
    kElement[3][1] = - pow(sin(ang),2);
    kElement[3][2] = sin(ang)*cos(ang);
    kElement[3][3] = pow(sin(ang),2);
 
}

void stiffnessMatrix::Set(int row,int column,const double &a)
{
    int nColumnvar = 3;
    int nRowvar = 3;
    
    if(1<=row && row<=nRowvar && 1<=column && column<=nColumnvar)
    {
        dat[(row-1)*nColumnvar+(column-1)]=a;
        cout << " isOK\n" << endl;
    }
    else
    {
        cout << " matrix3x3::Set()\n" << endl;
        cout << " There is an Error\n" << endl;
    }
}

void stiffnessMatrix::SetMtx(int row,int column,const double &a)
{
    kElement[row][column] = a;
}

void stiffnessMatrix::printMtrx(string name)
{
    cout << "\n-- Stiffness Matrix K for Element[" << name << "]\n";

    for(int i = 0 ; i< 4; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            cout << "k[" << i << "][" << j << "]:\t" << kElement[i][j] << "\t" ;
        }
        cout << endl;
    }
    
}

void stiffnessMatrix::printMtrx(double Mx[4][4], char* name)
{
    for(int i = 0 ; i< 4; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            cout << name <<"[" << i << "][" << j << "]:\t" << Mx[i][j] << "\t" ;
        }
        cout << endl;
    }
    
}


void stiffnessMatrix::printMtrx(double** Mx,int n, char* name)
{
    for(int i = 0 ; i< n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            cout << name <<"[" << i << "][" << j << "]:\t" << Mx[i][j] << "\t" ;
        }
        cout << endl;
    }
    
}

void stiffnessMatrix::globalMatrix(int numberOfNodes, stiffnessMatrix k, nodeInput conn)
{
    int rows, cols;
    rows=cols=numberOfNodes;
    
    //const size_t n = numberOfNodes;

    //Allocate a two dimmensional array of doubles
    double** marray = new double*[numberOfNodes*numberOfNodes];
    for (int i=0; i<numberOfNodes*numberOfNodes ; i++)
    {
        marray[i]=new double[numberOfNodes*numberOfNodes];
    }
    
    
    //Fill the array
    for (int i=0; i<numberOfNodes*numberOfNodes ; i++)
    {
        for (int j=0;j<numberOfNodes*numberOfNodes; j++)
        {
            marray[i][j]= i;
        }
    }
    
    //Fill the GLOBAL ARRAY
    for (int i=0; i<numberOfNodes ; i++)
    {
        for (int j=0;j<numberOfNodes; j++)
        {
            marray[conn.c1][conn.c1] = k.kElement[0][0];
            marray[conn.c1][conn.c2] = k.kElement[0][1];
            marray[conn.c1][conn.c3] = k.kElement[0][2];
            marray[conn.c1][conn.c4] = k.kElement[0][3];
            
            marray[conn.c2][conn.c1] = k.kElement[1][0];
            marray[conn.c2][conn.c2] = k.kElement[1][1];
            marray[conn.c2][conn.c3] = k.kElement[1][2];
            marray[conn.c2][conn.c4] = k.kElement[1][3];
            
            marray[conn.c3][conn.c1] = k.kElement[2][0];
            marray[conn.c3][conn.c2] = k.kElement[2][1];
            marray[conn.c3][conn.c3] = k.kElement[2][2];
            marray[conn.c3][conn.c4] = k.kElement[2][3];
            
            marray[conn.c4][conn.c1] = k.kElement[3][0];
            marray[conn.c4][conn.c2] = k.kElement[3][1];
            marray[conn.c4][conn.c3] = k.kElement[3][2];
            marray[conn.c4][conn.c4] = k.kElement[3][3];
            
        }
    }
    
    GLOBAL_K = marray;

    //output the array
    for (int i=0; i<numberOfNodes*numberOfNodes ; i++)
    {
        for (int j=0;j<numberOfNodes*numberOfNodes; j++)
        {
            cout << marray[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //deallocate memory
    for(int i=0;i<numberOfNodes;i++)
    {
        delete[] marray[i];
    }
    delete [] marray;
    
}

