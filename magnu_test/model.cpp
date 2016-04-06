#include "model.hpp"

inline vctr<3> Atom::get_m(int stage) const{
}
inline void Atom::step(int stage,const Model & model,const vctr<3> & Hexch){
for(auto stage = 0; stage<stage_count; ++stage){
    for(indx<3> pos = 0; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(auto l = 0; l<cell_sz; ++l){
            Atom &atom = cell.atoms[l];
            if(!atom.usage){
                continue;
            };
            vctr<3> Hexch;
            if(calc_exch&(1<<stage)){
                for(auto i = 0; i<nb_counts[l]; ++i){
                    const NbCR &nb = nb_arr[l][i];
                    const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
                    if(cell2.usage[nb.lattice]){
                        Hexch += cell2.atoms[nb.lattice].get_m(stage)*arrJ[l][nb.lattice];
                    };
                };
            };
        };
    };
};
}





 double Model::get_J(int l1,int l2) const{
return arrJ[l1][l2];
}
 void Model::set_J(int l1,int l2,double J){
arrJ[l1][l2] = J;
arrJ[l2][l1] = J;
}
 void Model::step(){
}

 void NbCR::NbCR(int l,indx<3> d){
}


