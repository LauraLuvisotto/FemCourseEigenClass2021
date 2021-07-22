//
//  DOF.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef DOF_h
#define DOF_h
#include "DataTypes.h"
///\cond
#include <iostream>
///\endcond
class CompMesh;

/**
@brief Definition of a degree of freedom

A degree of freedom groups the equations/degrees of freedom associated with an element/side
@ingroup approximation
*/
class DOF
{
    // First associated equation
    int64_t firstequation = -1;
    
    // Number of shape functions associated with the DOF
    int nshape = 0;
    
    // Number of state variables associated with each shape function
    int nstate = 0;
    
    // Polinomial order of the shape function associated with the connect
    int order = 1;
    
public:
    
    // Default constructor of DOF
    DOF();
    
    // Copy constructor of DOF
    DOF(const DOF &copy);
    
    // Operator of copy
    DOF &operator=(const DOF &copy);
    
    // Destructor of DOF
    ~DOF();
    
    // Return the first associated equation
    int64_t GetFirstEquation() const;
    
    // Set the first associated equation
    void SetFirstEquation(int64_t first);
    
    // Set the number of shape functions associated with the DOF and state variables associated with each shape function
    void SetNShapeStateOrder(int NShape, int NState, int Order);
    
    // Return the number of shape functions associated with the DOF
    int GetNShape() const;
    
    // Return the number of state variables associated with each shape function
    int GetNState() const;
    
    // Return maximum the order of the polinoms associated with DOF
    int GetOrder() const;
    
    // Method to print information of DOF elements
    void Print(const CompMesh &mesh, std::ostream & out = std::cout) const;
    

};
#endif /* DOF_h */
