//
//  readFile.cpp
//  FEM
//
//  Created by Diego Andrade on 8/31/17.
//  Copyright © 2017 Diego Andrade. All rights reserved.
//

#include "readFile.hpp"
#include "matrixUtil.hpp"

readFile::readFile()
{
    numberOfNodesGlobal = 0; //maximum number of nodesmo
   
}
readFile::~readFile()
{
    
}

void readFile::readWorkingFile(const char* file)
{
    elements = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number of nodes in this implementation
    conn = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number connectivity (WRONG!)
    
   
    int elementCounter = 0;
    int connectivityCounter = 0;
    
    int numberOfNodes=0;

    
    string tempvalue = "";
    std::string::size_type sz;

    
    try
    {
        string line;
        string str = "/Users/diegoandrade/Dropbox/USF/2017/FEM/FEM/";  //change here for your local folder
        str.append(file);

        
        ifstream myfile (str);
        
        if (myfile.is_open())
        {
            //FLAGS
            bool foundE = false;
            bool foundEND = false;
            bool foundA = false;
            bool foundL = false;
            bool foundN = false;
            bool foundC = false;

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
                else if (tokens[0] ==  "ELEMENTS")
                {
                    cout << "FOUND ELEMENTS DESCRIPTION" << '\n';
                    
                }
                else if (tokens[0] == "N" && foundC == false) //because connectivity happens later
                {
                    cout << "FOUND N" << '\n';
                    
                    foundN = true;
                    
                    //extract the information and pases it to class nodes
                    tempvalue = tokens[1];
                    elements[elementCounter].idx = stoi(tempvalue, &sz);
                    tempvalue = tokens[2];
                    elements[elementCounter].na = stoi(tempvalue, &sz);
                    tempvalue = tokens[3];
                    elements[elementCounter].nb = stoi(tempvalue, &sz);
                    tempvalue = tokens[4];
                    elements[elementCounter].l = stod(tempvalue, &sz);
                    tempvalue = tokens[5];
                    elements[elementCounter].fx = stod(tempvalue, &sz);
                    tempvalue = tokens[6];
                    elements[elementCounter].fy = stod(tempvalue, &sz);
                    tempvalue = tokens[7];
                    elements[elementCounter].ang = stod(tempvalue, &sz);
                    
                    //Find the biggest element on the working file -> gives the number of nodes for calculation
                    numberOfNodes = elements->findBiggestElement(elements[elementCounter]);
                    
                    elementCounter++;
                }

                else if (tokens[0] == "A")
                {
                    cout << "FOUND Area" << '\n';
                    tempvalue = tokens[1];
                    A = stod(tempvalue, &sz);
                    foundA = true;
                }
                else if (tokens[0] == "E" )
                {
                    D( cout << "FOUND E" << '\n'; )
                    cout << "FOUND Elasticity Modulus" << '\n';
                    tempvalue = tokens[1];
                    E = stod(tempvalue, &sz);
                    foundE = true;
                }
                else if (tokens[0] == "L" )
                {
                    D( cout << "FOUND L" << '\n'; )
                    cout << "FOUND Length" << '\n';
                    tempvalue = tokens[1];
                    L = stod(tempvalue, &sz);
                    foundL = true;
                }

                else if (tokens[0] == "C" && foundN==true)
                {
                    D( cout << "FOUND C" << '\n'; )
                    cout << "FOUND C" << '\n';
                    
                    //extract the information and pases it to class nodes -> connectivity
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
        
        numberOfNodesGlobal = 2*numberOfNodes; //because we have 2 degrees of freedom per node CHANGE HERE
        
        kelement = (stiffnessMatrix *) malloc(numberOfNodesGlobal*sizeof(stiffnessMatrix)); //creates a vector of elements k from class stiffnessMatrix
        
        stiffnessMatrix globalMatrix; //creates an object from class stiffnessMatrix
        
        kelement[0].elementStiffnessMatrix(A, elements[0].l, E, elements[0].ang);
        kelement[0].printMtrx(to_string(0+1));

        kelement[1].elementStiffnessMatrix(A, elements[1].l, E, elements[1].ang);
        kelement[1].printMtrx(to_string(1+1));
        
        kelement[2].elementStiffnessMatrix(A, elements[2].l, E, elements[2].ang);
        kelement[2].printMtrx(to_string(2+1));
        
        kelement[3].elementStiffnessMatrix(A, elements[3].l, E, elements[3].ang);
        kelement[3].printMtrx(to_string(3+1));
        
        kelement[4].elementStiffnessMatrix(A, elements[4].l, E, elements[4].ang);
        kelement[4].printMtrx(to_string(4+1));
        
        kelement[5].elementStiffnessMatrix(A, elements[5].l, E, elements[5].ang);
        kelement[5].printMtrx(to_string(5+1));
        
        kelement[6].elementStiffnessMatrix(A, elements[6].l, E, elements[6].ang);
        kelement[6].printMtrx(to_string(6+1));
        
        kelement[7].elementStiffnessMatrix(A, elements[7].l, E, elements[7].ang);
        kelement[7].printMtrx(to_string(7+1));
        
        
        matrixUtil matrixA, matrixB, matrixC;

        globalMatrix.globalMatrix(numberOfNodesGlobal, kelement[0], conn[0]);
        
        matrixA.m = numberOfNodesGlobal;
        matrixA.n = numberOfNodesGlobal;
        
        cout << "m= " << matrixA.m << " n= " << matrixA.n << "\n";
        
        cout << "MATRIX A: \n";
        
        matrixA.MX = globalMatrix.GLOBAL_K;
        
        for (int i=0;i<numberOfNodesGlobal; i++)
        {
            for(int j=0;j<numberOfNodesGlobal;j++)
            {
               cout << "| " << setw(10) << matrixA.MX[i][j] << "|";
            }
            cout << "\n" ;
        }

        cout << "\nMATRIX B: \n";

        
        globalMatrix.globalMatrix(numberOfNodesGlobal, kelement[1], conn[1]);
        matrixB.m = numberOfNodesGlobal;
        matrixB.n = numberOfNodesGlobal;
        matrixB.MX = globalMatrix.GLOBAL_K;
        
        for (int i=0;i<numberOfNodesGlobal; i++)
        {
            for(int j=0;j<numberOfNodesGlobal;j++)
            {
                 cout << "| " << setw(10) << matrixB.MX[i][j] << "|";
            }
            cout << "\n" ;
        }
        
        cout << "\nMATRIX C: \n";
        matrixC.m = numberOfNodesGlobal;
        matrixC.n = numberOfNodesGlobal;
       
        //matrixC = matrixA + matrixB;

        matrixC.MX = matrixC.sumMatrix(matrixA.MX, matrixB.MX, numberOfNodesGlobal);
        
        for (int i=0;i<numberOfNodesGlobal; i++)
        {
            for(int j=0;j<numberOfNodesGlobal;j++)
            {
                
                cout << "| " << setw(10) << matrixC.MX[i][j] << "|";

            }
            cout << "\n" ;
        }
        

        

        
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
}

double** readFile::readWorkFile(const char* file)
{
    elements = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number of nodes in this implementation
    conn = (nodeInput *) malloc(1000*sizeof(nodeInput)); //max number connectivity (WRONG!)
    
    int nodeCounter = 0;
    int connectivityCounter = 0;
    
    string tempvalue = "";
    std::string::size_type sz;
    
    double ** temp;
    
    
    
    return temp;
}



