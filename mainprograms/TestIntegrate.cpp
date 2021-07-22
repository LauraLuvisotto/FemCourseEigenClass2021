

///\cond
#include <iostream>
#include <math.h>
///\endcond
#include "IntRule1d.h"
#include "IntRuleQuad.h"
#include "IntRuleTriangle.h"
#include "IntRuleTetrahedron.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace Catch::literals;

using std::cout;
using std::endl;
using std::cin;

template<class intrule>
double Function(VecDouble &input, int index, int order);

template<class intrule>
double Integral(int index, int order);

template<class intrule>
double Integrate(int indexFunc, int orderRule)
{
    intrule TestInt1(orderRule);
    VecDouble CoordXi(TestInt1.Dimension());
    int NPoint = TestInt1.NPoints();
    CAPTURE(NPoint);
    double result = 0.;
    for (int i=0; i<NPoint; i++) {
        double weight;
        TestInt1.Point(i, CoordXi, weight);
        result += Function<intrule>(CoordXi,indexFunc, orderRule)*weight;
    }
    return result;
}

template<class intrule>
int NFunc(int order);

template<class intrule>
void GenerateCompareData(int order, std::vector<double> &correct, std::vector<double> &computed)
{
    int nfunc = NFunc<intrule>(order);
    correct.resize(nfunc);
    computed.resize(nfunc);
    for(int index=0; index<nfunc; index++)
    {
        correct[index] = Integral<intrule>(index,order);
        computed[index] = Integrate<intrule>(index, order);
    }

}

TEST_CASE("integrate","[integration]")
{
    auto order = GENERATE(0,1,2,3,4,5);
    //  test1D();
    //  testTriangle();
    //  testQuad();
    
    //Teste 1 - Regra de integração - Tabela de valores;
    
    std::vector<double> computed;
    std::vector<double> correct;
    CAPTURE(order);
    SECTION("IntRule1d")
    {
        GenerateCompareData<IntRule1d>(order, correct, computed);
        for (int i = 0; i< correct.size(); i++) {
            CAPTURE(i);
            REQUIRE_THAT(computed[i], Catch::Matchers::WithinAbs(correct[i],1.e-8));
        }
    }
    SECTION("IntRuleQuad")
    {
        GenerateCompareData<IntRuleQuad>(order, correct, computed);
        for (int i = 0; i< correct.size(); i++) {
            CAPTURE(i);
            REQUIRE_THAT(computed[i], Catch::Matchers::WithinAbs(correct[i],1.e-8));
        }
    }
    SECTION("IntRuleTriangle")
    {
        GenerateCompareData<IntRuleTriangle>(order, correct, computed);
        for (int i = 0; i< correct.size(); i++) {
            CAPTURE(i);
            REQUIRE_THAT(computed[i], Catch::Matchers::WithinAbs(correct[i],1.e-8));
        }
    }
    SECTION("IntRuleTetrahedron")
    {
        GenerateCompareData<IntRuleTetrahedron>(order, correct, computed);
        for (int i = 0; i< correct.size(); i++) {
            CAPTURE(i);
            REQUIRE_THAT(computed[i], Catch::Matchers::WithinAbs(correct[i],1.e-8));
        }
    }
}

template<class intrule>
void TestOutofBounds()
{
    PanicMessage = false;
    int maxorder = intrule::gMaxOrder();
    int order = -1;
    intrule loc;
    CAPTURE(order);
    REQUIRE_THROWS(intrule(order));
    REQUIRE_THROWS(loc.SetOrder(order));
    order = maxorder+1;
    CAPTURE(order);
    REQUIRE_THROWS(intrule(order));
    REQUIRE_THROWS(loc.SetOrder(order));
    
    PanicMessage = true;

}
TEST_CASE("integration_rule_out_of_range","[integration]")
{
    SECTION("IntRule1d")
    {
        TestOutofBounds<IntRule1d>();
    }
    SECTION("IntRuleQuad")
    {
        TestOutofBounds<IntRuleQuad>();
    }
    SECTION("IntRuleTriangle")
    {
        TestOutofBounds<IntRuleTriangle>();
    }
    SECTION("IntRuleTetrahedron")
    {
        TestOutofBounds<IntRuleTetrahedron>();
    }
}

