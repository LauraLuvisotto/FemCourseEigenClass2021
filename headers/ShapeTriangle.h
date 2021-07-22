//
//  ShapeTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef ShapeTriangle_h
#define ShapeTriangle_h

#include "TopologyTriangle.h"

/**
@brief Shape functions associated with a triangle
@ingroup shape
*/
class ShapeTriangle : public TopologyTriangle
{
public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int side, int order);
    
    // Returns the total number of shape functions
    static int NShapeFunctions(VecInt &orders);
    
};


#endif /* ShapeTriangle_h */
