#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct cell{
    double B;
    double E;
};
class Model{
public:
    double h;
    aiv::array<cell, 1> data;
    double time;
    double C2;
    double C1;
    double C0;
    double Omega;
    void start(aiv::indx<1> offset);
    void calc_cone_1(double init_time,aiv::indx<1> offset);
};
#endif