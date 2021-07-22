//
//  ShapeQuad.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef ShapeQuad_h
#define ShapeQuad_h

#include "TopologyQuad.h"

/**
@brief Shape functions associated with a quadrilateral
@ingroup shape
*/
class ShapeQuad : public TopologyQuad
{
public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int side, int order);
    
    // Returns the total number of shape functions
    static int NShapeFunctions(VecInt &orders);
    
};


#endif /* ShapeQuad_h */
