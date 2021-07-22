//
//  CompMesh.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef CompMesh_h
#define CompMesh_h

#include "DOF.h"

class CompElement;

class GeoMesh;

class MathStatement;

class GeoMesh;

class DOF;

/**
 @brief Definition of a computational mesh
 
 @ingroup approximation
 groups computational elements, degrees of freedom and pointers to the mathematical statement\n
 the computational mesh is essentially a database for the above mentioned objects
 */
class CompMesh
{
    /// pointer to the geometric mesh
    GeoMesh *geomesh;
    
    // Vector with computational elements objects
    std::vector<CompElement *> compelements;
    
    // Vector with degrees of freedom
    std::vector<DOF> dofs;
    
    // Vector with math statement objects
    std::vector<MathStatement *> mathstatements;
    
    // Vector with solution coeficients
    VecDouble solution;
    
    /** @brief Default order for all elements of this mesh */
    int64_t DefaultOrder = 1;
    
public:
    
    // Default constructor of CompMesh
    CompMesh();
    
    // Default constructor of CompMesh
    CompMesh(GeoMesh *gmesh);
    
    // Copy constructor of CompMesh
    CompMesh(const CompMesh &copy);
    
    // Destructor of CompMesh
    ~CompMesh();
    
    GeoMesh *GetGeoMesh() const;
    
    void SetGeoMesh(GeoMesh *gmesh);
    
    // Set the number of computational elements on the grid
    void SetNumberElement(int64_t nelem);
    
    // Set the number of degrees of freedom
    void SetNumberDOF(int64_t ndof);
    
    // Set the number of math statements
    void SetNumberMath(int nmath);
    
    int64_t GetNumberDOF() const {
        return dofs.size();
    }
    
    // Set the computational element associated to an index
    void SetElement(int64_t elindex, CompElement *cel);
    
    // Set the degree of freedom associated to an index
    void SetDOF(int64_t index, const DOF &dof);
    
    // Set the math statement object associated to an index
    void SetMathStatement(int index, MathStatement *math);
    
    // Set Default Order
    void SetDefaultOrder( int order )
    {
        DefaultOrder = order;
    }

    // Get Default Order
    int64_t GetDefaultOrder()
    {
        return DefaultOrder;
    }
    
    // Return the degree of freedom index
    DOF &GetDOF(int64_t dofindex);
    
    // Return the computational element associated to an index
    CompElement *GetElement(int64_t elindex) const;
    
    // Return the math statement object associated to an index
    MathStatement *GetMath(int matindex) const;

    // Return the vector with computational elements
    const std::vector<CompElement *> &GetElementVec() const;
    
    // Return the vector with degrees of freedom
    const std::vector<DOF> &GetDOFVec() const;
    
    // Return the vector with math statement objects
    const std::vector<MathStatement *> &GetMathVec() const;
    
    // Set the vector with computational elements
    void SetElementVec(const std::vector<CompElement *> &vec);
    
    // Set the vector with degrees of freedom
    void SetDOFVec(const std::vector<DOF> &dofvec);
    
    // Set the vector with math statement objects
    void SetMathVec(const std::vector<MathStatement *> &mathvec);
    
    // will create the computational elements
    void AutoBuild();
    
    // Initialize the datastructure FirstEquation of the DOF objects
    void Resequence();
    
    // Initialize the datastructure FirstEquation of the DOF objects in the order specified by the vector
    void Resequence(VecInt &DOFindices);
    
    VecDouble &Solution();
    
    void LoadSolution(VecDouble &Sol);
    
    // Method to print computational mesh
    virtual void Print(std::ostream & out = std::cout);
    
};

#endif /* CompMesh_h */
