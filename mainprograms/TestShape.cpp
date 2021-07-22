

///\cond
#include <iostream>
#include <math.h>
///\endcond
#include "Geom0d.h"
#include "Geom1d.h"
#include "GeomQuad.h"
#include "GeomTriangle.h"
#include "GeomTetrahedron.h"
#include "Shape0d.h"
#include "Shape1d.h"
#include "ShapeQuad.h"
#include "ShapeTriangle.h"
#include "ShapeTetrahedron.h"
#include "GeoElementTemplate.h"
#include "GeoMesh.h"
#include "CompMesh.h"
#include "CompElement.h"
#include "NullStatement.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace Catch::literals;


using std::cout;
using std::endl;
using std::cin;

static void MasterCo(MElementType elt, MatrixDouble& cornerco)
{
    switch (elt) {
    case EPoint:
        cornerco.resize(0, 1);
        break;
    case EOned:
        cornerco.resize(1, 2);
        cornerco(0, 0) = -1.;
        cornerco(0, 1) = 1.;
        break;
    case ETriangle:
        cornerco.resize(2, 3);
        cornerco(0, 0) = 0.;
        cornerco(1, 0) = 0.;
        cornerco(0, 1) = 1.;
        cornerco(1, 1) = 0.;
        cornerco(0, 2) = 0.;
        cornerco(1, 2) = 1.;
        break;
    case EQuadrilateral:
        cornerco.resize(2, 4);
        cornerco(0, 0) = -1.;
        cornerco(1, 0) = -1.;
        cornerco(0, 1) = 1.;
        cornerco(1, 1) = -1.;
        cornerco(0, 2) = 1.;
        cornerco(1, 2) = 1.;
        cornerco(0, 3) = -1.;
        cornerco(1, 3) = 1.;
        break;
    case ETetraedro:
        cornerco.resize(3, 4);
        cornerco(0, 0) = 0.;
        cornerco(1, 0) = 0.;
        cornerco(2, 0) = 0.;
        cornerco(0, 1) = 1.;
        cornerco(1, 1) = 0.;
        cornerco(2, 1) = 0.;
        cornerco(0, 2) = 0.;
        cornerco(1, 2) = 1.;
        cornerco(2, 2) = 0.;
        cornerco(0, 3) = 0.;
        cornerco(1, 3) = 0.;
        cornerco(2, 3) = 1.;
        break;
    default:
        DebugStop();
        break;
    }
}

static std::unique_ptr<IntRule> GetRule(MElementType eltype)
{
    std::unique_ptr<IntRule> rule;
    switch (eltype) {
    case EPoint:
        rule = std::make_unique<IntRule0d>(0);
        break;
    case EOned:
        rule = std::make_unique<IntRule1d>(2);
        break;
    case EQuadrilateral:
        rule = std::make_unique<IntRuleQuad>(2);
        break;
    case ETriangle:
        rule = std::make_unique<IntRuleTriangle>(2);
        break;
    case ETetraedro:
        rule = std::make_unique<IntRuleTetrahedron>(2);
        break;

    default:
        DebugStop();
        break;
    }
    return rule;
}
//GeoElementTemplate(const VecInt &nodeindices, int materialid, GeoMesh *gmesh, int index);

static void AddElement(MElementType eltype, VecInt& nodes, int index, GeoMesh* gmesh)
{
    int matid = 1;
    switch (eltype)
    {
    case EPoint:
        new GeoElementTemplate<Geom0d>(nodes, matid, gmesh, index);
        return;
    case EOned:
        new GeoElementTemplate<Geom1d>(nodes, matid, gmesh, index);
        break;
    case ETriangle:
        new GeoElementTemplate<GeomTriangle>(nodes, matid, gmesh, index);
        break;
    case EQuadrilateral:
        new GeoElementTemplate<GeomQuad>(nodes, matid, gmesh, index);
        break;
    case ETetraedro:
        new GeoElementTemplate<GeomTetrahedron>(nodes, matid, gmesh, index);
        break;
    default:
        DebugStop();
        break;
    }
}

static GeoMesh* BuildGMesh(MElementType eltype)
{
    GeoMesh* gmesh = new GeoMesh();
    MatrixDouble cornerco;
    MasterCo(eltype, cornerco);
    int nnodes = cornerco.cols();
    int dim = cornerco.rows();
    gmesh->SetNumNodes(nnodes);
    gmesh->SetDimension(dim);
    VecInt nodes(nnodes);
    for (int i = 0; i < nnodes; i++)
    {
        VecDouble co(cornerco.rows());
        for (int ir = 0; ir < cornerco.rows(); ir++) co[ir] = cornerco(ir, i);
        GeoNode& node = gmesh->Node(i);
        node.SetCo(co);
        nodes[i] = i;
    }
    int index = 0;
    AddElement(eltype, nodes, index, gmesh);
    GeoElement* gel = gmesh->Element(0);
    int nsides = gel->NSides();
    for (int is = 0; is < nsides - 1; is++)
    {
        int nsidenodes = gel->NSideNodes(is);
        VecInt sidenodes(nsidenodes);
        for (int i = 0; i < nsidenodes; i++) sidenodes[i] = gel->SideNodeIndex(is, i);
        AddElement(gel->Type(is), sidenodes, is + 1, gmesh);
    }
    gmesh->BuildConnectivity();
    return gmesh;
}

