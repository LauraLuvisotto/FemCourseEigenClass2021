//
//  GeoNode.h
//  FemSC
//
//  Created by Philippe Devloo on 16/04/18.
//

#ifndef GeoNode_h
#define GeoNode_h

#include "DataTypes.h"


/**
@brief Geometric node
 
 This class defines the location of a geometric node
@ingroup geometry
*/
class GeoNode
{
    // Vector with node coordinates
    VecDouble xco;
    
public:
    
    // Constructor of GeoNode
    GeoNode(): xco(0){
        
    }
    
    // Constructor of GeoNode
    GeoNode(VecDouble &co) : xco(co)
    {
        
    }
    
    // Destructor of GeoNode
    ~GeoNode(){
        
    }
    
    // Copy constructor of GeoNode
    GeoNode(const GeoNode &copy) : xco(copy.xco)
    {
        
    }
    
    // Operator of copy
    GeoNode &operator=(const GeoNode &copy)
    {
        xco = copy.xco;
        return *this;
    }
    
    // Return the coordinates of the current node
    const VecDouble &Co() const
    {
        return xco;
    }
    
    // Return i-th coordinate of the current node
    double Coord(int coo) const
    {
        return xco[coo];
    }
    
    // Sets all coordinates into the current node
    void SetCo(const VecDouble &co)
    {
        xco = co;
    }
    
    // Function to print results
    void Print(std::ostream &out) const;
    
};
#endif /* GeoNode_h */
