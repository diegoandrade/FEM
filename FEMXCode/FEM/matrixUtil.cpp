//
//  matrixUtil.cpp
//  FEM
//
//  Created by Diego Andrade on 9/4/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "matrixUtil.hpp"

matrixUtil::matrixUtil()
{
    nRow=0;
    nColumn=0;
    tmp=NULL;
}

matrixUtil::~matrixUtil()
{
   /*if(tmp!=NULL)
    {
        delete tmp;
    }
    if(dat!=NULL)
    {
        delete [] dat;
        dat=NULL;
    }
    */
}

matrixUtil::matrixUtil(const matrixUtil &from)
{
    *this=from;
}

matrixUtil::matrixUtil(int row, int col)
{
    m = row;
    n = col;
}

void matrixUtil::CreateWithoutClear(int nr, int nc)
{
    if(dat==NULL || nRow!=nr || nColumn!=nc)
    {
        if(dat!=NULL)
        {
            delete [] dat;
            
        }
        nRow=nr;
        nColumn=nc;
        dat=new double[nc*nr];
    }
}

void matrixUtil::Create(int nr,int nc)
{
    CreateWithoutClear(nr,nc);
    for(int i=0; i<nc*nr; i++)
    {
        dat[i]=0.0;
    }
}

void matrixUtil::Create(int nr,int nc,const double *d)
{
    CreateWithoutClear(nr,nc);
    for(int i=0; i<nr*nc; i++)
    {
        dat[i]=d[i];
    }
}

double** matrixUtil::sumMatrix(double **A, double **B, int n)
{
   
    
    double** K = new double*[n];
    for (int i=0; i<n ; i++)
    {
        K[i]=new double[n];
    }
    
    for (int i=0;i<n; i++)
    {
        for(int j=0;j<n;j++)
        {
            K[i][j] = A[i][j]+B[i][j];
        }
    }
    
    return K;
}

/*matrixUtil operator +(matrixUtil A, matrixUtil B)
{
    
    matrixUtil T;
    for (int i=0;i<4; i++)
    {
        for(int j=0;j<4;j++)
        {
            T.MX[i][j]=0.0;
            //T.MX[i][j]+(A.MX[i][j]+B.MX[i][j]);
        }
    }
    
    
    return T;
    
}
*/
