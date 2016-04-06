#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;

class Model;

struct Atom{  
	%(atom_data)s; // здесь какие то данные, полностью генерятся из питона

	// возвращает намагниченность атома в начале стадии stage
	inline vctr<3> get_m(int stage) const { %(atom_get_m)s; }

	inline void step(int stage, const Model &model, const vctr<3> &Hexch);
};


const int cell_sz = %(cell_sz)i; // число атомов в ячейке
const int stage_count = %(stage_count)i; // число стадий
const int calc_exch = %(calc_exch)i; // битоавя маска, указывающая на каких стадиях считать обменное поле

struct Cell{
	Atom atoms[cell_sz];
	bool usage[cell_sz]; // флаги использования атомов
};

class Model{
	array<Cell, 3> data;
	double arrJ[cell_sz][cell_sz]; // массив обменных интегралов
public:
	%(model_params)s; // параметры модели

	double get_J(int l1, int l2) const { return arrJ[l1][l2]; }
	void set_J(int l1, int l2, double J) { arrJ[l1][l2] = arrJ[l2][l1] = J; }
	void step(); // один шаг по времени
};


inline void Atom::step(int stage, const Model &model, const vctr<3> &Hexch){
	%(atom_steps)s
}

// описание кристаллической решетки
struct NbCR{ // доступ к одному элементу
	indx<3> dpos; // смещение в соседнюю ячейку
	int lattice;  // номекр подрешетки 
	NbCR(){}
	NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};

const int max_nb_count = %(max_nb_count)i; // максимальное количество соседей у атома
const int nb_counts[cell_sz] = {%(nb_counts)i}; // количество соседей у атомов различных подрешеток
const NbCR nb_arr[cell_sz][max_nb_count] = {%(nb_arr)s};


#endif
