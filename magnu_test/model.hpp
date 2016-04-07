#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;

class Model;

struct Atom{  
	vctr<3> m1;
	vctr<3> m0; // здесь какие то данные, полностью генерятся из питона
	inline void stage1(const Model &model, const vctr<3> &Hexch);
	inline void stage2(const Model &model, const vctr<3> &Hexch);
	inline void foo(const Model &model, const vctr<3> &Hexch);

};

const int cell_sz = 2; // число атомов в ячейке

struct Cell{
	Atom atoms[cell_sz];
	bool usage[cell_sz]; // флаги использования атомов
};

class Model{
	array<Cell, 3> data;
	double arrJ[cell_sz][cell_sz]; // массив обменных интегралов
public:
	double h;
	double alpha;
	vctr<3> Hext;
	double gamma; // параметры модели

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
	void step();
	void foo();

};


inline void Atom::stage1(const Model &model, const vctr<3> &Hexch){
Heff = Hext+Hexch;
m1 = m0-h*(gamma*m0%Heff+alpha*m0%(m0%Heff));
m1 /= m1.abs();
}
inline void Atom::stage2(const Model &model, const vctr<3> &Hexch){
m0 = m1;
}
inline void Atom::foo(const Model &model, const vctr<3> &Hexch){
m1 = m0;
}


#endif
