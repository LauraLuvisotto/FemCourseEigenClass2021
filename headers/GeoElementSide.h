//
//  GeoElementSide.h
//  FemSC
//
//  Created by Philippe Devloo on 16/04/18.
//

#include "GeoElement.h"

#ifndef GeoElementSide_h
#define GeoElementSide_h

class GeoElement;

/**
@brief Clas associating an element with a side
 
 This class is built to facilitate iterating between neighbours of elements
@ingroup geometry
*/
class GeoElementSide
{
    // Associated element
    GeoElement *fElement;
    
    // Associated side
    int fSide;
    
public:
    
    // Default Constructor of GeoElementSide
    GeoElementSide();
    
    // Constructor of GeoElementSide
    GeoElementSide(GeoElement *element, int side) : fElement(element), fSide(side)
    {
        if(!element || side >= element->NSides()) DebugStop();

    }
    
    // Copy constructor of GeoElementSide
    GeoElementSide(const GeoElementSide &copy);
    
    // Operator of copy 
    GeoElementSide &operator=(const GeoElementSide &copy);
    
    int operator==(const GeoElementSide &other) const {
        return fElement == other.fElement && fSide == other.fSide;
    }
    int operator!=(const GeoElementSide &other) const {
        return ! operator==(other);
    }
    
    // Return the associated element
    GeoElement *Element() const
    {
        return fElement;
    }

    // Return the associated side
    int Side() const
    {
        return fSide;
    }

    // Return neighbour element of a given side
    GeoElementSide Neighbour() const;
    
    int Exists() const {return (fElement != 0 && fSide > -1);}
    
    // Fill in the data structure for the neighbouring information
    void SetNeighbour(const GeoElementSide &neighbour);
    
    // Verifiy if an element is a neighbour
    bool IsNeighbour(const GeoElementSide &candidate) const;
    
    // Define elements neighbourhood
    void IsertConnectivity(GeoElementSide &connectivity);
    
    // Vector with all Neighbours
    void AllNeighbours(std::vector<GeoElementSide> &allneigh) const;
    
    // Compute all corner neighbours
    void ComputeNeighbours(std::vector<GeoElementSide> &neighbour);
    
    // Print the element index and side
    void Print(std::ostream &out) const;
    
};
#endif /* GeoElementSide_h */
