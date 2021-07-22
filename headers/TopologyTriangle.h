//
//  TopologyTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef TopologyTriangle_h
#define TopologyTriangle_h

#include "IntRuleTriangle.h"

/**
 @brief Defines the topology associated with a triangle
 @ingroup topology
 */
class TopologyTriangle
{
public:

    // Type definition of integration rule for triangle elements
    typedef IntRuleTriangle LocIntRule;
    
    // Number of sides associated with triangle elements elements
    static const int nSides = 7;
    
    // Number of corner nodes associated with triangle elements
    static const int nCorners = 3;
    
    // Dimension of triangle elements
    const static int Dimension = 2;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the enumerated element type
    static MElementType Type();
};


#endif /* TopologyTriangle_h */
