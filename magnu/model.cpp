#include "model.hpp"


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
