//
//  readFile.cpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "readFile.hpp"

using namespace std;



readFile::readFile()
{
    
}

readFile::~readFile()
{
    
}

void readFile::read()
{
    string line;
    ifstream myfile ("/Users/diegoandrade/Desktop/FEM/workingFile.FEMUSF");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
}
