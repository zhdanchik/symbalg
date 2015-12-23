#include "model.hpp"
void Model::start(aiv::indx<2> offset){
    auto data_crop = data.crop( offset, data.N, Indx(1,1));
    double X = offset[0];
    double Y = offset[1];
    data_crop[Indx(0,0)].Bx = 0;
    data_crop[Indx(0,0)].Bz = 0;
    data_crop[Indx(0,0)].Ey = 0;
}
void Model::calc_cone_1(double init_time,aiv::indx<2> offset){
    double time = init_time;
    auto data_crop = data.crop( offset, data.N, Indx(1,1));
    double X = offset[0];
    double Y = offset[1];
    data_crop[Indx(2,1)].Ey = data_crop[Indx(2,1)].Ey+h/epsilon*((data_crop[Indx(2,1)].Bx-data_crop[Indx(2,0)].Bx)/dz-(data_crop[Indx(2,1)].Bz-data_crop[Indx(1,1)].Bz)/dx);
    data_crop[Indx(2,1)].Bx = data_crop[Indx(2,1)].Bx+h/(mu*dz)*(data_crop[Indx(2,2)].Ey-data_crop[Indx(2,1)].Ey);
    data_crop[Indx(2,1)].Bz = data_crop[Indx(2,1)].Bz-h/(mu*dx)*(data_crop[Indx(3,1)].Ey-data_crop[Indx(2,1)].Ey);
}
void Model::calc_cone_0(double init_time,aiv::indx<2> offset){
    double time = init_time;
    auto data_crop = data.crop( offset, data.N, Indx(1,1));
    double X = offset[0];
    double Y = offset[1];
    data_crop[Indx(1,1)].Ey = data_crop[Indx(1,1)].Ey+h/epsilon*((data_crop[Indx(1,1)].Bx-data_crop[Indx(1,0)].Bx)/dz-(data_crop[Indx(1,1)].Bz-((1+Y==24)?(A*sin(Omega*time)):(0)))/dx);
    data_crop[Indx(1,1)].Bx = data_crop[Indx(1,1)].Bx+h/(mu*dz)*(data_crop[Indx(1,2)].Ey-data_crop[Indx(1,1)].Ey);
    data_crop[Indx(1,1)].Bz = data_crop[Indx(1,1)].Bz-h/(mu*dx)*(data_crop[Indx(2,1)].Ey-data_crop[Indx(1,1)].Ey);
}