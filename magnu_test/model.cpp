#include "model.hpp"


// описание кристаллической решетки
struct NbCR{ // доступ к одному элементу
	indx<3> dpos; // смещение в соседнюю ячейку
	int lattice;  // номекр подрешетки 
	NbCR(){}
	NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};

const int max_nb_count = 9; // максимальное количество соседей у атома
const int nb_counts[cell_sz] = {9}; // количество соседей у атомов различных подрешеток
const NbCR nb_arr[cell_sz][max_nb_count] = {};


void Model::step(){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            Atom &atom = cell.atoms[l];
            if(!cell.usage[l]) continue;
            vctr<3> Hexch; 

            if(calc_exch&(1<<stage)) for(int i=0; i<nb_counts[l]; ++i){ 
                const NbCR &nb = nb_arr[l][i];
                const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
                if(cell2.usage[nb.lattice]) Hexch += cell2.atoms[nb.lattice].m0*arrJ[l][nb.lattice];
            }

            atom.stage1(stage, *this, Hexch);
        }
}

    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            Atom &atom = cell.atoms[l];
            if(!cell.usage[l]) continue;
            vctr<3> Hexch; 

            atom.stage2(stage, *this, Hexch);
        }
}
}
void Model::foo(){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            Atom &atom = cell.atoms[l];
            if(!cell.usage[l]) continue;
            vctr<3> Hexch; 

            atom.foo(stage, *this, Hexch);
        }
}
}


//++Mview
