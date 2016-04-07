#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;

class Model;

struct Atom{  
%(atom_data)s // здесь какие то данные, полностью генерятся из питона
%(atom_steps_head)s
};

const int cell_sz = %(cell_sz)i; // число атомов в ячейке

struct Cell{
	Atom atoms[cell_sz];
	bool usage[cell_sz]; // флаги использования атомов
};

class Model{
	array<Cell, 3> data;
	double arrJ[cell_sz][cell_sz]; // массив обменных интегралов
public:
%(model_params)s // параметры модели

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
%(model_steps_heads)s
};


%(atom_steps)s

#endif
