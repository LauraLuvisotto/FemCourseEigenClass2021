//
//  GeomTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#ifndef GeomTriangle_h
#define GeomTriangle_h

#include "TopologyTriangle.h"
#include "GeoElementSide.h"

/**
 @brief Geometric map of a triangular element
 @ingroup geometrymap
 */
class GeomTriangle : public TopologyTriangle
{
public:
    
    // Constructor
    GeomTriangle();
    
    // Destructor
    ~GeomTriangle();
    
    // Copy constructor
    GeomTriangle(const GeomTriangle &copy);
    
    // Operator of copy
    GeomTriangle &operator=(const GeomTriangle &copy);
    
    /** @brief Computes the value of the shape functions associated with the geometric map at a given parametric coordinates
     * @param xi [input] A vector containing the d parametric coordinates of the point to evaluate shape functions. (d = dimension of this geometric map)
     * @param phi [output] A vector to fill with the sampled values of shape function
     * @param dphi [output] A matrix to fill with the derivatives of shape functions. dphi(i,j) contains the i'th derivative of the j'th shape function
    */
    static void Shape(const VecDouble &xi, VecDouble &phi, MatrixDouble &dphi);
    
    /** @brief Computes the mapped point (x) for a given point in parameter space (xi) as a function of corner coordinates 
     * @param xi [input] A vector containing the d parametric coordinates of the point to map
     * @param NodeCo [input] A matrix containing the coordinates of the corner nodes of the element. NodeCo(i,j) contains the i'th coord of the j'th node
     * @param x [output] A vector with the mapped coordinates
    */
    static void X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x);
    
    /** @brief Computes the mapped point (x) and the gradient of the map function at this point
     * @param xi [input] A vector containing the d parametric coordinates of the point to map
     * @param NodeCo [input] A matrix containing the coordinates of the corner nodes of the element. NodeCo(i,j) contains the i'th coord of the j'th node
     * @param x [output] A vector with the mapped coordinates
     * @param gradx [output] A matrix with the components of the gradient of the map at the point x. gradx(i,j) contains the derivative j of coordinate i
    */
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

#endif /* GeomTriangle_h */
