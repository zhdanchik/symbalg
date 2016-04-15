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
%(model_steps)s

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
                s = %(atom_m)s;
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
            %(atom_st_m)s = mstart;
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
            tmpM1+=%(atom_m)s/Natoms;
        }
    }
    return tmpM1;
}