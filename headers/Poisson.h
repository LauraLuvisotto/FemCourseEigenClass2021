//
//  Poisson.h
//  FemCourse
//
//  Created by Philippe Devloo on 24/04/18.
//

#ifndef Poisson_h
#define Poisson_h

#include "MathStatement.h"
///\cond
#include <functional>
///\endcond
/**
 @brief Implements a poisson problem in 1-, 2- or 3-dimensions
 @ingroup mathstatement
 */
class Poisson : public MathStatement
{

    // Permeability matrix
    MatrixDouble permeability;
    
    // Force funtion related to Poisson math statement
    std::function<void(const VecDouble &co, VecDouble &result)> forceFunction;
    
    std::function<void(const VecDouble &loc, VecDouble &result, MatrixDouble &deriv)> SolutionExact;
    
public:
    
    enum PostProcVar {ENone, ESol, EDSol, EFlux, EForce, ESolExact, EDSolExact};
    
    // Default constructor of Poisson
    Poisson();
    
    // Constructor of Poisson
    Poisson(int materialid, MatrixDouble &perm);
    
    // Copy constructor of Poisson
    Poisson(const Poisson &copy);
    
    // Operator of copy
    Poisson &operator=(const Poisson &copy);
    
    // Method for creating a copy of the element
    virtual Poisson *Clone() const;

    // Destructor of Poisson
    virtual ~Poisson();
    
    // Return the permeability matrix
    MatrixDouble GetPermeability() const;

    // Set the permeability matrix
    void SetPermeability(const MatrixDouble &perm);
    
    // Return the force function related to Poisson math statement
    std::function<void(const VecDouble &co, VecDouble &result)> GetForceFunction() const
    {
        return forceFunction;
    }
    
    // Set the force function related to Poisson math statement
    void SetForceFunction(const std::function<void(const VecDouble &co, VecDouble &result)> &f)
    {
        forceFunction = f;
    }
    
    // Set the exact solution related to Poisson math statement
    void SetExactSolution(const std::function<void(const VecDouble &loc, VecDouble &result, MatrixDouble &deriv)> &Exact)
    {
        SolutionExact = Exact;
    }
    
    // Return the number of state variables
    virtual int NState() const {
        return 1;
    };
    
    virtual int NEvalErrors() const;
    
//    int Dimension() const {
//        return 2;
//    }
    
    
    virtual int VariableIndex(const PostProcVar var) const;
    
    // Return the variable index associated with the name
    virtual PostProcVar VariableIndex(const std::string &name);
    
    // Return the number of variables associated with the variable indexed by var. Param var Index variable into the solution, is obtained by calling VariableIndex
    virtual int NSolutionVariables(const PostProcVar var);
    
    
    // Method to implement integral over element's volume
    virtual void Contribute(IntPointData &integrationpointdata, double weight , MatrixDouble &EK, MatrixDouble &EF) const;
    
    // Method to implement error over element's volume
    virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, MatrixDouble &du_exact, VecDouble &errors) const;
    
    // Prepare and print post processing data
    virtual void PostProcessSolution(const IntPointData &integrationpointdata, const int var, VecDouble &sol) const;

    virtual double Inner(MatrixDouble &S,MatrixDouble &T) const;
    
    
};
#endif /* Poisson_h */
