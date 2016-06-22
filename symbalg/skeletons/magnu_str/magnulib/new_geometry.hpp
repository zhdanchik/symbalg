#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <aivlib/vectorD.hpp>
// #include <vector>
// #include <algorithm>
using namespace aiv;


struct BaseFigure{
protected:
    int counter;
public:
    virtual void free() = 0;
    // virtual vctr<3> get_min() const = 0;
    // virtual vctr<3> get_max() const = 0;
    // virtual bool check(const aiv::vctr<3> &r) const = 0;

    // const BaseFigure* transform(const aiv::vctr<3> &ox, const aiv::vctr<3> &oy, const aiv::vctr<3> &oz) {}
    // const BaseFigure* move(const aiv::vctr<3> &offset) {}
    BaseFigure* rotate(const aiv::vctr<3> &center, const aiv::vctr<3> &n_phi);
};

// const BaseFigure* operator + (const BaseFigure* a, const BaseFigure* b);
// const BaseFigure* operator - (const BaseFigure* a, const BaseFigure* b);
// const BaseFigure* operator * (const BaseFigure* a, const BaseFigure* b);

BaseFigure* cylinder(const aiv::vctr<3> center, const aiv::vctr<3> &n, double R, double H);
//box
//sphere
//ellipse

#endif //GEOMETRY_HPP