template<class shape>
CompMesh* BuildCompMesh(VecInt& orders)
{
    auto gmesh = BuildGMesh(shape::Type());
    {
        std::ofstream sout("gmesh_tetra.txt");
        gmesh->Print(sout);
    }
    CompMesh* cmesh = new CompMesh(gmesh);
    cmesh->SetDefaultOrder(1);
    int matid = 1;
    NullStatement* null = new NullStatement(matid);
    cmesh->SetMathStatement(matid, null);
    cmesh->AutoBuild();
    int ndof = cmesh->GetNumberDOF();
    if (ndof != shape::nSides)
    {
        DebugStop();
    }
    for (int idf = shape::nCorners; idf < ndof; idf++) {
        int nshape = shape::NShapeFunctions(idf, orders[idf]);
        int nstate = 1;
        cmesh->GetDOF(idf).SetNShapeStateOrder(nshape, nstate, orders[idf]);
    }
    cmesh->Resequence();
    return cmesh;
}


void VerifyShape(CompMesh* cmesh, int side)
{
    CAPTURE(side);
    CompElement* elroot = cmesh->GetElement(0);
    GeoElement* gelroot = elroot->GetGeoElement();
    CompElement* celside = cmesh->GetElement(side + 1);
    GeoElement* gelside = celside->GetGeoElement();
    int dim = cmesh->GetGeoMesh()->Dimension();
    // build the correspondence between the DOF of celside and DOF of root
    // compute the first shape for each DOF
    std::map<int, int> rootDOF;
    int rootndof = elroot->NDOF();
    int sidendof = celside->NDOF();
    VecInt firstshapeRoot(rootndof), firstshapeSide(sidendof);
    firstshapeRoot.setZero();
    firstshapeSide.setZero();
    for (int dof = 0; dof < elroot->NDOF(); dof++)
    {
        int dofindex = elroot->GetDOFIndex(dof);
        rootDOF[dofindex] = dof;
        if (dof < elroot->NDOF() - 1) firstshapeRoot[dof + 1] = firstshapeRoot[dof] + elroot->NShapeFunctions(dof);
    }
    for (int dof = 0; dof < celside->NDOF(); dof++)
    {
        int dofindex = celside->GetDOFIndex(dof);
        if (rootDOF.find(dofindex) == rootDOF.end()) {
            DebugStop();
        }
        if (dof < celside->NDOF() - 1) firstshapeSide[dof + 1] = firstshapeSide[dof] + celside->NShapeFunctions(dof);
    }
    MElementType sidetype = gelroot->Type(side);
    std::unique_ptr<IntRule> intrule = GetRule(sidetype);
    int npoints = intrule->NPoints();
    VecDouble point(intrule->Dimension());
    int root_nshape = elroot->NShapeFunctions();
    int side_nshape = celside->NShapeFunctions();
    VecDouble phiRoot(root_nshape);
    VecDouble phiSide(side_nshape);
    MatrixDouble dphiroot(gelroot->Dimension(), root_nshape);
    MatrixDouble dphiside(gelside->Dimension(), side_nshape);
    double weight;
    for (int ip = 0; ip < npoints; ip++) {
        intrule->Point(ip, point, weight);
        VecDouble qsiroot(dim);
        gelside->X(point, qsiroot);
        elroot->ShapeFunctions(qsiroot, phiRoot, dphiroot);
        celside->ShapeFunctions(point, phiSide, dphiside);
        int ndof = celside->NDOF();
        int count = 0;
        for (int idf = 0; idf < ndof; idf++)
        {
            if (celside->GetDOF(idf).GetNShape() == 0) continue;
            int dofindex = celside->GetDOFIndex(idf);
            int rootlocdof = rootDOF[dofindex];
            int sidepos = firstshapeSide[idf];
            int rootpos = firstshapeRoot[rootlocdof];
            REQUIRE_THAT(phiSide[sidepos], Catch::Matchers::WithinAbs(phiRoot[rootpos], 1.e-8));
        }
    }
}

template<class shape>
void CheckShape(int order)
{
    VecInt orders(shape::nSides, 1);
    for (int is = shape::nCorners; is < shape::nSides; is++) orders[is] = order;
    CompMesh* cmesh = BuildCompMesh<shape>(orders);
    for (int is = 0; is < shape::nSides - 1; is++)
    {
        VerifyShape(cmesh, is);
    }
    auto gmesh = cmesh->GetGeoMesh();
    delete cmesh;
    delete gmesh;
}
TEST_CASE("shape_compare", "[functionspace]")
{

    SECTION("Shape1d")
    {
        CheckShape<Shape1d>(1);
        CheckShape<Shape1d>(2);
    }
    SECTION("ShapeQuad")
    {
        CheckShape<ShapeQuad>(1);
        CheckShape<ShapeQuad>(2);
    }
    SECTION("ShapeTriangle")
    {
        CheckShape<ShapeTriangle>(1);
        CheckShape<ShapeTriangle>(2);
    }
    SECTION("ShapeTetrahedra")
    {
        CheckShape<ShapeTetrahedron>(1);
        CheckShape<ShapeTetrahedron>(2);
    }
}
