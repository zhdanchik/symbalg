#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <aivlib/vectorD.hpp>
#include <vector>
#include <algorithm>
using namespace aiv;

//https://en.wikipedia.org/wiki/Constructive_solid_geometry

struct GlobalTrans{
    vctr<3> I1,I2,I3;

    GlobalTrans(){}
    GlobalTrans(vctr<3> i1, vctr<3> i2, vctr<3> i3): I1(i1), I2(i2), I3(i3) {}

    vctr<3> trans_vec (const aiv::vctr<3> &r){
        if (fabs(I1 * (I2%%I3)) <1e-16){raise("Transformation is incorrect");}
        double x = r[0], y = r[1], z = r[2];
        double x1 = I1[0], x2 = I2[0], x3 = I3[0];
        double y1 = I1[1], y2 = I2[1], y3 = I3[1];
        double z1 = I1[2], z2 = I2[2], z3 = I3[2];
        return Vctr( ((x3*y2 - x2*y3)*z - (x3*y - x*y3)*z2 + (x2*y - x*y2)*z3),
                    -((x3*y1 - x1*y3)*z - (x3*y - x*y3)*z1 + (x1*y - x*y1)*z3),
                     ((x2*y1 - x1*y2)*z - (x2*y - x*y2)*z1 + (x1*y - x*y1)*z2) ) / ((x3*y2 - x2*y3)*z1 - (x3*y1 - x1*y3)*z2 + (x2*y1 - x1*y2)*z3);
    }
    vctr<3> trans_vec_back (const aiv::vctr<3> &r){
        if (fabs(I1 * (I2%%I3)) <1e-16){raise("Transformation is incorrect");}
        double x = r[0], y = r[1], z = r[2];
        double x1 = I1[0], x2 = I2[0], x3 = I3[0];
        double y1 = I1[1], y2 = I2[1], y3 = I3[1];
        double z1 = I1[2], z2 = I2[2], z3 = I3[2];

        return Vctr(x*x1 + x2*y + x3*z,
                    x*y1 + y*y2 + y3*z,
                    x*z1 + y*z2 + z*z3);
    }
};

inline vctr<3> internal_trans_vec(const aiv::vctr<3> &r, const aiv::vctr<3> &center, const aiv::vctr<3> &updirect){
    if (updirect.abs() <1e-16) {raise("Transformation is incorrect");}
    vctr<3> r0 = r-center;
    double a = updirect[0];
    double b = updirect[1];
    double c = updirect[2];
    if ((fabs(a)>1e-16)||(fabs(b)>1e-16)){
        r0 = rotate(Vctr(-b, a, 0)/sqrt(a*a+b*b),acos(c/sqrt(a*a+b*b+c*c)) ,r0);
    }
    return r0;
}

inline vctr<3> internal_trans_vec_back(const aiv::vctr<3> &r, const aiv::vctr<3> &center, const aiv::vctr<3> &updirect){
    if (updirect.abs() <1e-16) {raise("Transformation is incorrect");}
    vctr<3> r0 = r;
    double a = updirect[0];
    double b = updirect[1];
    double c = updirect[2];
    if ((fabs(a)>1e-16)||(fabs(b)>1e-16)){
        r0 = rotate(Vctr(-b, a, 0)/sqrt(a*a+b*b),-acos(c/sqrt(a*a+b*b+c*c)) ,r0);
    }
    r0 = r+center;
    return r0;
}

struct BaseFigure{
    virtual vctr<3> get_minxyz() const = 0;
    virtual vctr<3> get_maxxyz() const = 0;
    virtual bool check(const aiv::vctr<3> &r) const = 0;
};

struct Cylinder: public BaseFigure{
    vctr<3> center; // центр нижней грани
    double R, H;    // радиус и высота
    vctr<3> updirect; // направляющая вдоль оси z
    vctr<3> get_minxyz() const { return center - Vctr(R,R,0);}
    vctr<3> get_maxxyz() const { return center + Vctr(R,R,H);}
    bool check(const aiv::vctr<3> &r) const {
        vctr<3> r0 = internal_trans_vec(r, center, updirect);
        return fabs(r0[2]-H*0.5)<=H*0.5 && (r0^2).abs()<=R;
    }
    Cylinder(){}
    Cylinder(vctr<3> c, double r, double h, vctr<3> u): center(c), R(r), H(h), updirect(u) {}
};

