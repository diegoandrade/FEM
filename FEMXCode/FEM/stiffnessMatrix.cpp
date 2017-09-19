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
    double k = double(A*E)/L ;
    
    double nang = ang;
    //nang = gradToRad(ang);
    
    kElement[0][0] = k* pow(cos(nang),2);
    kElement[0][1] = k* sin(nang)*cos(nang);
    kElement[0][2] = k* (- pow(cos(nang),2));
    kElement[0][3] = k* (- sin(nang)*cos(nang));
   
    kElement[1][0] = k* (sin(nang)*cos(nang));
    kElement[1][1] = k* (pow(sin(nang),2));
    kElement[1][2] = k* (- sin(nang)*cos(nang));
    kElement[1][3] = k* (- pow(sin(nang),2));

    kElement[2][0] = k* (- pow(cos(nang),2));
    kElement[2][1] = k* (- sin(nang)*cos(nang));
    kElement[2][2] = k* (pow(cos(nang),2));
    kElement[2][3] = k* (sin(nang)*cos(nang));
    
    kElement[3][0] = k* (- sin(nang)*cos(nang));
    kElement[3][1] = k* (- pow(sin(nang),2));
    kElement[3][2] = k* (sin(nang)*cos(nang));
    kElement[3][3] = k* (pow(sin(nang),2));
    
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            if (kElement[i][j]<0.0000000001 && kElement[i][j]>=0 ){kElement[i][j]=0.0;}
            else if (kElement[i][j]>-0.0000000001 && kElement[i][j]<=0) kElement[i][j]=0.0;
            
            
        }
    }
    
 
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
            cout << "|  k[" << i << "][" << j << "]: " << setw(8) << kElement[i][j] << "|";
            //cout << "k[" << i << "][" << j << "]:\t" << kElement[i][j] << "\t" ;
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

double stiffnessMatrix::gradToRad(double ang)
{
    double temp = 0;
    
    temp = ang * PI/180;
    
    return temp;
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
            marray[i][j]= 0;
        }
    }
    
    //Fill the GLOBAL ARRAY
    for (int i=0; i<numberOfNodes ; i++)
    {
        for (int j=0;j<numberOfNodes; j++)
        {
            marray[conn.c1-1][conn.c1-1] = k.kElement[0][0]; // -1 because for loop starts from zero and the problem description
            marray[conn.c1-1][conn.c2-1] = k.kElement[0][1];
            marray[conn.c1-1][conn.c3-1] = k.kElement[0][2];
            marray[conn.c1-1][conn.c4-1] = k.kElement[0][3];
            
            marray[conn.c2-1][conn.c1-1] = k.kElement[1][0];
            marray[conn.c2-1][conn.c2-1] = k.kElement[1][1];
            marray[conn.c2-1][conn.c3-1] = k.kElement[1][2];
            marray[conn.c2-1][conn.c4-1] = k.kElement[1][3];
            
            marray[conn.c3-1][conn.c1-1] = k.kElement[2][0];
            marray[conn.c3-1][conn.c2-1] = k.kElement[2][1];
            marray[conn.c3-1][conn.c3-1] = k.kElement[2][2];
            marray[conn.c3-1][conn.c4-1] = k.kElement[2][3];
            
            marray[conn.c4-1][conn.c1-1] = k.kElement[3][0];
            marray[conn.c4-1][conn.c2-1] = k.kElement[3][1];
            marray[conn.c4-1][conn.c3-1] = k.kElement[3][2];
            marray[conn.c4-1][conn.c4-1] = k.kElement[3][3];
            
        }
    }
    
    GLOBAL_K = marray;

    //output the array
    /*for (int i=0; i<numberOfNodes*numberOfNodes ; i++)
    {
        for (int j=0;j<numberOfNodes*numberOfNodes; j++)
        {
            cout << marray[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
    
    //deallocate memory
    /*for(int i=0;i<numberOfNodes;i++)
    {
        delete[] marray[i];
    }
    delete [] marray;*/
    
}

