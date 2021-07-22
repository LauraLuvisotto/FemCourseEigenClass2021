/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Assemble.h"
#include "CompMesh.h"
#include "GeoMesh.h"
#include "MathStatement.h"
#include "CompElement.h"



Assemble::Assemble() {
}

Assemble::Assemble(CompMesh* mesh) {
    cmesh = mesh;
}

Assemble::Assemble(const Assemble& copy) {
    cmesh = copy.cmesh;
}

Assemble& Assemble::operator=(const Assemble& copy) {
    cmesh = copy.cmesh;
    return *this;
}

void Assemble::SetMesh(CompMesh* mesh) {
    cmesh = mesh;
}

int64_t Assemble::NEquations() {
    int64_t neq = 0;
    int64_t i, ncon = cmesh->GetDOFVec().size();
    for (i = 0; i < ncon; i++) {
        DOF dof = cmesh->GetDOF(i);
        int64_t dofsize = dof.GetNShape() * dof.GetNState();
        neq += dofsize;
    }
    return neq;
}

void Assemble::OptimizeBandwidth() {
}

void Assemble::Compute(MatrixDouble& globmat, MatrixDouble& rhs) {

    auto neq = NEquations();

    globmat.resize(neq, neq);
    globmat.setZero();
    rhs.resize(neq, 1);
    rhs.setZero();

    int64_t nelem = cmesh->GetGeoMesh()->NumElements();
    for (int el = 0; el < nelem; el++) {
        CompElement* cel = cmesh->GetElement(el);

        int nshape = cel->NShapeFunctions();
        int nstate = cel->GetStatement()->NState();
        MatrixDouble ek(nstate * nshape, nstate * nshape);
        MatrixDouble ef(nstate * nshape, 1);
        ek.setZero();
        ef.setZero();

        cel->CalcStiff(ek, ef);

        auto ndof = cel->NDOF();
        VecInt iglob(ndof);
        int ni = 0;
        for (auto i = 0; i < ndof; i++) {
            auto dofindex = cel->GetDOFIndex(i);
            const DOF& dof = cmesh->GetDOF(dofindex);
            for (auto j = 0; j < dof.GetNShape() * dof.GetNState(); j++) {
                iglob[ni] = dof.GetFirstEquation() + j;
                ni++;
            }

        }

        for (auto i = 0; i < ek.rows(); i++) {
            auto IG = iglob[i];
            rhs(IG, 0) += ef(i, 0);

            for (auto j = 0; j < ek.rows(); j++) {
                auto JG = iglob[j];
                globmat(IG, JG) += ek(i, j);
            }
        }

    }
}
