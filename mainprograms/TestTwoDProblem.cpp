

//
//  TestOneDProblem.cpp MODIFICADO DO ORIGINAL
//  FemSC
//
//  Created by Eduardo Ferri on 08/17/15.
//
//
//TestOneDProblem cpp

// Os testes foram preparados com um proposito educacional,
// recomenda-se que o aluno entenda a funcionalidade de cada
// teste e posteriormente use com seu cÛdigo caso a caso

//      Obs: O xmax e xmin estao tomados como 4 e 0, respectivamente,
//      caso estes valores sejam alterados, editar o teste TestNodes.
//
//
#include <iostream>
#include <math.h>
#include "GeoNode.h"
#include "GeoElement.h"
#include "IntPointData.h"
#include "CompElementTemplate.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ReadGmsh.h"
#include "CompMesh.h"
#include "GeoMesh.h"
#include "GeoElement.h"
#include "GeoElementTemplate.h"
#include "MathStatement.h"
#include "Poisson.h"
#include "L2Projection.h"
#include "Analysis.h"
#include "IntRule.h"
#include "IntRule1d.h"
#include "IntRuleQuad.h"
#include "IntRuleTetrahedron.h"
#include "IntRuleTriangle.h"
#include "Topology1d.h"
#include "TopologyTriangle.h"
#include "TopologyQuad.h"
#include "TopologyTetrahedron.h"
#include "PostProcess.h"
#include "PostProcessTemplate.h"
#include "DataTypes.h"
#include "VTKGeoMesh.h"
#include "CompElement.h"



int main() {
    GeoMesh gmesh;
    ReadGmsh read;
    //std::string filename("quads.msh");

//#ifdef MACOSX
    //filename = "../" + filename;
//#endif // MACOSX
    read.Read(gmesh, "quadsquadrada.msh");

    //void exact(const VecDouble & point, VecDouble & val, MatrixDouble & deriv);

    CompMesh cmesh(&gmesh);
    MatrixDouble perm(3, 3);
    perm.setZero();
    perm(0, 0) = 1.;
    perm(1, 1) = 1.;
    perm(2, 2) = 1.;
    //Poisson* mat1 = new Poisson(1, perm);
    Poisson* mat1 = new Poisson(1, perm);

    mat1->SetDimension(2);

    auto force = [](const VecDouble& x, VecDouble& res)
    {
        res[0] = 2. * (1. - x[0] * x[0] + 2. * (1 - x[1]) * x[1]);
    };
    auto exact = [](const VecDouble& x, VecDouble& val, MatrixDouble& deriv)
    {
        val[0] = (1. - x[0] * x[0] * (1 - x[1]) * x[1]);
        deriv(0, 0) = (1. - 2. * x[0]) * (1 - x[1] * x[1]);
        deriv(1, 0) = (1. - 2. * x[1]) * (1 - x[0]) * x[0];

    };
    mat1->SetForceFunction(force);
    mat1->SetExactSolution(exact);
    MatrixDouble proj(1, 1), val1(1, 1), val2(1, 1);
    proj.setZero();
    val1.setZero();
    val2.setZero();

    L2Projection* bc_linha = new L2Projection(0, 2, proj, val1, val2);
    L2Projection* bc_point = new L2Projection(0, 1, proj, val1, val2);
    std::vector<MathStatement*> mathvec = { 0,mat1,bc_point,bc_linha };
    cmesh.SetMathVec(mathvec);
    cmesh.SetDefaultOrder(2);
    cmesh.AutoBuild();
    cmesh.Resequence();

    Analysis locAnalysis(&cmesh);
    locAnalysis.RunSimulation();
    PostProcessTemplate<Poisson> postprocess;



    postprocess.AppendVariable("Flux");
    postprocess.AppendVariable("Sol");
    postprocess.AppendVariable("DSol");
    postprocess.AppendVariable("SolExact");
    postprocess.AppendVariable("Force");
    postprocess.AppendVariable("DSolExact");

    postprocess.SetExact(exact);
    mat1->SetExactSolution(exact);
    mat1->SetExactSolution(exact);


    locAnalysis.PostProcessSolution("quadsquadrada.vtk", postprocess);

    VecDouble errvec;
    errvec = locAnalysis.PostProcessError(std::cout, postprocess);

    VTKGeoMesh::PrintCMeshVTK(&cmesh, 2, "solution.vtk");

    return 0;


}
