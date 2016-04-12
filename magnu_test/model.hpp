#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;

class Model;

struct Atom{  
// поля атома. передаются в mk_module как Atom(field1 = "type1", ...)
	vctr<3> m1;
	vctr<3> m0; 

// методы атома - различные стадии. Передаюся в mk_module 
	inline void stage1(const Model &model, const vctr<3> &Hexch);
	inline void stage2(const Model &model);
	inline void foo(const Model &model);
 
};

const int cell_sz = 1; // число атомов в ячейке (число подрешеток)

struct Cell{
	Atom atoms[cell_sz]; // атомы
	bool usage[cell_sz]; // флаги использования атомов
};

class Model{

	double arrJ[cell_sz][cell_sz];     // массив обменных интегралов

public:
    array<Cell, 3> data;               // массив ячеек

// поля модели, передаются в mk_module
	double h;
	double alpha;
	vctr<3> Hext;
	double gamma;

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
// методы модели, передаются в mk_module
	void step();
	void foo();

    vctr<3> M1();
    void simplestart(const vctr<3> &mstart);
};
// тела методов атома - различных стадий.
inline void Atom::stage1(const Model &model, const vctr<3> &Hexch){
auto Heff = model.Hext+Hexch;
m1 = m0-model.h*(model.gamma*m0%Heff+model.alpha*m0%(m0%Heff));
m1 /= m1.abs();
}
inline void Atom::stage2(const Model &model){
m0 = m1;
}
inline void Atom::foo(const Model &model){
m1 = m0;
}


#endif
