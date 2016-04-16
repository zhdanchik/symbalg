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
	vctr<3> m1;
	vctr<3> m0; 

// методы атома - различные стадии. Передаюся в mk_module 
	inline void stage1(const Model &model, const vctr<3> &Hexch, const vctr<3> &Haniso);
	inline void stage2(const Model &model);
 
};

struct Cell;

struct Aniso{
	vctr<3> n;
	double K;
};

class Model: public latFCC4{
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
	double h;
	vctr<3> Hext;
	double gamma;
	double alpha;
	
	double time;
	int Natoms;
	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
	void add_K1(Aniso aniso, int lattice){ arrK1[lattice].push_back(aniso); }
	void add_K3(Aniso aniso, int lattice){ arrK3[lattice].push_back(aniso); }
// методы модели, передаются в mk_module
	void step();
        
	
	void init(BaseFigure &figure);

	//Временная диагностика для тестирования
	void dump_head(aiv::Ostream& S); 
    void dump_data(aiv::Ostream& S); 

    void init_diag(aiv::Ostream& S);
    void dump_diag(aiv::Ostream& S);
    void simplestart(const vctr<3> &mstart);
};

struct Cell{
	Atom atoms[Model::cell_sz]; // атомы
	bool usage[Model::cell_sz]; // флаги использования атомов
};

// тела методов атома - различных стадий.
	inline void Atom::stage1(const Model &model, const vctr<3> &Hexch, const vctr<3> &Haniso){
auto Heff = model.Hext+Hexch+Haniso;
m1 = m0-model.h*(model.gamma*m0%Heff+model.alpha*m0%(m0%Heff));
m1 /= m1.abs();
}
	inline void Atom::stage2(const Model &model){
m0 = m1;
}


#endif //MODEL_HPP
