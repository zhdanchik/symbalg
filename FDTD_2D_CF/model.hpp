#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct cell{
    double Ey;
    double Bx;
    double Bz;
};
class Model{
public:
    double A;
    double epsilon;
    double Omega;
    double mu;
    double dz;
    double dx;
    double time;
    double Y;
    double h;
    aiv::array<cell, 2> data;
    void start(aiv::indx<2> offset);
    void calc_cone_1(double init_time,aiv::indx<2> offset);
    void calc_cone_0(double init_time,aiv::indx<2> offset);
};
#endif