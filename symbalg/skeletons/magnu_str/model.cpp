#include "model.hpp"


// описание кристаллической решетки
struct NbCR{ // доступ к одному элементу
	indx<3> dpos; // смещение в соседнюю ячейку
	int lattice;  // номекр подрешетки 
	NbCR(){}
	NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};

const int max_nb_count = %(max_nb_count)i; // максимальное количество соседей у атома
const int nb_counts[cell_sz] = {%(nb_counts)s}; // количество соседей у атомов различных подрешеток
const NbCR nb_arr[cell_sz][max_nb_count] = {%(nb_arr)s};


%(model_steps)s

//++Mview
