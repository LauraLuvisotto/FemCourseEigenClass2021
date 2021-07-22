//
//  Shape1d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef Shape0d_h
#define Shape0d_h

#include "Topology0d.h"

/**
 @defgroup shape Shape functions
 @brief Groups classes that compute shape functions
 */

/**
 @brief Shape functions associated with a point element
 @ingroup shape
 */
class Shape0d : public Topology0d
{
public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int side, int order);
    
    // Returns the total number of shape functions
    static int NShapeFunctions(VecInt &orders);

};

#endif /* Shape1d_h */
