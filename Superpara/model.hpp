#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <aivlib/sphereT.hpp>
#include <math.h>
#include <stdio.h>
using namespace aiv;
struct part{
    aiv::vctr<3> m;
};
class Model{
public:
    aiv::vctr<3> A;
    aiv::vctr<3> k;
    aiv::array<part, 1> partarr;
    double rand_alpha2PI;
    double abs;
    double T;
    double time;
    double alpha;
    double dt;
    double One;
    double Omega;
    aiv::vctr<3> Hext;
    double gamma;
    aiv::sphere<float> f;
    aiv::vctr<3> M1;
    aiv::vctr<3> M2;
    void calc();
    void means();
    void start();
};
#endif