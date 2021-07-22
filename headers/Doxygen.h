//
//  documentation mainpage
//
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __DOXYGEN__
#define __DOXYGEN__

/**
 @mainpage A Simple object oriented finite element code
 
 Object oriented programming combines well with finite element computations :
 elements are objects, nodes are objects, matrices are objects etc.
 
 The proper definition of classes, however, is not straightforward. In this code we separate the geometric map (\ref geometrymap) from the definition of the approximation space (\ref shape). This makes the code inherently extensible: other approximation spaces can be added without changing the geometric map. The geometric map can be extended without affecting the definition of the approximation space.
 
 
 
 Another separate module is the definition of the variational statement. Finite elements applied to partial differential equations invariably apply a Galerkin approximation to a variational statement associated with a (system of) partial differential equation(s). Keeping the classes that compute the integration point contributions seperate allow to use the same class to the Poisson equation and/or elasticity equation.
 
 \page FEM Performing a finite element simulation
 
 In order to perform a finite element simulation a sequence of steps have to be performed:
    - Generate a geometric mesh based on a Gmsh file using the class ReadGmsh
    - Create a CompMesh object based on the object GeoMesh created by ReadGmsh
    - Insert MathStatement objects that implement the variational statement and boundary conditions
            - Associate a forcing function using the Poisson::SetForceFunction method (Poisson and L2Projection)
            - Register an analytic solution (if available) with Poisson::SetExactSolution
    - Create the computational elements and other structures using the CompMesh::AutoBuild method
    - Create an Analysis object taking the CompMesh object as input
    - Call the Analysis::RunSimulation method
    - Post process the results with the Analysis::PostProcessSolution method
    - Compute the approximation error with the Analysis::PostProcessError method
 
 HAVE FUN COMPUTING
 
 \page Stiffness Computing an element stiffness matrix
 
 ![Integrating a stiffness matrix](StiffnessIntegral.png)
 
 The above image summarizes the computing of a stiffness matrix for a Poisson problem. From this formula one can deduce the
 steps necessary to compute an element stiffness matrix
 
 - Initialize the matrices EK and EF
 - Initialize the IntPointData data structure calling CompElement::InitializeIntPointData
 - Create an integration rule
        - Compute the integration point data in IntPointData using CompElement::ComputeRequiredData
 
 */
#endif
