#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct cell{
    double Bx;
    double Ey;
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
    double h;
    aiv::array<cell, 2> data;
    void start1(aiv::indx<2> offset);
    void start(aiv::indx<2> offset);
    void calc_cone_all(double init_time,aiv::indx<2> offset);
};
#endif