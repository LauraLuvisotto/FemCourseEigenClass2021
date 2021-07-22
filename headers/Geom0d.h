//
//  Geom0d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef Geom0d_h
#define Geom0d_h

#include "Topology0d.h"
#include "GeoElementSide.h"

/**
 @defgroup geometrymap Geometric map of an element
 @brief Groups classes define the mapping from the master element to the deformed element
 
 They need to define the computation of X and GradX at a point in master element space
 */

/**
 @brief Defines the geometry associated with a point
 
 In this case the geometric map is rather trivial, a point in parametric space has dimension zero
 @ingroup geometrymap
 */
class Geom0d : public Topology0d
{
public:
    
    // Constructor
    Geom0d();
    
    // Destructor
    ~Geom0d();
    
    // Copy constructor
    Geom0d(const Geom0d &copy);
    
    // Operator of copy
    Geom0d &operator=(const Geom0d &copy);
    
    // Computes the shape functions associated with the geometric map
    static void Shape(const VecDouble &xi, VecDouble &phi, MatrixDouble &dphi);
    
    // Computes the value of x for a given point in parameter space as a function of corner coordinates
    static void X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x);
    
    // Computes the value of x and gradx for a given point in parameter space
    static void GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx);
    
    // Return the number of nodes of the template
    static int NumNodes();
    
    // Set the node indices of the element
    void SetNodes(const VecInt &nodes);
    
    // Set the node indices of the element
    void GetNodes(VecInt &nodes) const;
    
    // Return the index of a node
    int NodeIndex(int node) const;
    
    // Return the neighbour along side
    GeoElementSide Neighbour(int side) const;
    
    // Initialize the neighbour data structure
    void SetNeighbour(int side, const GeoElementSide &neighbour);
    
protected:
    
    // Indexes of the nodes of the geometry
	VecInt fNodeIndices;
    
    // Vector of neighbours
    GeoElementSide fNeighbours[nSides];
};

#endif /* Geom0d_h */
