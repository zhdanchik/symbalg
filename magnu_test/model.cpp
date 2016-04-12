#include "model.hpp"

// описание кристаллической решетки
struct NbCR{ // доступ к одному элементу
	indx<3> dpos; // смещение в соседнюю ячейку
	int lattice;  // номер подрешетки 
	NbCR(){}
	NbCR(indx<3> d, int l):dpos(d), lattice(l){}
};

const int max_nb_count = 6; // максимальное количество соседей у атома
const int nb_counts[cell_sz] = {6}; // количество соседей у атомов различных подрешеток
const NbCR nb_arr[cell_sz][max_nb_count] = {{{Indx(-1, 0, 0),0},
                                             {Indx( 0,-1, 0),0},
                                             {Indx( 0, 0,-1),0},
                                             {Indx( 1, 0, 0),0},
                                             {Indx( 0, 1, 0),0},
                                             {Indx( 0, 0, 1),0}}}; 

// тела методов модели
void Model::step(){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
            vctr<3> Hexch;    
            for(int i=0; i<nb_counts[l]; ++i){ 
                const NbCR &nb = nb_arr[l][i];
                const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
                if(cell2.usage[nb.lattice]) {
                    const Atom &atom2 = cell2.atoms[nb.lattice];
                    Hexch += (atom2.m0)*arrJ[l][nb.lattice];
                }
            }
			atom.stage1(*this, Hexch);
        }
    }
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
			atom.stage2(*this);
        }
    }
}
void Model::foo(){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
			atom.foo(*this);
        }
    }
}



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