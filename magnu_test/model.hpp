#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
class Model;
class Atom {
public:
	inline vctr<3> get_m(int stage) const;
	inline void step(int stage,const Model & model,const vctr<3> & Hexch);
};
const int cell_sz;
const int stage_count;
const int calc_exch;
class Cell {
public:
	 Atom atoms[cell_sz];
	 bool usage[cell_sz];
};
class Model {
public:
	 array<Cell,3> tile_data;
	 double arrJ[cell_sz][cell_sz];
	 double get_J(int l1,int l2) const;
	 void set_J(int l1,int l2,double J);
	 void step();
};
class NbCR {
public:
	 indx<3> dpos;
	 int lattice;
	 void NbCR(int l,indx<3> d);
};
const int max_nb_count;
const int nb_counts[cell_sz];
const NbCR nb_arr[cell_sz][max_nb_count];
#endif