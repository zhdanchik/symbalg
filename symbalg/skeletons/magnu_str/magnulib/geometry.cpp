#include "new_geometry.hpp"

struct RotatedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> center;
    aiv::vctr<3> n_phi;

    virtual vctr<3> get_min() const {};
    virtual vctr<3> get_max() const {};
    virtual bool check(const aiv::vctr<3> &r) const {};
};
struct TransformedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> ox;
    aiv::vctr<3> oy;
    aiv::vctr<3> oz;

    virtual vctr<3> get_min() const {};
    virtual vctr<3> get_max() const {};
    virtual bool check(const aiv::vctr<3> &r) const {};
};
struct MovedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> offset;

    virtual vctr<3> get_min() const {};
    virtual vctr<3> get_max() const {};
    virtual bool check(const aiv::vctr<3> &r) const {};
};

Figure Figure::rotate(const aiv::vctr<3> &center, const aiv::vctr<3> &n_phi){
    RotatedFigure *f = new RotatedFigure; 
    f->child = figure; f->center = center; f->n_phi = n_phi;
    Figure res; res.figure.reset(f); return res;
}
Figure Figure::transform(const aiv::vctr<3> &ox, const aiv::vctr<3> &oy, const aiv::vctr<3> &oz){
    TransformedFigure *f = new TransformedFigure; 
    f->child = figure; f->ox = ox; f->oy = oy; f->oz = oz;
    Figure res; res.figure.reset(f); return res;
}
Figure Figure::move(const aiv::vctr<3> &offset){
    MovedFigure *f = new MovedFigure; 
    f->child = figure; f->offset = offset;
    Figure res; res.figure.reset(f); return res;
}


struct UnionFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
    virtual vctr<3> get_min() const { return lchild->get_min() << rchild->get_min(); };
    virtual vctr<3> get_max() const { return lchild->get_max() >> rchild->get_max(); };
    virtual bool check(const aiv::vctr<3> &r) const { return lchild->check(r) && rchild->check(r); };
};
struct IntersectFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
    virtual vctr<3> get_min() const { return lchild->get_min() >> rchild->get_min(); };
    virtual vctr<3> get_max() const { return lchild->get_max() << rchild->get_max(); };
    virtual bool check(const aiv::vctr<3> &r) const { return lchild->check(r) || rchild->check(r); };
};
struct ExcludeFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
    virtual vctr<3> get_min() const { return lchild->get_min(); }; // вот тут можно и по-точнее
    virtual vctr<3> get_max() const { return lchild->get_max(); }; // вот тут можно и по-точнее
    virtual bool check(const aiv::vctr<3> &r) const { return lchild->check(r) && !rchild->check(r); };
};

Figure Figure::operator + (const Figure &other) const{
    UnionFigure *f = new UnionFigure;
    f->lchild = figure; f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};
Figure Figure::operator - (const Figure &other) const{
    IntersectFigure *f = new IntersectFigure;
    f->lchild = figure; f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};
Figure Figure::operator * (const Figure &other) const{
    ExcludeFigure *f = new ExcludeFigure;
    f->lchild = figure; f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};


vctr<3> rotmov(const aiv::vctr<3> &r, const aiv::vctr<3> &center, const aiv::vctr<3> &n, double phi){
    if (n.abs() < 1e-16) {raise("Transformation is incorrect");}
    vctr<3> r0 = r-center;
    if ((n^2).abs() > 1e-16){ r0 = rotate(Vctr(-n[1], n[0], 0), acos(n[2]/n.abs()), r0); }
    if (phi > 1e-16){ r0 = rotate(n, phi, r0); }
    return r0;
}

vctr<3> rotmov_back(const aiv::vctr<3> &r, const aiv::vctr<3> &center, const aiv::vctr<3> &n, double phi){
    if (n.abs() < 1e-16) {raise("Transformation is incorrect");}
    vctr<3> r0 = r;
    if (phi > 1e-16){ r0 = rotate(n, -phi, r0); }
    if ((n^2).abs() > 1e-16){ r0 = rotate(Vctr(-n[1], n[0], 0), -acos(n[2]/n.abs()), r0); }
    r0 = r+center;
    return r0;
}

