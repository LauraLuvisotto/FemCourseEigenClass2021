//
//  TopologyQuad.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef TopologyQuad_h
#define TopologyQuad_h

#include "IntRuleQuad.h"

/**
 @brief Defines the topology associated with a quadrilateral
 @ingroup topology
 */
class TopologyQuad
{
public:
    
    // Type definition of integration rule for quadrilateral elements
    typedef IntRuleQuad LocIntRule;
    
    // Number of sides associated with quadrilateral elements elements
    const static int nSides = 9;
    
    // Number of corner nodes associated with quadrilateral elements
    const static int nCorners = 4;
    
    // Dimension of quadrilateral elements
    const static int Dimension = 2;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the enumerated element type
    static MElementType Type();
};


#endif /* TopologyQuad_h */
