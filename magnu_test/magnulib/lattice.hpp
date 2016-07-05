#ifndef MAGNU_LATTICE_HPP
#define MAGNU_LATTICE_HPP

#include <aivlib/vectorD.hpp>
using namespace aiv;
//-----------------------------------------------------------------------------


struct NbCR{ // доступ к одному элементу
    indx<3> dpos; // смещение в соседнюю ячейку
    int lattice;  // номер подрешетки 
    NbCR(){}
    NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};


class latCubic{
public:
    static const int cell_sz = 1; // число атомов в ячейке (число подрешеток)
    static const int max_nb_count = 6; // максимальное количество соседей у атома
    static const int nb_counts[cell_sz]; // количество соседей у атомов различных подрешеток
    static const NbCR nb_arr[cell_sz][max_nb_count]; 
    static const vctr<3> coords[cell_sz]; 
    static const vctr<3> cell_coord_size; // максимальное количество соседей у атома
};

class latICC{
public:
    static const int cell_sz = 2; // число атомов в ячейке (число подрешеток)
    static const int max_nb_count = 8; // максимальное количество соседей у атома
    static const int nb_counts[cell_sz]; // количество соседей у атомов различных подрешеток
    static const NbCR nb_arr[cell_sz][max_nb_count]; 
    static const vctr<3> coords[cell_sz]; 
    static const vctr<3> cell_coord_size; // максимальное количество соседей у атома
};

class latFCC3{
public:
    static const int cell_sz = 3; // число атомов в ячейке (число подрешеток)
    static const int max_nb_count = 8; // максимальное количество соседей у атома
    static const int nb_counts[cell_sz]; // количество соседей у атомов различных подрешеток
    static const NbCR nb_arr[cell_sz][max_nb_count]; 
    static const vctr<3> coords[cell_sz]; 
    static const vctr<3> cell_coord_size; // максимальное количество соседей у атома
};

class latFCC4{
public:
    static const int cell_sz = 4; // число атомов в ячейке (число подрешеток)
    static const int max_nb_count = 12; // максимальное количество соседей у атома
    static const int nb_counts[cell_sz]; // количество соседей у атомов различных подрешеток
    static const NbCR nb_arr[cell_sz][max_nb_count]; 
    static const vctr<3> coords[cell_sz]; 
    static const vctr<3> cell_coord_size; // максимальное количество соседей у атома
};

class latFCC4_trans_1{
public:
    static const int cell_sz = 1; // число атомов в ячейке (число подрешеток)
    static const int max_nb_count = 12; // максимальное количество соседей у атома
    static const int nb_counts[cell_sz]; // количество соседей у атомов различных подрешеток
    static const NbCR nb_arr[cell_sz][max_nb_count]; 
    static const vctr<3> coords[cell_sz]; 
    static const vctr<3> cell_coord_size; // максимальное количество соседей у атома
};
//-----------------------------------------------------------------------------

struct GlobalTrans{
    vctr<3> I1,I2,I3;

    GlobalTrans(){}
    GlobalTrans(vctr<3> i1, vctr<3> i2, vctr<3> i3): I1(i1), I2(i2), I3(i3) {}

    vctr<3> trans_vec (const aiv::vctr<3> &r){
        if (fabs(I1 * (I2%I3)) <1e-16){raise("Transformation is incorrect");}
        double x = r[0], y = r[1], z = r[2];
        double x1 = I1[0], x2 = I2[0], x3 = I3[0];
        double y1 = I1[1], y2 = I2[1], y3 = I3[1];
        double z1 = I1[2], z2 = I2[2], z3 = I3[2];
        return Vctr( ((x3*y2 - x2*y3)*z - (x3*y - x*y3)*z2 + (x2*y - x*y2)*z3),
                    -((x3*y1 - x1*y3)*z - (x3*y - x*y3)*z1 + (x1*y - x*y1)*z3),
                     ((x2*y1 - x1*y2)*z - (x2*y - x*y2)*z1 + (x1*y - x*y1)*z2) ) / ((x3*y2 - x2*y3)*z1 - (x3*y1 - x1*y3)*z2 + (x2*y1 - x1*y2)*z3);
    }
    vctr<3> trans_vec_back (const aiv::vctr<3> &r){
        if (fabs(I1 * (I2%I3)) <1e-16){raise("Transformation is incorrect");}
        double x = r[0], y = r[1], z = r[2];
        double x1 = I1[0], x2 = I2[0], x3 = I3[0];
        double y1 = I1[1], y2 = I2[1], y3 = I3[1];
        double z1 = I1[2], z2 = I2[2], z3 = I3[2];

        return Vctr(x*x1 + x2*y + x3*z,
                    x*y1 + y*y2 + y3*z,
                    x*z1 + y*z2 + z*z3);
    }
};


#endif //MAGNU_LATTICE_HPP