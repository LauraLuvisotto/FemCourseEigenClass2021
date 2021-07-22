//
//  CompElementTemplate.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef CompElementTemplate_h
#define CompElementTemplate_h

#include "CompElement.h"
#include "DOF.h"

/**
@brief Computational element based on @ref shape

This class implements the computation of element shape functions and holds the information of DOF objects
 through their indices
@ingroup approximation
*/

template<class Shape>
class CompElementTemplate : public CompElement
{

    // Vector with degrees of freedom indices
    std::vector<int64_t> dofindexes;
    
    // Integration rule object
    typename Shape::LocIntRule intrule;
    
public:
    
    // Default constructor of CompElementTemplate
    CompElementTemplate();
    
    // Constructor of CompElementTemplate
    CompElementTemplate(int64_t ind, CompMesh *cmesh, GeoElement *geo);
    
    // Copy constructor of CompElementTemplate
    CompElementTemplate(const CompElementTemplate &);
    
    // Operator of copy
    CompElementTemplate &operator=(const CompElementTemplate &);
    
    // Destructor of CompElementTemplate
    virtual ~CompElementTemplate();
    
    // Method for creating a copy of the element
    virtual CompElement *Clone() const;
    
    // Compute shape functions set at point x
    virtual void ShapeFunctions(const VecDouble &intpoint, VecDouble &phi, MatrixDouble &dphi) const;
    
    // 
    virtual void GetMultiplyingCoeficients(VecDouble &coefs) const;
    
    // Return the number of shape functions
    virtual int NShapeFunctions() const;

    // Set number of DOF
    virtual void SetNDOF(int64_t ndof);
    
    // Se DOF index in vector position i
    virtual void SetDOFIndex(int i, int64_t dofindex);
    
    // Get DOF index in vector position i
    virtual int64_t GetDOFIndex(int i) const;
    
    // Return the number of degree of freedom
    virtual int64_t NDOF() const;
    
    // Return the number of shape functions stored in the DOF data structure
    virtual int NShapeFunctions(int doflocindex) const;
    
    // Use the Shape template class to compute the number of shape functions
    virtual int ComputeNShapeFunctions(int doflocindex, int order);
    
    // Return space dimension
    virtual int Dimension() const {
        return Shape::Dimension;
    }
    
    virtual void Print(std::ostream &out);
};

// Create a computational element
CompElement *CreateCompEl(GeoElement *gel, CompMesh *mesh, int64_t index);

#endif /* CompElementTemplate_h */