struct Cube: public BaseFigure{
    vctr<3> center; // центр нижней грани
    double A;    // длина ребра
    vctr<3> updirect; // направляющая вдоль оси z
    vctr<3> get_minxyz() const { return center - Vctr(0.5*A,0.5*A,0);}
    vctr<3> get_maxxyz() const { return center + Vctr(0.5*A,0.5*A,A);}
    bool check(const aiv::vctr<3> &r) const {
        vctr<3> r0 = internal_trans_vec(r, center, updirect);
        return fabs(r0[2]-A*0.5)<=A*0.5 && fabs(r0[1])<=A*0.5 && fabs(r0[0])<=A*0.5;
    }   
    Cube(){}
    Cube(vctr<3> c, double a, vctr<3> u): center(c), A(a), updirect(u) {}
};

struct Box: public BaseFigure{
    vctr<3> center; // центр нижней грани
    double A, B, H;    // длина ребер основания и высота
    vctr<3> updirect; // направляющая вдоль оси z
    vctr<3> get_minxyz() const { return center - Vctr(0.5*A,0.5*B,0);}
    vctr<3> get_maxxyz() const { return center + Vctr(0.5*A,0.5*B,H);}
    bool check(const aiv::vctr<3> &r) const {
        vctr<3> r0 = internal_trans_vec(r, center, updirect);
        return fabs(r0[2]-H*0.5)<=H*0.5 && fabs(r0[1])<=B*0.5 && fabs(r0[0])<=A*0.5;
    }
    Box(){}
    Box(vctr<3> c, double a, double b, double h, vctr<3> u): center(c), A(a), B(b), H(h), updirect(u) {}
};

struct SetFigures: public BaseFigure{
    std::vector<BaseFigure*> Figures;
    void add(BaseFigure *figure){Figures.push_back(figure);}

    vctr<3> get_minxyz() const{
        if (Figures.empty()) raise("Figures is empty!\n");
        vctr<3> tmpminxyz = Figures[0]->get_minxyz();
        for(auto A=Figures.begin(); A!=Figures.end(); ++A){ 
            vctr<3> tmpxyz = (*A)->get_minxyz();
            tmpminxyz[0] = std::min(tmpminxyz[0], tmpxyz[0]);
            tmpminxyz[1] = std::min(tmpminxyz[1], tmpxyz[1]);
            tmpminxyz[2] = std::min(tmpminxyz[2], tmpxyz[2]);
        }
        return tmpminxyz;
    }

    vctr<3> get_maxxyz() const{
        if (Figures.empty()) raise("Figures is empty!\n");
        vctr<3> tmpmaxxyz = Figures[0]->get_maxxyz();
        for(auto A=Figures.begin(); A!=Figures.end(); ++A){ 
            vctr<3> tmpxyz = (*A)->get_maxxyz();
            tmpmaxxyz[0] = std::max(tmpmaxxyz[0], tmpxyz[0]);
            tmpmaxxyz[1] = std::max(tmpmaxxyz[1], tmpxyz[1]);
            tmpmaxxyz[2] = std::max(tmpmaxxyz[2], tmpxyz[2]);
        }
        return tmpmaxxyz;
    }

    // vctr<3> get_center() const {
    //     if (Figures.empty()) raise("Figures is empty!\n");
    //     return (get_maxxyz()+get_minxyz())*0.5;
    // };
    // double get_max_size() const {
    //     if (Figures.empty()) raise("Figures is empty!\n");
    //     vctr<3> minxyz = get_minxyz();
    //     vctr<3> maxxyz = get_maxxyz();

    //     return 0.5*sqrt((maxxyz[0]-minxyz[0])*(maxxyz[0]-minxyz[0]) + (maxxyz[1]-minxyz[1])*(maxxyz[1]-minxyz[1]) + (maxxyz[2]-minxyz[2])*(maxxyz[2]-minxyz[2]));
    // };

    bool check(const aiv::vctr<3> &r) const {
        if (Figures.empty()) raise("Figures is empty!\n");
        for(auto A=Figures.begin(); A!=Figures.end(); ++A){ 
            if (((*A)->check(r))) return true;
        }
        return false;
    }
    // ~SetFigures(){
    //     for(auto A=Figures.begin(); A!=Figures.end(); ++A){ 
    //         delete (*A); // ?????????////
    //     }
    // }
};
/*
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
*/
//------------------------------------------------------------------------------
#endif //GEOMETRY_HPP
