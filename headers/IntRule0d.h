//
//  IntRule0d.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRule0d__
#define __FemSC__IntRule0d__

///\cond
#include <cmath>
#include <stdio.h>
///\endcond
#include "IntRule.h"

/**
 @brief Integration rule associated with a point
 @ingroup integration
 */
class IntRule0d : public IntRule
{
    
public:
  
    // Default Constructor of integration rule 1D
    IntRule0d();
    
    // Constructor of integration rule 1D
    IntRule0d(int order);
    
    // Method to set polynomial order of the integration rule 1D
    virtual void SetOrder(int order) override;
    
    // Dimension of the integration rule
    virtual int Dimension() const override
    {
        return 0;
    }
    
    // Return the maximum polynomial order that can be integrated exactly
    static int gMaxOrder()
    {
        return 0;
    }

    // Return the maximum polynomial order that can be integrated exactly
    virtual int MaxOrder() const override
    {
        return gMaxOrder();
    }

};


#endif /* defined(__FemSC__TIntRule0d__) */
