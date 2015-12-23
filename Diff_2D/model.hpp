#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct cell{
    double g;
    double f;
};
class Model{
public:
    double h;
    aiv::array<cell, 2> data;
    double D;
    double dx;
    double dy;
    void start(aiv::indx<2> offset);
    void start_delta(aiv::indx<2> offset);
    void calc_cone_1(double init_time,aiv::indx<2> offset);
};
#endif