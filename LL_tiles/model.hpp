#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct Base_cell {
};
struct cell0 : public Base_cell{
public:
	 aiv::vctr<3,double> m;
	 aiv::vctr<3,double> H;
};
struct cell1 : public Base_cell{
public:
	 aiv::vctr<3,double> m;
	 aiv::vctr<3,double> m1;
	 aiv::vctr<3,double> H;
	 aiv::vctr<3,double> H1;
};
typedef Base_cell* pcell;
class Base_tile {
public:
	typedef Base_tile* ptile;
	 aiv::array<pcell,3> tile_data;
	virtual void start() = 0;
	virtual void step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp) = 0;
	virtual void step_m() = 0;
};
class tile0 : public Base_tile{
public:
	 void start();
	 void step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp);
	 void step_m();
};
class tile1 : public Base_tile{
public:
	 void start();
	 void step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp);
	 void step_m();
};
class tile2 : public Base_tile{
public:
	 void start();
	 void step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp);
	 void step_m();
};
typedef Base_tile* ptile;
#endif