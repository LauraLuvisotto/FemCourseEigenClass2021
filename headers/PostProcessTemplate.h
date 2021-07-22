//
//  PostProcessTemplate.h
//  FemCourse
//
//  Created by Philippe Devloo on 15/05/18.
//

#ifndef PostProcessTemplate_h
#define PostProcessTemplate_h

#include "Poisson.h"
#include "Analysis.h"
#include "L2Projection.h"
///\cond
#include <list>
///\endcond

class PostProcess;

/**
 @brief Interfaces post processing for a particular math statement
 @ingroup global
 */
template<class math>
class PostProcessTemplate: public PostProcess
{

    protected:
    /// indices of the post processing variables that will be annexed to the vtk file
    std::vector<typename math::PostProcVar> scalarvariables;
    /// indexes of the vector valued post processing variables that will be annexed to the vtk file
    std::vector<typename math::PostProcVar> vectorvariables;

    /// names of the vector valued post processed quantities
    std::vector<std::string> vectornames;
    /// name of the scalar valued post processed quantities
    std::vector<std::string> scalarnames;

    
    public:
    
    PostProcessTemplate() : PostProcess(){
    }
    
    PostProcessTemplate(const PostProcessTemplate &copy) : PostProcess(copy) {
    }
    
    ~PostProcessTemplate(){
        
    }
    
    
    PostProcessTemplate &operator=(const PostProcessTemplate &cp){
        return *this;
    }

    
    virtual std::vector<std::string> Vectornames() const{
        return vectornames;
    }

    virtual std::vector<std::string> Scalarnames() const{
        return scalarnames;
    }
    
    /// translates the post processed vector variables strings into post processed indexes
    virtual VecInt VectorvariablesIds() const{
        math Statement;
        VecInt VecVar(NumVectorVariables());
        
        for (int index = 0; index< NumVectorVariables(); index++) {
            VecVar[index]=Statement.VariableIndex(vectorvariables[index]);
        }
        
        return VecVar;
    }

    /// translate the post processed scalar variables into post processed indexes
    virtual VecInt ScalarvariablesIds() const{
        math Statement;
        VecInt ScalVar(NumScalarVariables());
        
        for (int index = 0; index< NumScalarVariables(); index++) {
            ScalVar[index]=Statement.VariableIndex(scalarvariables[index]);
        }
        
        return ScalVar;
    }
    
    /// add a post processed quantity defined by a string
    virtual void AppendVariable(const std::string &name){
        math Statement;
        typename math::PostProcVar var = Statement.VariableIndex(name);
        AppendVariable(var);
    
        int nsol = Statement.NSolutionVariables(var);
        
        if (nsol==1) {
            scalarnames.push_back(name);
        }else if(nsol > 1){
            vectornames.push_back(name);
        }
        else
        {
            DebugStop();
        }
        
    }
    
    /// append a post processed variable identified by its enumerated value
    void AppendVariable(typename math::PostProcVar var){
        math Statement;
        int nsol = Statement.NSolutionVariables(var);
        
        if (nsol==1) {
            scalarvariables.push_back(var);
        }else{
            vectorvariables.push_back(var);
        }
        
    }
    
    /// compute a post processed quantity for a post processing variable index at a point defined by the intpointdata
    VecDouble PostProcResult(MathStatement &mathStatement, unsigned int varIndex, const IntPointData &data) const {
        math *locptr = dynamic_cast<math *> (&mathStatement);
        
        if(!locptr) DebugStop();
        const int numScalarVariables = NumScalarVariables();
        VecDouble sol;
        locptr->PostProcessSolution(data, varIndex < numScalarVariables? scalarvariables[varIndex] : vectorvariables[varIndex-numScalarVariables],sol);
        return sol;
    }
    
    virtual inline unsigned int NumScalarVariables() const {
        return scalarvariables.size();
    }
    
    virtual  inline unsigned int NumVectorVariables() const {
        return vectorvariables.size();
    }
    
    virtual inline unsigned int NumVariables() const {
        return NumScalarVariables() + NumVectorVariables();
    }
};
#endif /* PostProcessTemplate_h */

template class PostProcessTemplate<Poisson>;
template class PostProcessTemplate<L2Projection>;
