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
    conn = (nodeInput *) malloc(1000*sizeof(nodeInput));        //max number connectivity (WRONG!)
    forces = (nodeInput *) malloc(1000*sizeof(nodeInput));        //max number connectivity (WRONG!)
    
    int elementCounter = 0;
    int connectivityCounter = 0;
    int forceCounter = 0;
    int numberOfNodes=0;

    string tempvalue = "";
    std::string::size_type sz;

    try
    {
        string line;
        string str = "/Users/diegoandrade/Dropbox/USF/2017/FEM/FEM/FEMXCode/";  //here change to your local folder
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
                
                else if (tokens[0] == "F" && foundN==true)
                {
                    D( cout << "FOUND F" << '\n'; )
                    cout << "FOUND F" << '\n';
                    
                    //extract the information and pases it to class nodes -> connectivity
                    tempvalue = tokens[1];
                    forces[forceCounter].fx = stod(tempvalue, &sz);
                    tempvalue = tokens[2];
                    forces[forceCounter].fy = stod(tempvalue, &sz);
                    tempvalue = tokens[3];

                    forceCounter++;
                    
                    
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
        
        for (int i=0;i<8;i++)
        {
            kelement[i].elementStiffnessMatrix(A, elements[i].l, E, elements[i].ang);
            kelement[i].printMtrx(to_string(i+1));
        }
        
        matrixUtil matrixA, matrixB, matrixC;
        matrixA.m = matrixB.m =  matrixC.m = numberOfNodesGlobal;
        matrixA.n = matrixB.n =  matrixC.n = numberOfNodesGlobal;
        
        globalMatrix.globalMatrix(numberOfNodesGlobal, kelement[0], conn[0]);
        matrixA.MX = globalMatrix.GLOBAL_K;
        
        globalMatrix.globalMatrix(numberOfNodesGlobal, kelement[1], conn[1]);
        matrixB.MX = globalMatrix.GLOBAL_K;

        matrixC.MX = matrixC.sumMatrix(matrixA.MX, matrixB.MX, numberOfNodesGlobal);
        
        for (int k=2;k<8;k++)
        {
            matrixA.MX = matrixC.MX;
            globalMatrix.globalMatrix(numberOfNodesGlobal, kelement[k], conn[k]);
            matrixB.MX = globalMatrix.GLOBAL_K;
            matrixC.MX = matrixC.sumMatrix(matrixA.MX, matrixB.MX, numberOfNodesGlobal);
        }
        
        cout << "\n GLOBAL STIFNESS MATRIX [K_G]: \n";
        for (int i=0;i<numberOfNodesGlobal; i++)
        {
            for(int j=0;j<numberOfNodesGlobal;j++)
            {
                
                cout << "| " << setw(11) << matrixC.MX[i][j] << "|";
                
            }
            cout << "\n" ;
        }
        
        double * forceTemp = new double [numberOfNodesGlobal];
        
        for (int i=0;i<numberOfNodesGlobal;i++)
        {
            forceTemp[i]=0.0;
        }
        
        for (int i=0;i<numberOfNodesGlobal;i++)
        {
            forceTemp[2*i]=forces[i].fx;
            forceTemp[2*i+1]=forces[i].fy;
        }
        
        cout << "\nFORCE VECTOR [F]: \n";
        for(int j=0;j<numberOfNodesGlobal;j++)
        {
            
            cout << "Force[" << j+1 << "]: " << setw(0) << forceTemp[j] << endl;
            
        }
        cout << "\n" ;
        
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



