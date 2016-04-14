#include "model.hpp"




const NbCR Cubic::nb_arr[cell_sz][max_nb_count] = {{{Indx(-1, 0, 0),0},
                                                 {Indx( 0,-1, 0),0},
                                                 {Indx( 0, 0,-1),0},
                                                 {Indx( 1, 0, 0),0},
                                                 {Indx( 0, 1, 0),0},
                                                 {Indx( 0, 0, 1),0}}}; 

const vctr<3> Cubic::coords[cell_sz] = {Vctr(0.,0.,0.)}; 






// тела методов модели
%(model_steps)s

void Model::dump_head( aiv::Ostream& S ){
        int zero=0; 
        S.fwrite( &zero, sizeof(int) ); 
        int count=0;
        for(indx<3> pos; pos.less(data.N); ++pos){
            Cell &cell = data[pos];
            for(int l=0; l<cell_sz; ++l){ 
                if(!cell.usage[l]) continue;
                count++;

            }
        }        
        S.fwrite( &count, sizeof(int) );
        vctr<3,float> r;
        for(indx<3> pos; pos.less(data.N); ++pos){
            Cell &cell = data[pos];
            for(int l=0; l<cell_sz; ++l){ 
                if(!cell.usage[l]) continue;
                r = coords[l]+(pos*Vctr(1.,1.,1.));
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
                s = cell.atoms[l].m0;
                S.fwrite( &s, sizeof(s) );

            }
        }

}

void Model::simplestart(const vctr<3> &mstart){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            cell.usage[l] = true;
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