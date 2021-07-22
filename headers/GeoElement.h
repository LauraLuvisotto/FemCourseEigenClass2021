//
//  GeoElement.h
//  FemSC
//
//  Created by Philippe Devloo on 16/04/18.
//

#ifndef GeoElement_h
#define GeoElement_h

#include "DataTypes.h"

/**
 @defgroup geometry Geometry of the domain
 @brief Groups geometric elements, geometric mesh and element/side classes
 */
class CompMesh;

class CompElement;

class GeoElementSide;

class GeoMesh;

/**
 @brief Root element class that defines a geometric element
 @ingroup geometry
 */
class GeoElement
{

protected:
    // Geometric mesh to which the element belongs
    GeoMesh *GMesh;
    
    // Material ID associated with the element
    int MaterialId;
    
    // Pointer to computational element
    CompElement *Reference;
    
    // Index of the element in the element vector
    int Index;
    
public:

    // Default Constructor of GeoElement
    GeoElement();
    
    // Constructor of GeoElement
    GeoElement(int materialid, GeoMesh *mesh, int index);

    // Copy constructor of GeoElement
    GeoElement(const GeoElement &copy);

    // Destructor of GeoElement
    virtual ~GeoElement();
    
    virtual GeoElement *Clone(GeoMesh *gmesh) const =0;
    
    // return the dimension of the element
    virtual int Dimension() const = 0;
    
    // Return number of corner nodes
    virtual int NCornerNodes() const = 0;
    
    // Return number of nodes
    virtual int NNodes() const = 0;
    
    // Return number of sides
    virtual int NSides() const = 0;

    // Return the index of an element nodes
    virtual int NodeIndex(int node) const = 0;
    
    // Return number fo sides associated with a side
    virtual int NSideNodes(int side) const = 0;
    
    // Local node index of a node associated with a side
    virtual int SideNodeIndex(int side, int node) const = 0;
    
    // Local node index of a node associated with a side
    virtual int SideNodeLocIndex(int side, int node) const = 0;
    
    /// Set the node indices of the element
    virtual void GetNodes(VecInt &nodes) const = 0;
    
    // Return neighbour element of a given side
    virtual GeoElementSide Neighbour(int side) const = 0;
    
    // Set neighbour element of a given side
    virtual void SetNeighbour(int side, const GeoElementSide &neigh) = 0;
    
    // Return the enumerated element type
    virtual MElementType Type() const = 0;

    // Return the enumerated element type
    virtual MElementType Type(int side) const;

    //Set reference
    virtual void SetReference(CompElement * elp){
        Reference = elp;
    }
    
    //Get reference
    virtual CompElement *GetReference() const {
        return Reference;
    }
    
    // Set geometric mesh
    void SetMesh(GeoMesh *gmesh)
    {
        GMesh = gmesh;
    }
    
    // Get geometric mesh
    GeoMesh* GetMesh() const {
        return GMesh;
    }
    
    // Return material ID
    int Material() const
    {
        return MaterialId;
    }
    
    // Set the element index
    void SetIndex(int index)
    {
        Index = index;
    }
    
    // Return the element index
    int GetIndex() const
    {
        return Index;
    }
    
    // returns true is the neighbour along side hasn't been initialized
    virtual int SideIsUndefined(int side) const = 0;
    
    virtual int WhichSide(VecInt &SideNodeIds) const;
    
    // Compute x mapping from local parametric coordinates
    virtual void X(const VecDouble &xi,  VecDouble &x) const = 0;
    
    // Compute gradient of x mapping from local parametric coordinates
    virtual void GradX(const VecDouble &xi, VecDouble &x, MatrixDouble &gradx) const = 0;
    
    // Compute a QR facotrization of the gradient of the mapping function, Q = Jacobian and R = axes
    virtual void Jacobian(const MatrixDouble &gradx, MatrixDouble &jac,MatrixDouble &axes, double &detjac, MatrixDouble &jacinv) const;
    
    // Function to print results
    virtual void Print(std::ostream &out) const;
    

};
#endif /* GeoElement_h */
