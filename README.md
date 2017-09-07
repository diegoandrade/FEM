# FEM
Finite Element Solver for USF class (Fall 2017)

Please create a folder using this files to create your own solver for finite elements.

> How to use the files in FEMVC++ 

1. Download the files to your computer
2. Look for FEM.sln
3. If you intalled VC++ you will be able to run the program directly by double clicking the icon.
4. Go to readFile.cpp
5. Add breakpoints to look at the program functionality.
6. Go to line 165 on readFile.cpp, this is the place where you need to add the new method.
7. Line 236 shows how to add two matrices using sumMatrix() method. Make sure to add all the Kelement matrices not just 2.

# HW 3

> 1. Create a method that makes the calculation and prints the matrices of the entire structure (e.g. for loop).

> 2. Create a method that sums all the Kelements for the eight elements K(global) = k(1) + ... + k(8).

> 3. Create a method that defines a vector where to store the forces on our system check slide 8 for class05.

# Deliverables

> a) Print out the three methods.

> b) Print out of K[Global] Matrix(12x12).

* Compare the results with your hand calculations

# Note 
Uncomment gradToRad() method in lines 32 and 133 for stiffnessMatrix.cpp, this will change the calculations on elementStiffnessMatrix() method, from degrees to radians.