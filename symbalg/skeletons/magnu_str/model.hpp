#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
#include <vector>
#include "magnulib/lattice.hpp"
#include "magnulib/geometry.hpp"
using namespace aiv;

class Model;

struct Atom{  
// поля атома. передаются в mk_module как Atom(field1 = "type1", ...)
%(atom_data)s 

// методы атома - различные стадии. Передаюся в mk_module 
%(atom_stages_heads)s 
};

struct Cell;

struct Aniso{
	vctr<3> n;
	double K;
};

class Model: public %(lattice_name)s{
    array<Cell, 3> data;               // массив ячеек
	double arrJ[cell_sz][cell_sz];     // массив обменных интегралов
	std::vector<Aniso> arrK1[cell_sz],  arrK3[cell_sz];
	vctr<3> minxyz;
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
	/////////?????????///////////
	inline double calc_Wexch(const vctr<3> &m, int lattice){ /////////?????????///////////
		return 0;/////////?????????///////////
	}/////////?????????///////////
	/////////?????????///////////
public:

// поля модели, передаются в mk_module
%(model_params)s
	
	double time;
	int Natoms;
	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
	void add_K1(Aniso aniso, int lattice){ arrK1[lattice].push_back(aniso); }
	void add_K3(Aniso aniso, int lattice){ arrK3[lattice].push_back(aniso); }
// методы модели, передаются в mk_module
%(model_steps_heads)s        
	GlobalTrans *trans;
	void init(BaseFigure &figure, GlobalTrans &trans);

	//Временная диагностика для тестирования
	void dump_head(aiv::Ostream& S); 
    void dump_data(aiv::Ostream& S); 

    void init_diag(aiv::Ostream& S);
    void dump_diag(aiv::Ostream& S);
    void simplestart(const vctr<3> &mstart);
    //занятые ячейки.
    int total_cells();
    int total_cells_x();
    int total_cells_y();
    int total_cells_z();
    int used_cells();
    void text_dump();
};

struct Cell{
	Atom atoms[Model::cell_sz]; // атомы
	bool usage[Model::cell_sz]; // флаги использования атомов
};

// тела методов атома - различных стадий.
%(atom_stages)s

#endif //MODEL_HPP
