#include <math.h>
#include "model.hpp"

const int latCubic::nb_counts[cell_sz] = {6};
const NbCR latCubic::nb_arr[cell_sz][max_nb_count] = {{{Indx(-1, 0, 0),0}, {Indx( 0,-1, 0),0}, {Indx( 0, 0,-1),0},
                                                       {Indx( 1, 0, 0),0}, {Indx( 0, 1, 0),0}, {Indx( 0, 0, 1),0}}
                                                     }; 
const vctr<3> latCubic::coords[cell_sz] = {Vctr(0.,0.,0.)}; 
const vctr<3> latCubic::cell_coord_size = Vctr(1.,1.,1.);

const int latICC::nb_counts[cell_sz] = {8,8};
const NbCR latICC::nb_arr[cell_sz][max_nb_count] = {{{Indx( 0, 0, 0),1}, {Indx(-1, 0, 0),1}, {Indx( 0,-1, 0),1}, {Indx(-1,-1, 0),1},
                                                     {Indx( 0, 0,-1),1}, {Indx(-1, 0,-1),1}, {Indx( 0,-1,-1),1}, {Indx(-1,-1,-1),1}},

                                                    {{Indx( 0, 0, 0),0}, {Indx( 1, 0, 0),0}, {Indx( 0, 1, 0),0}, {Indx( 1, 1, 0),0},
                                                     {Indx( 0, 0, 1),0}, {Indx( 1, 0, 1),0}, {Indx( 0, 1, 1),0}, {Indx( 1, 1, 1),0}}
                                                   }; 
const vctr<3> latICC::coords[cell_sz] = {Vctr(0.,0.,0.), Vctr(1.,1.,1.)}; 
const vctr<3> latICC::cell_coord_size = Vctr(2.,2.,2.);

const int latFCC3::nb_counts[cell_sz] = {8,8,8};
const NbCR latFCC3::nb_arr[cell_sz][max_nb_count] = {{{Indx( 0, 0, 0),1}, {Indx( 0, 1, 0),1}, {Indx( 0, 0,-1),1}, {Indx( 0, 1,-1),1},
                                                      {Indx( 0, 0, 0),2}, {Indx( 1, 0, 0),2}, {Indx( 0, 0,-1),2}, {Indx( 1, 0,-1),2}},

                                                     {{Indx( 0, 0, 0),0}, {Indx( 0, 0, 1),0}, {Indx( 0,-1, 0),0}, {Indx( 0,-1, 1),0},
                                                      {Indx( 0, 0, 0),2}, {Indx( 1, 0, 0),2}, {Indx( 0,-1, 0),2}, {Indx( 1,-1, 0),2}},

                                                     {{Indx( 0, 0, 0),0}, {Indx( 0, 0, 1),0}, {Indx(-1, 0, 0),0}, {Indx(-1, 0, 1),0},
                                                      {Indx( 0, 0, 0),1}, {Indx( 0, 1, 0),1}, {Indx(-1, 0, 0),1}, {Indx(-1, 1, 0),1}}
                                                   }; 
const vctr<3> latFCC3::coords[cell_sz] = {Vctr(1.,1.,0.), Vctr(1.,0.,1.), Vctr(0.,1.,1.)}; 
const vctr<3> latFCC3::cell_coord_size = Vctr(2.,2.,2.);

const int latFCC4::nb_counts[cell_sz] = {12,12,12,12};
const NbCR latFCC4::nb_arr[cell_sz][max_nb_count] = {{{Indx( 0, 0, 0),1}, {Indx(-1, 0, 0),1}, {Indx( 0,-1, 0),1}, {Indx(-1,-1, 0),1},
                                                      {Indx( 0, 0, 0),2}, {Indx( 0, 0,-1),2}, {Indx(-1, 0, 0),2}, {Indx(-1, 0,-1),2},
                                                      {Indx( 0, 0, 0),3}, {Indx( 0,-1, 0),3}, {Indx( 0, 0,-1),3}, {Indx( 0,-1,-1),3}},

                                                     {{Indx( 0, 0, 0),0}, {Indx( 0, 1, 0),0}, {Indx( 1, 0, 0),0}, {Indx( 1, 1, 0),0},
                                                      {Indx( 0, 0, 0),2}, {Indx( 0, 0,-1),2}, {Indx( 0, 1, 0),2}, {Indx( 0, 1,-1),2},
                                                      {Indx( 0, 0, 0),3}, {Indx( 1, 0, 0),3}, {Indx( 0, 0,-1),3}, {Indx( 1, 0,-1),3}},

                                                     {{Indx( 0, 0, 0),0}, {Indx( 1, 0, 0),0}, {Indx( 0, 0, 1),0}, {Indx( 1, 0, 1),0},
                                                      {Indx( 0, 0, 0),1}, {Indx( 0, 0, 1),1}, {Indx( 0,-1, 0),1}, {Indx( 0,-1, 1),1},
                                                      {Indx( 0, 0, 0),3}, {Indx( 0,-1, 0),3}, {Indx( 1, 0, 0),3}, {Indx( 1,-1, 0),3}},

                                                     {{Indx( 0, 0, 0),0}, {Indx( 0, 1, 0),0}, {Indx( 0, 0, 1),0}, {Indx( 0, 1, 1),0},
                                                      {Indx( 0, 0, 0),1}, {Indx( 0, 0, 1),1}, {Indx(-1, 0, 0),1}, {Indx(-1, 0, 1),1},
                                                      {Indx( 0, 0, 0),2}, {Indx(-1, 0, 0),2}, {Indx( 0, 1, 0),2}, {Indx(-1, 1, 0),2}}
                                                   }; 
const vctr<3> latFCC4::coords[cell_sz] = {Vctr(0.,0.,0.), Vctr(1.,1.,0.), Vctr(1.,0.,1.), Vctr(0.,1.,1.)}; 
const vctr<3> latFCC4::cell_coord_size = Vctr(2.,2.,2.);


// тела методов модели
void Model::stepRK4(){
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
			atom.rk_stage1(*this, Hexch);
        }
    }
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
			atom.rk_stage2(*this, Hexch);
        }
    }
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
			atom.rk_stage3(*this, Hexch);
        }
    }
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
			atom.rk_stage4(*this, Hexch);
        }
    }
	time+=h;}


void Model::init(BaseFigure &figure){

    minxyz = figure.get_minxyz();
    vctr<3> maxxyz = figure.get_maxxyz();
    indx<3> iminxyz = Indx(floor(minxyz[0]),floor(minxyz[1]),floor(minxyz[2]));
    indx<3> imaxxyz = Indx(ceil(maxxyz[0]),ceil(maxxyz[1]),ceil(maxxyz[2]));
    data.init(imaxxyz-iminxyz); // /Vctr(1.,1.,1.)
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if (figure.check(coords[l]+(minxyz + pos*cell_coord_size))){ 
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
                r = coords[l]+(minxyz + pos*cell_coord_size); 
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

void Model::init_diag(aiv::Ostream& S){S.printf("#:t M1x M1y M1z Wf W\n" );}

void Model::dump_diag(aiv::Ostream& S){
    vctr<3> tmpM1 = Vctr(0.,0.,0.);
    double W = 0.;
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            const Atom &atom = cell.atoms[l];
            tmpM1+=atom.m0/Natoms;
            W+=-calc_Wexch(atom.m0,l)-calc_Waniso(atom.m0,l) - Hext*atom.m0;
        }
    }
    double W1 = W/Natoms;
    S.printf("%f %f %f %f %f %f\n",time, tmpM1[0], tmpM1[1], tmpM1[2], W, W1);
}
