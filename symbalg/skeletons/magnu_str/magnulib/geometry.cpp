#include "new_geometry.hpp"

struct RotatedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> center;
    aiv::vctr<3> n_phi;
};
struct TransformedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> ox;
    aiv::vctr<3> oy;
    aiv::vctr<3> oz;
};
struct MovedFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> child;
    aiv::vctr<3> offset;
};

Figure Figure::rotate(const aiv::vctr<3> &center, const aiv::vctr<3> &n_phi){
    RotatedFigure *f = new RotatedFigure; 
    f->child = figure;  f->center = center; f->n_phi = n_phi;
    Figure res; res.figure.reset(f); return res;
}
Figure Figure::transform(const aiv::vctr<3> &ox, const aiv::vctr<3> &oy, const aiv::vctr<3> &oz){
    TransformedFigure *f = new TransformedFigure; 
    f->child = figure;  f->ox = ox; f->oy = oy; f->oz = oz;
    Figure res; res.figure.reset(f); return res;
}
Figure Figure::move(const aiv::vctr<3> &offset){
    MovedFigure *f = new MovedFigure; 
    f->child = figure;  f->offset = offset;
    Figure res; res.figure.reset(f); return res;
}


struct Cylinder: public BaseFigure{
    aiv::vctr<3> boc; // центр нижней грани
    double R, H;    // радиус и высота
    aiv::vctr<3> n; // направляющая вдоль оси z
};

Figure cylinder(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double R, double H){
    Cylinder* f = new Cylinder;
    f->boc = bottom_origin_center;
    f->n = n; f->R = R; f->H = H;
    Figure res; res.figure.reset(f); return res;
};


struct  UnionFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
};
struct  IntersectFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
};
struct  ExcludeFigure: public BaseFigure{
    std::shared_ptr<BaseFigure> lchild;
    std::shared_ptr<BaseFigure> rchild;
};

Figure Figure::operator + (const Figure &other) const{
    UnionFigure *f = new UnionFigure;
    f->lchild = figure;
    f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};
Figure Figure::operator - (const Figure &other) const{
    IntersectFigure *f = new IntersectFigure;
    f->lchild = figure;
    f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};
Figure Figure::operator * (const Figure &other) const{
    ExcludeFigure *f = new ExcludeFigure;
    f->lchild = figure;
    f->rchild = other.figure;
    Figure res; res.figure.reset(f); return res;
};

//int main(){
//
 //   Figure f1 = cylinder(Vctr(0.,0.,0.),Vctr(0.,0.,1.), 20., 20.);
 //   Figure f2 = f1.rotate(Vctr(0.,0.,0.), Vctr(1.,1.,1));
 //   Figure f3 = f1 + f2;

   // return 0;
//}
