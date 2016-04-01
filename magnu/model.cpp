#include "model.hpp"

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

void Model::step(){
	for(int stage=0; stage<stage_count; ++stage)
		for(indx<3> pos; pos.less(data.N); ++pos){
			Cell &cell = data[pos];
			for(int l=0; l<cell_sz; ++l){ 
				Atom &atom = cell.atoms[l];
				if(!atom.usage) continue; 
				vctr<3> Hexch; 
				if(calc_exch&(1<<stage)) for(int i=0; i<nb_counts[l]; ++i){ 
					const NbCR &nb = nb_arr[l][i];
					const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
					if(cell2.usage[nb.lattice]) Hexch += cell2.atoms[nb.lattice].get_m(stage)*arrJ[l][nb.lattice];
				}
				atom.step(stage, *this, Hexch);
			}
		}
}

//++Mview
