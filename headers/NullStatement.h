//
//  NullStatement.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef NULL_h
#define NULL_h

#include "MathStatement.h"
///\cond
#include <functional>
///\endcond
/**
 @brief Implements a NULL variational formulation
 @ingroup mathstatement
 
 This class contributes zero to the stiffness matrix and right hand side
 */
class NullStatement : public MathStatement
{

    
public:
    
    enum PostProcVar {ENone, ESol, EDSol};
    
    // Default constructor of NullStatement
    NullStatement();
    
    // Constructor of NullStatement
    NullStatement(int materialid);
    
    // Copy constructor of NullStatement
    NullStatement(const NullStatement &copy);
    
    // Operator of copy
    NullStatement &operator=(const NullStatement &copy);
    
    // Method for creating a copy of the element
    virtual NullStatement *Clone() const;

    // Destructor of NullStatement
    virtual ~NullStatement();
    
    
    // Return the number of state variables
    virtual int NState() const {
        return 1;
    };
    
    
    virtual int VariableIndex(const PostProcVar var) const;
    
    // Return the variable index associated with the name
    virtual PostProcVar VariableIndex(const std::string &name);
    
    // Return the number of variables associated with the variable indexed by var. Param var Index variable into the solution, is obtained by calling VariableIndex
    virtual int NSolutionVariables(const PostProcVar var);
    
    
    // Method to implement integral over element's volume
    virtual void Contribute(IntPointData &integrationpointdata, double weight , MatrixDouble &EK, MatrixDouble &EF) const;
    
    // Return the number of errors
    virtual int NEvalErrors() const {
        return 0;
    }

    // Method to implement error over element's volume
    virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, MatrixDouble &du_exact, VecDouble &errors) const
    {
        DebugStop();
    }
    
    // Prepare and print post processing data
    virtual void PostProcessSolution(const IntPointData &integrationpointdata, const int var, VecDouble &sol) const;

    
};
#endif /* NullStatement_h */
