#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <aivlib/sphereT.hpp>
#include <math.h>
#include <stdio.h>
using namespace aiv;
struct part{
    double Vx;
    double X;
};
class Model{
public:
    double A;
    double a;
    double b;
    aiv::array<part, 1> partarr;
    double T;
    double time;
    double dt;
    double Omega;
    double gamma;
    double M4X;
    double M2X;
    aiv::mesh<double,2> f;
    double M2V;
    double M1V;
    double M1X;
    void calc();
    void means();
    void start();
};
#endif