template<>
int NFunc<IntRule1d>(int order)
{
    return order+1;
}

template<>
double Function<IntRule1d>(VecDouble &input, int index, int order)
{
    return std::pow(input[0], index);
}

template<>
double Integral<IntRule1d>(int index, int order)
{
    if(index%2 != 0) return 0.;
    return 2./(index+1.);
}

template<>
int NFunc<IntRuleQuad>(int order)
{
    return (order+1)*(order+1);
}

template<>
double Function<IntRuleQuad>(VecDouble &input, int index, int order)
{
    int orderx = index /(order+1);
    int ordery = index %(order+1);
    double x = std::pow(input[0], orderx);
    double y = std::pow(input[1], ordery);
    return x*y;

}

template<>
double Integral<IntRuleQuad>(int index, int order)
{
    int orderx = index /(order+1);
    int ordery = index %(order+1);
    double intx;
    if(orderx%2 != 0) return intx = 0;
    else intx = 2./(orderx+1.);
    double inty;
    if(ordery%2 != 0) return inty = 0;
    else inty = 2./(ordery+1.);
    return intx*inty;
}

template<>
int NFunc<IntRuleTriangle>(int order)
{
    return (order+1)*(order+2)/2;
}

template<>
int NFunc<IntRuleTetrahedron>(int order)
{
    int res = 0;
    for(int i=0; i<=order; i++) res+= NFunc<IntRuleTriangle>(i);
    return res;
}

std::pair<int,int> Indexy(int index,int order)
{
    int orderx = 0;
    int ordery = 0;
    int counter = 0;
    int incr = order;
    while (index > counter+incr && incr > 0) {
        counter += incr+1;
        orderx++;
        incr--;
    }
    ordery = index-counter;
    return std::pair<int,int>(orderx,ordery);
}

std::tuple<int,int,int> Indexyz(int index,int order)
{
    int orderx = 0;
    int ordery = 0;
    int counter = 0;
    int corder = order;
    int incr = NFunc<IntRuleTriangle>(corder);
    int orderz = 0;
    while (index >= counter+incr && incr > 0) {
        counter += incr;
        orderz++;
        corder--;
        incr =NFunc<IntRuleTriangle>(corder);
    }
    auto orderxy = Indexy(index-counter, corder);
    if(orderxy.first<0 || orderxy.second < 0 || orderz < 0)
    {
        DebugStop();
    }
    if(orderxy.first+orderxy.second+orderz > order)
    {
        DebugStop();
    }
    return std::tuple<int,int,int>(orderxy.first,orderxy.second,orderz);
}


template<>
double Function<IntRuleTriangle>(VecDouble &input, int index, int order)
{
    auto ordxy = Indexy(index,order);
    double x = std::pow(input[0], ordxy.first);
    double y = std::pow(input[1], ordxy.second);
    return x*y;

}

template<>
double Integral<IntRuleTriangle>(int index, int order)
{
    auto ordxy = Indexy(index,order);
    int orderx = ordxy.first;
    int ordery = ordxy.second;
    
    return std::tgamma(orderx+1.)*std::tgamma(ordery+1.)/std::tgamma(3.+orderx+ordery);
}

template<>
double Function<IntRuleTetrahedron>(VecDouble &input, int index, int order)
{
    auto ordxyz = Indexyz(index,order);
    double x = std::pow(input[0], std::get<0>(ordxyz));
    double y = std::pow(input[1], std::get<1>(ordxyz));
    double z = std::pow(input[2], std::get<2>(ordxyz));
    return x*y*z;

}

template<>
double Integral<IntRuleTetrahedron>(int index, int order)
{
    auto ordxy = Indexyz(index,order);
    int orderx = std::get<0>(ordxy);
    int ordery = std::get<1>(ordxy);
    int orderz = std::get<2>(ordxy);
    return std::tgamma(orderx+1.)*std::tgamma(ordery+1.)*std::tgamma(orderz+1.)/std::tgamma(4.+orderx+ordery+orderz);
}

