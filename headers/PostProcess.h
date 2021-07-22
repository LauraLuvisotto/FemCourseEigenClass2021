//
//  PostProcess.h
//  FemCourse
//
//  Created by Philippe Devloo on 15/05/18.
//

#ifndef PostProcess_h
#define PostProcess_h

///\cond
#include <functional>
///\endcond
#include "DataTypes.h"

class Analysis;

/**
 @brief Generates a .vtk file to graphically represent the results
 @ingroup global
 */
class PostProcess
{
protected:
    // Pointer to Exact solution function, it is necessary to calculating errors
    std::function<void (const VecDouble &loc, VecDouble &result, MatrixDouble &deriv)> fExact;
    
public:
    
    PostProcess() : fExact(0){
    }

    PostProcess(const PostProcess &copy){
        fExact = copy.fExact;
    }

    ~PostProcess(){

    }

    PostProcess &operator=(const PostProcess &cp){
        fExact = cp.fExact;
        return *this;
    }
    
    virtual void Write(std::string filename){
        
    }
    
    virtual void SetExact(std::function<void (const VecDouble &loc, VecDouble &result, MatrixDouble &deriv)> Exact){
        fExact=Exact;
    }
    
    virtual std::function<void (const VecDouble &loc, VecDouble &result, MatrixDouble &deriv)> GetExact(){
        return fExact;
    }
    
    virtual std::vector<std::string> Vectornames() const = 0;
    
    virtual std::vector<std::string> Scalarnames() const = 0;
    
    virtual VecInt VectorvariablesIds() const = 0;
    
    virtual VecInt ScalarvariablesIds() const = 0;
    
    virtual void AppendVariable(const std::string &name) = 0;
    
    virtual inline unsigned int NumScalarVariables() const = 0;
    
    virtual  inline unsigned int NumVectorVariables() const = 0;
    
    virtual inline unsigned int NumVariables() const = 0;
    
    
};
#endif /* PostProcess_h */
