#include <math.h>
#include "model.hpp"


const NbCR latCubic::nb_arr[cell_sz][max_nb_count] = {{{Indx(-1, 0, 0),0},
                                                 {Indx( 0,-1, 0),0},
                                                 {Indx( 0, 0,-1),0},
                                                 {Indx( 1, 0, 0),0},
                                                 {Indx( 0, 1, 0),0},
                                                 {Indx( 0, 0, 1),0}}}; 

const vctr<3> latCubic::coords[cell_sz] = {Vctr(0.,0.,0.)}; 






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
            vctr<3> Haniso = calc_Haniso(atom.m0, l);
			atom.stage1(*this, Hexch, Haniso);
        }
        time+=h;
    }
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
			atom.stage2(*this);
        }
        time+=h;
    }
}


void Model::init(BaseFigure &figure){
    vctr<3> center = figure.get_center();
    double out_radius = figure.get_max_size();
    minxyz = center-vctr<3>(out_radius);
    const int intrad = floor(2*out_radius)+1;
    data.init(Indx(intrad,intrad,intrad)); // /Vctr(1.,1.,1.)
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if (figure.check(coords[l]+(minxyz + pos*vctr<3>(1.)))){ 
                cell.usage[l] = true;
                Natoms++;
            }
        }
    }
}


//Временная диагностика для тестирования

void Model::dump_head( aiv::Ostream& S ){
        int zero=0; 
        S.fwrite( &zero, sizeof(int) ); 
        S.fwrite( &Natoms, sizeof(int) );
        vctr<3,float> r;
        for(indx<3> pos; pos.less(data.N); ++pos){
            Cell &cell = data[pos];
            for(int l=0; l<cell_sz; ++l){ 
                if(!cell.usage[l]) continue;
                r = coords[l]+(minxyz + pos*vctr<3>(1.)); 
                S.fwrite( &r, sizeof(r) );
            }
        }
}
//------------------------------------------------------------------------------
void Model::dump_data( aiv::Ostream& S ){
        S.fwrite( &time, sizeof(double) ); vctr<3,float> s;

        for(indx<3> pos; pos.less(data.N); ++pos){
            Cell &cell = data[pos];
            for(int l=0; l<cell_sz; ++l){ 
                if(!cell.usage[l]) continue;
                Atom &atom = cell.atoms[l];    
                s = atom.m0;
                S.fwrite( &s, sizeof(s) );

            }
        }

}

void Model::simplestart(const vctr<3> &mstart){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
            atom.m0 = mstart;
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
            tmpM1+=atom.m0/Natoms;
        }
    }
    return tmpM1;
}