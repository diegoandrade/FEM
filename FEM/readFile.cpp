//
//  readFile.cpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "readFile.hpp"

readFile::readFile()
{
    numberOfNodes = 0; //maximum number of nodesmo
   
}
readFile::~readFile()
{
    
}

void readFile::readWorkingFile(const char* file)
{
    nodes = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number of nodes in this implementation
    conn = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number connectivity (WRONG!)
    
    int nodeCounter = 0;
    int connectivityCounter = 0;

    
    string tempvalue = "";
    std::string::size_type sz;

    
    try
    {
        string line;
        string str = "/Users/diegoandrade/Dropbox/USF/2017/FEM/FEM/";
        str.append(file);

        
        ifstream myfile (str);
        
        if (myfile.is_open())
        {
            bool foundE = false;
            bool foundEND = false;
            bool foundA = false;
            bool foundL = false;
            bool foundN = false;

            while ( getline (myfile,line) && foundEND == false)
            {
                istringstream iss(line);
                
                vector<string> tokens;
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter(tokens));
                
                
                if (tokens[0] ==  "GEOMETRIC")
                {
                    cout << "FOUND GEOMETRIC PROPERTIES" << '\n';
                    
                }
                else if (tokens[0] ==  "NODE")
                {
                    cout << "FOUND NODE DESCRIPTION" << '\n';
                    
                }
                else if (tokens[0] == "N" && foundL == false) //because connectivity happens later
                {
                    cout << "FOUND N" << '\n';
                    
                    foundN = true;
                    
                    tempvalue = tokens[1];
                    nodes[nodeCounter].idx = stoi(tempvalue, &sz);
                    tempvalue = tokens[2];
                    nodes[nodeCounter].na = stoi(tempvalue, &sz);
                    tempvalue = tokens[3];
                    nodes[nodeCounter].nb = stoi(tempvalue, &sz);
                    tempvalue = tokens[4];
                    nodes[nodeCounter].ux = stod(tempvalue, &sz);
                    tempvalue = tokens[5];
                    nodes[nodeCounter].uy = stod(tempvalue, &sz);
                    tempvalue = tokens[6];
                    nodes[nodeCounter].fx = stod(tempvalue, &sz);
                    tempvalue = tokens[7];
                    nodes[nodeCounter].fy = stod(tempvalue, &sz);
                    tempvalue = tokens[8];
                    nodes[nodeCounter].ang = stod(tempvalue, &sz);

                    
                    nodeCounter++;
                }

                else if (tokens[0] == "A")
                {
                    cout << "FOUND A" << '\n';
                    tempvalue = tokens[1];
                    A = stod(tempvalue, &sz);
                    foundA = true;
                }
                else if (tokens[0] == "E" )
                {
                    D( cout << "FOUND E" << '\n'; )
                    cout << "FOUND E" << '\n';
                    tempvalue = tokens[1];
                    A = stod(tempvalue, &sz);
                    foundE = true;
                }
                else if (tokens[0] == "L" && foundN==true)
                {
                    D( cout << "FOUND L" << '\n'; )
                    cout << "FOUND L" << '\n';
                    
                    tempvalue = tokens[1];
                    conn[connectivityCounter].c1 = stoi(tempvalue, &sz);
                    tempvalue = tokens[2];
                    conn[connectivityCounter].c2 = stoi(tempvalue, &sz);
                    tempvalue = tokens[3];
                    conn[connectivityCounter].c3 = stoi(tempvalue, &sz);
                    tempvalue = tokens[4];
                    conn[connectivityCounter].c4 = stoi(tempvalue, &sz);
                    
                    connectivityCounter++;
              
                    
                }
                else if (tokens[0] == "END" )
                {
                    foundEND = true;
                }
                
            }
            myfile.close();
            
            
        }
        
        else cout << "Unable to open file" <<  endl;
        
        numberOfNodes = nodeCounter;
        
        kelement = (stiffnessMatrix *) malloc(numberOfNodes*sizeof(stiffnessMatrix)); //creates a vector of elements k from class stiffnessMatrix
        
        stiffnessMatrix globalMatrix; //creates an object from class stiffnessMatrix
        
        kelement[0].elementStiffnessMatrix(A, 1, E, nodes[0].ang);
        kelement[1].elementStiffnessMatrix(A, 1, E, nodes[1].ang);
        kelement[2].elementStiffnessMatrix(A, 1, E, nodes[2].ang);
        kelement[3].elementStiffnessMatrix(A, 1, E, nodes[3].ang);
        
       
        kelement[0].printMtrx(to_string(0));
        kelement[1].printMtrx(to_string(1));
        kelement[2].printMtrx(to_string(2));
        kelement[3].printMtrx(to_string(3));

        globalMatrix.globalMatrix(numberOfNodes, kelement[3], conn[3]);
        
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
}
