
#include <iostream>
#include <math.h>

#include "GeoMesh.h"
#include "ReadGmsh.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "L2Projection.h"
#include "Analysis.h"
#include "PostProcessTemplate.h"


int main()
{
    GeoMesh gmesh;
    ReadGmsh read;
    std::string filename("cube3D.msh");

    read.Read(gmesh, filename);

    CompMesh cmesh(&gmesh);
    MatrixDouble perm(3, 3);
    perm.setZero();
    perm(0, 0) = 1.;
    perm(1, 1) = 1.;
    perm(2, 2) = 1.;
    Poisson* mat1 = new Poisson(1, perm);
    mat1->SetDimension(3);

    auto force = [](const VecDouble& x, VecDouble& res)
    {
        double ax, ay, az;
        ax = (1 - x[0]) * x[0];
        ay = (1 - x[1]) * x[1];
        az = (1 - x[2]) * x[2];
        res[0] = 2. * (ay * az + ax * az + ax * ay);
    };
    mat1->SetForceFunction(force);
    MatrixDouble proj(1, 1), val1(1, 1), val2(1, 1);
    proj.setZero();
    val1.setZero();
    val2.setZero();
    L2Projection* bc_linha = new L2Projection(0, 2, proj, val1, val2);
    L2Projection* bc_point = new L2Projection(0, 3, proj, val1, val2);
    std::vector<MathStatement*> mathvec = { 0,mat1,bc_point,bc_linha };
    cmesh.SetMathVec(mathvec);
    cmesh.SetDefaultOrder(2);
    cmesh.AutoBuild();
    cmesh.Resequence();



    Analysis locAnalysis(&cmesh);
    locAnalysis.RunSimulation();
    PostProcessTemplate<Poisson> postprocess;
    auto exact = [](const VecDouble& x, VecDouble& val, MatrixDouble& deriv)
    {
        double ax, ay, az;
        ax = (1 - x[0]) * x[0];
        ay = (1 - x[1]) * x[1];
        az = (1 - x[2]) * x[2];
        val[0] = ax * ay * az;
        deriv(0, 0) = (1. - 2. * x[0]) * ay * az;
        deriv(1, 0) = (1 - 2. * x[1]) * ax * az;
        deriv(2, 0) = (1 - 2. * x[2]) * ax * ay;
    };

    postprocess.AppendVariable("Sol");
    postprocess.AppendVariable("DSol");
    postprocess.AppendVariable("Flux");
    postprocess.AppendVariable("Force");
    postprocess.AppendVariable("SolExact");
    postprocess.AppendVariable("DSolExact");
    postprocess.SetExact(exact);
    mat1->SetExactSolution(exact);
    locAnalysis.PostProcessSolution("cube3D.vtk", postprocess);

    VecDouble errvec;
    errvec = locAnalysis.PostProcessError(std::cout, postprocess);


    return 0;
}


