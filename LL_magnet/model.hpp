#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct cell{
    aiv::vctr<3> H;
    aiv::vctr<3> m;
};
class Model{
public:
    double h;
    double J;
    aiv::vctr<3> Init_m;
    aiv::vctr<3> H_ext;
    double alpha;
    aiv::array<cell, 3> data;
    double gamma;
    aiv::vctr<3> M1m;
    void start(aiv::indx<3> offset);
    void calc_means();
    void calc_cone_all(double init_time,aiv::indx<3> offset);
};
#endif