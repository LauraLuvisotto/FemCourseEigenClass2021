//
//  Topology1d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef Topology0d_h
#define Topology0d_h

/**
@defgroup topology Topology of a finite element
@brief Groups the class that define the topologies
 
The topology classes define master element as the union of open sets of points.
A topology has a dimension, a number of sides and number of corner nodes

A topology can be associated with each side. The topology associated with the last side is the topology itself

*/

#include "IntRule0d.h"

/*
 @brief Defines the topology associated with a point
 
 This topology has dimension zero and only one point
 It will be used to define point loads
 @ingroup topology
 */
class Topology0d
{
public:
    
    // Type definition for integration rule 1D
    typedef IntRule0d LocIntRule;
    
    // Number of sides associated with 1D elements
    const static int nSides = 1;

    // Number of corner nodes associated with 1D elements
    const static int nCorners = 1;
    
    // Dimension of 1D elements
    const static int Dimension = 0;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the enumerated element type
    static MElementType Type();
};

#endif /* Topology1d_h */
