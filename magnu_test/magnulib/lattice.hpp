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
#endif //MAGNU_LATTICE_HPP