#ifndef MAGNUS_GEOMETRY_HPP
#define MAGNUS_GEOMETRY_HPP

#include <memory>
#include <aivlib/vectorD.hpp>
#include <aivlib/dekart.hpp>
// #include <vector>
// #include <algorithm>
using namespace aiv;


#ifndef SWIG
struct BaseFigure{
    virtual vctr<3> get_min() const = 0;
    virtual vctr<3> get_max() const = 0;
    virtual bool check(const aiv::vctr<3> &r) const = 0;
    virtual ~BaseFigure(){}
};
#endif //SWIG

class Figure{
    std::shared_ptr<BaseFigure> figure;

    friend Figure cylinder(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double R, double H);
    friend Figure box(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A, double B, double H);
    friend Figure cube(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A);
    friend Figure spheroid(const aiv::vctr<3> center, double R);

public:
    vctr<3> get_min() const { return figure->get_min(); }
    vctr<3> get_max() const { return figure->get_max(); }
    bool check(const aiv::vctr<3> &r) const { return figure->check(r); }

    Figure move(const aiv::vctr<3> &offset);
    Figure rotate(const aiv::vctr<3> &center, const aiv::vctr<3> &n_phi);
    Figure transform(const aiv::vctr<3> &ox, const aiv::vctr<3> &oy, const aiv::vctr<3> &oz);
    

    Figure operator + (const Figure &other) const;
    Figure operator - (const Figure &other) const;
    Figure operator * (const Figure &other) const;
};

Figure cylinder(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double R, double H);
Figure box(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A, double B, double H);
Figure cube(const aiv::vctr<3> bottom_origin_center, const aiv::vctr<3> &n, double phi, double A);
Figure spheroid(const aiv::vctr<3> center, double R);
//sphere
//ellipse

#endif //MAGNUS_GEOMETRY_HPP