#include "model.hpp"

// описание кристаллической решетки
struct NbCR{ // доступ к одному элементу
	indx<3> dpos; // смещение в соседнюю ячейку
	int lattice;  // номер подрешетки 
	NbCR(){}
	NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};

const int max_nb_count = %(max_nb_count)i; // максимальное количество соседей у атома
const int nb_counts[cell_sz] = {%(nb_counts)s}; // количество соседей у атомов различных подрешеток
const NbCR nb_arr[cell_sz][max_nb_count] = {%(nb_arr)s}; 

// тела методов модели
%(model_steps)s


void Model::simplestart(const vctr<3> &mstart){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            cell.usage[l] = true;
            // if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
            atom.m0 = mstart;
            atom.m1 = mstart;
        }
    }
}
vctr<3> Model::M1(){
    vctr<3> tmpM1 = Vctr(0.,0.,0.);
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            const Atom &atom = cell.atoms[l];
            tmpM1+=atom.m0/data.N.volume();
        }
    }
    return tmpM1;
}