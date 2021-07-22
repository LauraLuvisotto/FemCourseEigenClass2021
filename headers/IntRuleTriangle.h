//
//  IntRuleTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __FemSC__IntRuleTriangle__
#define __FemSC__IntRuleTriangle__

///\cond
#include <stdio.h>
///\endcond
#include "IntRule.h"


/**
@brief Integration rule associated with a triangle
@ingroup integration
*/
class IntRuleTriangle : public IntRule
{
  
    public:
  
    // Default Constructor of integration rule for triangle elements
    IntRuleTriangle();
  
    // Constructor of integration rule for triangle elements
    IntRuleTriangle(int order);
  
    // Dimension of the integration rule
    virtual int Dimension() const override{
        return 2;
    }
    
    // Return the maximum polynomial order that can be integrated exactly
    static int gMaxOrder()
    {
        return 5;
    }

    // Return the maximum polynomial order that can be integrated exactly
    virtual int MaxOrder() const override
    {
        return gMaxOrder();
    }
    // Method to set polynomial order of the integration rule for triangle elements
    virtual void SetOrder(int order) override;
  
};


#endif /* defined(__FemSC__TIntRule1d__) */
