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

const int latFCC4_trans_1::nb_counts[cell_sz] = {12};
const NbCR latFCC4_trans_1::nb_arr[cell_sz][max_nb_count] = {{{Indx(-1, 0, 0),0}, {Indx( 0,-1, 0),0}, {Indx( 0, 0,-1),0},
                                                              {Indx( 1, 0, 0),0}, {Indx( 0, 1, 0),0}, {Indx( 0, 0, 1),0},
                                                              {Indx(-1,-1,-1),0}, {Indx(-1, 0,-1),0}, {Indx( 0,-1,-1),0}, 
                                                              {Indx( 1, 1, 1),0}, {Indx( 1, 0, 1),0}, {Indx( 0, 1, 1),0}},
                                                   }; 
const vctr<3> latFCC4_trans_1::coords[cell_sz] = {Vctr(0.,0.,0.)}; 
const vctr<3> latFCC4_trans_1::cell_coord_size = Vctr(1.,1.,1.);




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
    }
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];
			atom.stage2(*this);
        }
    }
	time+=h;}


void Model::init(BaseFigure &figure, GlobalTrans &tr){
    trans=&tr; 
    // Нужно перебрать все 4 диагонали прямоугольника! Пока работать будет не во всех случаях

    vctr<3> tmp_minxyz = figure.get_minxyz(); // в новой системе координат
    vctr<3> tmp_maxxyz = figure.get_maxxyz();
    vctr<3> C = 0.5*(tmp_maxxyz + tmp_minxyz);
    vctr<3> dv = (tmp_maxxyz -tmp_minxyz)/2;

    vctr<3> tmp_minxyz_1 = trans->trans_vec_back(C-dv);// в исходной системе координат
    vctr<3> tmp_maxxyz_1 = trans->trans_vec_back(C-dv);

    for (int ix=-1;ix<=1;ix+=2) for (int iy=-1;iy<=1;iy+=2) for (int iz=-1;iz<=1;iz+=2) {
      vctr<3> new_corn = trans->trans_vec_back((dv^Vctr(ix,iy,iz))+C);
      tmp_minxyz_1[0] = std::min(new_corn[0], tmp_minxyz_1[0]);
      tmp_minxyz_1[1] = std::min(new_corn[1], tmp_minxyz_1[1]);
      tmp_minxyz_1[2] = std::min(new_corn[2], tmp_minxyz_1[2]);

      tmp_maxxyz_1[0] = std::max(new_corn[0], tmp_maxxyz_1[0]);
      tmp_maxxyz_1[1] = std::max(new_corn[1], tmp_maxxyz_1[1]);
      tmp_maxxyz_1[2] = std::max(new_corn[2], tmp_maxxyz_1[2]);
    }
    
    minxyz = tmp_minxyz_1;
    vctr<3> maxxyz = tmp_maxxyz_1;

    indx<3> iminxyz = Indx(floor(minxyz[0])-1,floor(minxyz[1])-1,floor(minxyz[2])-1);
    indx<3> imaxxyz = Indx(ceil(maxxyz[0])+1,ceil(maxxyz[1])+1,ceil(maxxyz[2])+1);
    // printf("%s | %s | %s | %s | %s | %s\n",tmp_minxyz.c_str(),tmp_maxxyz.c_str(),tmp_minxyz_1.c_str(),tmp_maxxyz_1.c_str(), iminxyz.c_str(), imaxxyz.c_str());
    data.init(imaxxyz-iminxyz+Indx(1,1,1)); // /Vctr(1.,1.,1.)
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            vctr<3> inv_cell_coord_size  = Vctr(1./cell_coord_size[0], 1./cell_coord_size[1], 1./cell_coord_size[2]);
            vctr<3> new_vec = trans->trans_vec((coords[l]^inv_cell_coord_size)+(iminxyz + pos)*Vctr(1.,1.,1.));
            // printf("%d %s %s %d\n",l,pos.c_str(),new_vec.c_str(),figure.check(new_vec));
            if (figure.check(new_vec)){ 
                cell.usage[l] = true;
                Natoms++;
            } else {cell.usage[l] = false;}
        }
    }
}


//Временная диагностика для тестирования

void Model::dump_head( aiv::Ostream& S ){
    int zero=0; 
    S.fwrite( &zero, sizeof(int) ); 
    S.fwrite( &Natoms, sizeof(int) );
    vctr<3,float> r;
    indx<3> iminxyz = Indx(floor(minxyz[0]),floor(minxyz[1]),floor(minxyz[2]));
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            vctr<3> inv_cell_coord_size  = Vctr(1./cell_coord_size[0], 1./cell_coord_size[1], 1./cell_coord_size[2]);
            vctr<3> new_vec = trans->trans_vec((coords[l]^inv_cell_coord_size)+(iminxyz + pos)*Vctr(1.,1.,1.));
            r = new_vec;
            // r = trans->trans_vec( coords[l] + (((iminxyz + pos)*Vctr(1.,1.,1.))^cell_coord_size) );
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


int Model::total_cells(){return data.N.volume();}
int Model::total_cells_x(){return data.N[0];}
int Model::total_cells_y(){return data.N[1];}
int Model::total_cells_z(){return data.N[2];}
int Model::used_cells(){
      int tmpN = 0;
      for(indx<3> pos; pos.less(data.N); ++pos){
          Cell &cell = data[pos];
          for(int l=0; l<cell_sz; ++l){ 
              if (cell.usage[l]){ 
                  tmpN++;
                  break;
              }
          }
      }
      return tmpN;
}

void Model::text_dump(){
    for(indx<3> pos; pos.less(data.N); ++pos){
      Cell &cell = data[pos];
      printf("%s ",pos.c_str());
      for(int l=0; l<cell_sz; ++l){ 
            printf("%d %4d ",l, cell.usage[l]);
            const Atom &atom = cell.atoms[l];
            printf("%s\n",atom.m0.c_str());
          }
      }
}

void Model::border_space(){
  int sp = 0;
  bool ss1 = false;
  for (int i=0; i< data.N[0]; i++) {
    for (int k=0; k<data.N[1]; k++) for (int l = 0; l<data.N[2]; l++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf("X axis: total %d, left %d",data.N[0],sp);
  sp = 0;
  ss1 = false;  
  for (int i=data.N[0]-1; i>=0; i--) {
    for (int k=0; k<data.N[1]; k++) for (int l = 0; l<data.N[2]; l++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf(", right %d\n",sp);

  sp = 0;
  ss1 = false;
  for (int k=0; k< data.N[1]; k++) {
    for (int i=0; i<data.N[0]; i++) for (int l = 0; l<data.N[2]; l++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf("Y axis: total %d, left %d",data.N[1],sp);
  sp = 0;
  ss1 = false;  
  for (int k=data.N[1]-1; k>=0; k--) {
    for (int i=0; i<data.N[0]; i++) for (int l = 0; l<data.N[2]; l++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf(", right %d\n",sp);

  sp = 0;
  ss1 = false;
  for (int l=0; l< data.N[2]; l++) {
    for (int i=0; i<data.N[0]; i++) for (int k = 0; k<data.N[1]; k++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf("Z axis: total %d, left %d",data.N[2],sp);
  sp = 0;
  ss1 = false;  
  for (int l=data.N[2]-1; l>=0; l--) {
    for (int i=0; i<data.N[0]; i++) for (int k = 0; k<data.N[1]; k++) {
      Cell &cell = data[Indx(i,k,l)];
      for (int j=0; j<cell_sz; j++){
        if (cell.usage[j]){ss1=true;}
      }
    }
    if (ss1){break;}else{sp++;}
  }
  printf(", right %d\n",sp);
}