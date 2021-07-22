//
//  IntRule.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef __DATATYPES__
#define __DATATYPES__

///\cond
#include <cmath>
#include <stdio.h>
#include <vector>
#include <functional>
#include <Eigen/Dense>
///\endcond
#include "tpanic.h"

using namespace Eigen;

typedef Eigen::MatrixXd MatrixDouble ;
//typedef Eigen::VectorXi VecInt;
typedef Eigen::Matrix<int64_t, Dynamic, 1> VecInt;
typedef Eigen::VectorXd VecDouble;


enum MElementType
{
    /*0*/    EPoint,
    /*1*/    EOned,
    /*2*/    ETriangle,
    /*3*/    EQuadrilateral,
    /*4*/    ETetraedro,
    /*5*/    EPiramide,
    /*6*/    EPrisma,
    /*7*/    ECube
};

#endif /* defined(__FemSC__DATATYPES__) */
