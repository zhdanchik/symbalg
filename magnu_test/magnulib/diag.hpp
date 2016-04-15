#ifndef MAGNU_DIAG_HPP
#define MAGNU_DIAG_HPP


class Diag{
        //Временная диагностика для тестирования
    void dump_head(aiv::Ostream& S); 
    void dump_data(aiv::Ostream& S); 

    vctr<3> M1();
    void simplestart(const vctr<3> &mstart);


};



//Временная диагностика для тестирования

void Diag::dump_head( aiv::Ostream& S ){
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
                r = coords[l]+(minxyz + pos*vctr<3>(1.));
                S.fwrite( &r, sizeof(r) );

            }
        }
}
//------------------------------------------------------------------------------
void Diag::dump_data( aiv::Ostream& S ){
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

void Diag::simplestart(const vctr<3> &mstart){
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
            atom.m0 = mstart;
            atom.m1 = mstart;
        }
    }
}
vctr<3> Diag::M1(){
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

#endif //MAGNU_DIAG_HPP