#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
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

class Model{

	double arrJ[cell_sz][cell_sz];     // массив обменных интегралов

public:
    array<Cell, 3> data;               // массив ячеек

// поля модели, передаются в mk_module
%(model_params)s

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
// методы модели, передаются в mk_module
%(model_steps_heads)s
    vctr<3> M1();
    void simplestart(const vctr<3> &mstart);
};
// тела методов атома - различных стадий.
%(atom_stages)s

#endif
