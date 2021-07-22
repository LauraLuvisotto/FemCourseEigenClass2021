//
//  Topology1d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef Topology1d_h
#define Topology1d_h

#include "IntRule1d.h"

/**
 @brief Defines the topology associated with a 1d element
 @ingroup topology
 
 represents a one dimensional line between -1 and 1
 */
class Topology1d
{
public:
    
    // Type definition for integration rule 1D
    typedef IntRule1d LocIntRule;
    
    // Number of sides associated with 1D elements
    const static int nSides = 3;

    // Number of corner nodes associated with 1D elements
    const static int nCorners = 2;
    
    // Dimension of 1D elements
    const static int Dimension = 1;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the enumerated element type
    static MElementType Type();
};

#endif /* Topology1d_h */
