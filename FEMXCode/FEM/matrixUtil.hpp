//
//  matrixUtil.hpp
//  FEM
//
//  Created by Diego Andrade on 9/4/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#ifndef matrixUtil_hpp
#define matrixUtil_hpp

#include "Common.h"

class matrixUtil
{

protected:
    int nRow,nColumn;
    mutable matrixUtil *tmp; // To keep temporary matrix
    
private:
    double ** M;
    double *dat;

    
public:
    matrixUtil();
    matrixUtil(const matrixUtil &from);
    ~matrixUtil();
    
    inline int nr(void) const
    {
        return nRow;
    }
    inline int nc(void) const
    {
        return nColumn;
    }
    
    inline const double &v(int row,int column) const;
    void Create(int nr,int nc);
    void Create(int nr,int nc,const double *d);
    void CreateWithoutClear(int nr,int nc);
    
    double** MX;
    
    matrixUtil(int row, int col);
    matrixUtil(int n);
    
    double** sumMatrix(double** A, double** B, int n);
    
    matrixUtil friend operator +(matrixUtil,matrixUtil); //EXTRA POINTS
    
    inline FEMRESULT Set(int row,int column,const double &v);
    
    int m,n;
    
    // For Internal Use
    matrixUtil *UseTemporaryMatrix(void) const;
    
    
    //Jacobi Rotations Solver
    
};

inline const matrixUtil &operator+(const matrixUtil &a,const matrixUtil &b)
{
    matrixUtil *tmp;
    
    if(a.nc()!=b.nc() || a.nr()!=b.nr())
    {
        printf("Warning : Invalid Matrix Summation.\n");
    }
    
    tmp=a.UseTemporaryMatrix();
    tmp->CreateWithoutClear(a.nr(),b.nc());
    
    int r,c;
    for(r=1; r<=a.nr(); r++)
    {
        for(c=1; c<=b.nc(); c++)
        {
            tmp->Set(r,c,a.v(r,c)+b.v(r,c));
        }
    }
    
    return *tmp;
}

inline FEMRESULT matrixUtil::Set(int row,int column,const double &a)
{
    if(1<=row && row<=nRow && 1<=column && column<=nColumn)
    {
        dat[(row-1)*nColumn+(column-1)]=a;
        return FEMOK;
    }
    else
    {
        return FEMERR;
    }
}

inline const double &matrixUtil::v(int row,int column) const
{
    if(1<=row && row<=nRow && 1<=column && column<=nColumn)
    {
        return dat[(row-1)*nColumn+(column-1)];
    }
    else
    {
        cout << " matrixUtil::v()\n";
        cout << "  Index out of range.  (Note : Row/Column begins with 1\n";
        return dat[0];
    }
}

#endif /* matrixUtil_hpp */
