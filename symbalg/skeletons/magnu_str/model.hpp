#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
#include <vector>
using namespace aiv;

class Model;

struct Atom{  
// поля атома. передаются в mk_module как Atom(field1 = "type1", ...)
%(atom_data)s 

// методы атома - различные стадии. Передаюся в mk_module 
%(atom_stages_heads)s 
};

const int cell_sz = %(cell_sz)i; // число атомов в ячейке (число подрешеток)

struct Cell{
	Atom atoms[cell_sz]; // атомы
	bool usage[cell_sz]; // флаги использования атомов
};

struct Aniso{
	vctr<3> n;
	double K;
};

class Model{

	double arrJ[cell_sz][cell_sz];     // массив обменных интегралов
	
	std::vector<Aniso> arrK1[cell_sz],  arrK3[cell_sz];
	inline vctr<3> calc_Haniso(const vctr<3> &m, int lattice){
		vctr<3> H;
		for(auto A=arrK1[lattice].begin(); A!=arrK1[lattice].end(); ++A) H += A->n*(A->n*m*A->K);
		for(auto A=arrK3[lattice].begin(); A!=arrK3[lattice].end(); ++A){ double nm = A->n*m; H += A->n*(nm*nm*nm*A->K); }
		return H;
	}
	inline double calc_Waniso(const vctr<3> &m, int lattice){
		double W = 0;
		for(auto A=arrK1[lattice].begin(); A!=arrK1[lattice].end(); ++A){ double nm = A->n*m; W += nm*nm*A->K*.5; }
		for(auto A=arrK3[lattice].begin(); A!=arrK3[lattice].end(); ++A){ double nm = A->n*m; W += nm*nm*nm*nm*A->K*.25; }
		return W;
	}
public:
    array<Cell, 3> data;               // массив ячеек

// поля модели, передаются в mk_module
%(model_params)s

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
	void add_K1(Aniso aniso, int lattice){ arrK1[lattice].push_back(aniso); }
	void add_K3(Aniso aniso, int lattice){ arrK3[lattice].push_back(aniso); }
// методы модели, передаются в mk_module
%(model_steps_heads)s
    vctr<3> M1();
    void simplestart(const vctr<3> &mstart);
};
// тела методов атома - различных стадий.
%(atom_stages)s

#endif