struct Cylinder: public BaseFigure{
    aiv::vctr<3> boc; // центр нижней грани
    double R, H;    // радиус и высота
    aiv::vctr<3> n; // направляющая вдоль оси z

    virtual vctr<3> get_min() const {
        vctr<3> tmp_min = rotmov_back(Vctr(-R,-R,0.0), boc, n, 0.0);
        for (int ix=-1;ix<=1;ix+=2) for (int iy=-1;iy<=1;iy+=2) for (int iz=0;iz<=1;iz+=1){
            tmp_min<<=rotmov_back(Vctr(R*ix,R*iy,H*iz), boc, n, 0.0);
        }
        return tmp_min;
    }
    virtual vctr<3> get_max() const {
        vctr<3> tmp_max = rotmov_back(Vctr(R,R,H), boc, n, 0.0);
        for (int ix=-1;ix<=1;ix+=2) for (int iy=-1;iy<=1;iy+=2) for (int iz=0;iz<=1;iz+=1){
            tmp_max>>=rotmov_back(Vctr(R*ix,R*iy,H*iz), boc, n, 0.0);
        }
        return tmp_max;
    }
    virtual bool check(const aiv::vctr<3> &r) const {
        vctr<3> r0 = rotmov(r, boc, n, 0.0);
        return fabs(r0[2]-H*0.5)<=H*0.5 && (r0^2).abs()<=R;
    }
};

struct Box: public BaseFigure{
    aiv::vctr<3> boc; // центр нижней грани
    double A, B, H;    // стороны нижней грани и высота
    aiv::vctr<3> n; // направляющая вдоль оси z
    double phi; // угол поворота относительно оси z

    virtual vctr<3> get_min() const {
        vctr<3> tmp_min = rotmov_back(Vctr(-A*0.5,-B*0.5,0.0), boc, n, phi);
        for (int ix=-1;ix<=1;ix+=2) for (int iy=-1;iy<=1;iy+=2) for (int iz=0;iz<=1;iz+=1){
            tmp_min<<=rotmov_back(Vctr(A*ix*0.5,B*iy*0.5,H*iz), boc, n, phi);
        }
        return tmp_min;
    }
    virtual vctr<3> get_max() const {
        vctr<3> tmp_max = rotmov_back(Vctr(A*0.5,B*0.5,H), boc, n, phi);
        for (int ix=-1;ix<=1;ix+=2) for (int iy=-1;iy<=1;iy+=2) for (int iz=0;iz<=1;iz+=1){
            tmp_max>>=rotmov_back(Vctr(A*ix*0.5,B*iy*0.5,H*iz), boc, n, phi);
        }
        return tmp_max;
    }
    virtual bool check(const aiv::vctr<3> &r) const {
        vctr<3> r0 = rotmov(r, boc, n, phi);
        return fabs(r0[2]-H*0.5)<=H*0.5 && fabs(r0[1])<=B*0.5 && fabs(r0[0])<=A*0.5;
    }
};

Figure cylinder(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double R, double H){
    Cylinder* f = new Cylinder;
    f->boc = bottom_origin_center;
    f->n = n; f->R = R; f->H = H;
    Figure res; res.figure.reset(f); return res;
};

Figure box(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A, double B, double H){
    Box* f = new Box;
    f->boc = bottom_origin_center;
    f->n = n; f->phi = phi; f->A = A; f->B = B; f->H = H;
    Figure res; res.figure.reset(f); return res;
};

Figure cube(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A){
    Box* f = new Box;
    f->boc = bottom_origin_center;
    f->n = n; f->phi = phi; f->A = A; f->B = A; f->H = A;
    Figure res; res.figure.reset(f); return res;
};

int main(){

   Figure f1 = cylinder(Vctr(0.,0.,0.),Vctr(0.,0.,1.), 20., 20.);
   Figure f2 = f1.rotate(Vctr(0.,0.,0.), Vctr(1.,1.,1));
   Figure f3 = f1 + f2;

   return 0;
}
