//
//  GeoElementTemplate.h
//  FemSC
//
//  Created by Philippe Devloo on 16/04/18.
//

#ifndef GeoElementTemplate_h
#define GeoElementTemplate_h

#include "GeoElementSide.h"

/**
@brief Geometric element defined based on a @ref geometrymap
 
 The template TGeom must be one of the classes defined in @ref geometrymap
@ingroup geometry
*/
template<class TGeom>
class GeoElementTemplate : public GeoElement
{
    
protected:
    
    // Definition of an element type
    TGeom Geom;
    
    
public:
    
    // Constructor of GeoElementTemplate
    GeoElementTemplate(const VecInt &nodeindices, int materialid, GeoMesh *gmesh, int index);
    
    // Copy constructor of GeoElementTemplate
    GeoElementTemplate(const GeoElementTemplate &copy);
    
    // Operator of copy
    GeoElementTemplate &operator=(const GeoElementTemplate &copy);
    
    // Make a geometric mesh clone from GeoElement
    GeoElement *Clone(GeoMesh *gmesh) const
    {
        GeoElement *result = new GeoElementTemplate(*this);
        result->SetMesh(gmesh);
        return result;
    }

    // return the dimension of the element
    virtual int Dimension() const
    {
        return TGeom::Dimension;
    }
    
    // Return the number of corner nodes of a given element
    virtual int NCornerNodes() const
    {
        return TGeom::nCorners;
    }
    
    // Return the number of nodes of a given element
    virtual int NNodes() const
    {
        return Geom.NumNodes();
    }
    
    // Return the number of nodes of a given element
    virtual int NSides() const
    {
        return TGeom::nSides;
    }
    
    // Return number fo sides associated with a side
    virtual int NSideNodes(int side) const
    {
        return Geom.NSideNodes(side);
    }
    
    // Local node index of a node associated with a side
    virtual int SideNodeIndex(int side, int node) const
    {
        return Geom.NodeIndex(Geom.SideNodeLocIndex(side,node));
    }
    
    // Local node index of a node associated with a side
    virtual int SideNodeLocIndex(int side, int node) const
    {
        return Geom.SideNodeLocIndex(side,node);
    }
    
    /// Return the node indices of the element
    virtual void GetNodes(VecInt &nodes) const
    {
        return Geom.GetNodes(nodes);
    };

    // Return the index of an element node
    virtual int NodeIndex(int node) const
    {
        if(node<0 || node>=Geom.NumNodes()) DebugStop();
        return Geom.NodeIndex(node);
    }
    
    // Return the neighbour along side
    virtual GeoElementSide Neighbour(int side) const
    {
        return Geom.Neighbour(side);
    }
    
    // Initialize the neighbour data structure
    virtual void SetNeighbour(int side, const GeoElementSide &neigh)
    {
        Geom.SetNeighbour(side,neigh);
    }
    
    // Return the enumerated element type
    virtual MElementType Type() const;
    
    // Compute x mapping from local parametric coordinates
    virtual void X(const VecDouble &xi, VecDouble &x) const;
    
    // Compute gradient of x mapping from local parametric coordinates
    virtual void GradX(const VecDouble &xi, VecDouble &x, MatrixDouble &gradx) const;
    
    virtual int SideIsUndefined(int side) const;
    
    // Function to print results
    virtual void Print(std::ostream &out) const;

};

#endif /* GeoElementTemplate_h */
