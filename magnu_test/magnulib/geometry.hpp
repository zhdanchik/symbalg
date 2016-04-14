#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <aivlib/vectorD.hpp>
using namespace aiv;

//------------------------------------------------------------------------------
struct BaseFigure{
	virtual vctr<3> get_center() const = 0;
	virtual double get_max_size() const = 0;
	virtual bool leak_check(const aiv::vctr<3> &r, double delta) const = 0;
	virtual bool check(const aiv::vctr<3> &r) const = 0;
	virtual bool cutcheck(const aiv::vctr<3> &r, int i) const = 0;
};
//------------------------------------------------------------------------------
struct Cylinder: public BaseFigure{
	vctr<3> center; // центр нижней грани
	double R, H;    // радиус и высота
	vctr<3> rmin, rmax;
	bool cut;

	vctr<3> get_center() const { return center+vctr<3>(0, 0, .5*H); }
	virtual double get_max_size() const { return 2*sqrt(.25*H*H+R*R); }

	bool leak_check(const aiv::vctr<3> &r, double delta) const {
		return center[2]-delta<=r[2] && r[2]<=center[2]+H+delta && ((r^2)-(center^2)).abs()<=R+delta;		
	}
	bool check(const aiv::vctr<3> &r) const {
		return center[2]<=r[2] && r[2]<=center[2]+H && ((r^2)-(center^2)).abs()<=R;
	}
	bool cutcheck(const aiv::vctr<3> &r, int i) const {
		if(cut) return rmin[i]<=r[i] && r[i]<=rmax[i];
		else{return true;}
	}

};
//------------------------------------------------------------------------------
struct Cube: public BaseFigure{
	vctr<3> center; // центр нижней грани
	double A;    // радиус и высота
	vctr<3> rmin, rmax;
	bool cut;

	vctr<3> get_center() const { return center+vctr<3>(0, 0, .5*A); }
	virtual double get_max_size() const { return 0.5*sqrt(3)*A; }

	bool leak_check(const aiv::vctr<3> &r, double delta) const {
		return center[2]-delta<=r[2] && r[2]<=center[2]+A+delta && center[1]-delta-A*0.5<=r[1] && r[1]<=center[1]+A*0.5+delta && center[0]-delta-A*0.5<=r[0] && r[0]<=center[0]+A*0.5+delta;		
	}
	bool check(const aiv::vctr<3> &r) const {
		return center[2]<=r[2] && r[2]<=center[2]+A && center[1]-A*0.5<=r[1] && r[1]<=center[1]+A*0.5 && center[0]-A*0.5<=r[0] && r[0]<=center[0]+A*0.5;
	}
	bool cutcheck(const aiv::vctr<3> &r, int i) const {
		if(cut) return rmin[i]<=r[i] && r[i]<=rmax[i];
		else{return true;}	}

};
//------------------------------------------------------------------------------
struct Box: public BaseFigure{
	vctr<3> center; // центр нижней грани
	double L, H;    // радиус и высота
	vctr<3> rmin, rmax;
	bool cut;
	
	vctr<3> get_center() const { return center+vctr<3>(0, 0, .5*H); }
	virtual double get_max_size() const { return sqrt(H*H+2*L*L); }

	bool leak_check(const aiv::vctr<3> &r, double delta) const {
		return center[2]-delta<=r[2] && r[2]<=center[2]+H+delta && center[1]-delta-L*0.5<=r[1] && r[1]<=center[1]+L*0.5+delta && center[0]-delta-L*0.5<=r[0] && r[0]<=center[0]+L*0.5+delta;		
	}
	bool check(const aiv::vctr<3> &r) const {
		return center[2]<=r[2] && r[2]<=center[2]+H && center[1]-L*0.5<=r[1] && r[1]<=center[1]+L*0.5 && center[0]-L*0.5<=r[0] && r[0]<=center[0]+L*0.5;
	}
	
	bool cutcheck(const aiv::vctr<3> &r, int i) const {
		if(cut) return rmin[i]<=r[i] && r[i]<=rmax[i];
		else{return true;}	}	
};

//------------------------------------------------------------------------------
#endif //GEOMETRY_HPP
