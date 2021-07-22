

#include <cmath>
#include <math.h>
///\endcond
#include "Shape1d.h"

void Shape1d::Shape(const VecDouble& xi, VecInt& orders, VecDouble& phi, MatrixDouble& dphi) {

    if (orders[0] < 0 || orders[1] < 0 || orders[2] < 0) {
        std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
    }
    if (orders[0] > 1 || orders[1] > 1) {
        std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
    }
    if (orders[2] > 2) {
        std::cout << "Shape1d::Shape: Please implement it for order > 2\n";
        DebugStop();
    }

    auto nshape = NShapeFunctions(orders);

    phi.resize(nshape);
    dphi.resize(1, nshape);

    double qsi = xi[0];

    phi[0] = (1. - qsi) / 2.;
    phi[1] = (1. + qsi) / 2.;
    dphi(0, 0) = -1. / 2.;
    dphi(0, 1) = 1. / 2.;

    int is = 2;

    if (orders[is] == 2) {
        int is1 = 0;
        int is2 = 1;

        phi[2] = 4. * phi[is1] * phi[is2];
        dphi(0, 2) = 4. * (dphi(0, is1) * phi[is2] + phi[is1] * dphi(0, is2));
    }

    else if (orders[is] != 1) DebugStop();

}



/// returns the number of shape functions associated with a side
int Shape1d::NShapeFunctions(int side, int order) {

    if (order < 1 || order >2) DebugStop();
    switch (side)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return order - 1;
        break;

    default:
        std::cout << "Shape1d::NShapeFunctions : Wrong side " << side << "\n";
        DebugStop();
        return -1;
        break;
    }
    return -1;
}

/// returns the total number of shape functions
int Shape1d::NShapeFunctions(VecInt& orders) {

    int nsf_tot = 0;
    for (int is = 0; is < 3; is++) {
        nsf_tot += NShapeFunctions(is, orders[is]);
    }

    return nsf_tot;
}
