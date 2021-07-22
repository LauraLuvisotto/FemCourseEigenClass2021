

#include <iostream>
#include <chrono>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main ()
{
    VectorXd vec1;

    // Testing Eigen matrix
    // Copied from: https://gitlab.com/libeigen/eigen/-/blob/master/doc/examples/QuickStart_example.cpp 

    auto tsim1 = std::chrono::high_resolution_clock::now();
    
    MatrixXd m(2,2); // matrix composed by doubles.
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << m << endl;

    VectorXd v(2);
    v(0) = 4;
    v(1) = v(0) - 1;
    cout << "Here is the vector v:\n" << v << endl;

    cout << "Here is the vector v:\n" << v << endl;

    auto tsim2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time = tsim2 - tsim1;
    cout << "measure time: " << elapsed_time.count() << endl;
  
    return 0;
}