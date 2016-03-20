#include "model.hpp"

// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!


//----------------------------------------------------------------------
//--------------------------EmptyTile------------------------------------
//----------------------------------------------------------------------

SecTile1* EmptyTile::cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    for(int ix=0; ix<SecTile1::Nx; ++ix) 
        for(int iy=0; iy<SecTile1::Ny; ++iy) 
            for(int iz=0; iz<SecTile1::Nz; ++iz) {
               buf[buf_sz].m1[ix][iy][iz] = Vctr(0.,0.,0.);
               buf[buf_sz].m2[ix][iy][iz] = Vctr(0.,0.,0.);
    }

    return buf+buf_sz++; 
}
SecTile2* EmptyTile::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    for(int ix=0; ix<SecTile2::Nx; ++ix) 
        for(int iy=0; iy<SecTile2::Ny; ++iy) 
            for(int iz=0; iz<SecTile2::Nz; ++iz) {
                buf[buf_sz].m1[ix][iy][iz] = Vctr(0.,0.,0.);
                buf[buf_sz].m2[ix][iy][iz] = Vctr(0.,0.,0.);
    }
    return buf+buf_sz++; 
}
SecTile3* EmptyTile::cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    for(int ix=0; ix<SecTile3::Nx; ++ix) 
        for(int iy=0; iy<SecTile3::Ny; ++iy) 
            for(int iz=0; iz<SecTile3::Nz; ++iz) {
                buf[buf_sz].m1[ix][iy][iz] = Vctr(0.,0.,0.);
                buf[buf_sz].m2[ix][iy][iz] = Vctr(0.,0.,0.);
    }
    return buf+buf_sz++; 
} 


//----------------------------------------------------------------------
//--------------------------SecTile1------------------------------------
//----------------------------------------------------------------------


SecTile1* SecTile1::cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { return this; } 
SecTile2* SecTile1::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
// копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile2::Nx*(1 - abs(sx))+abs(sx); ++ix) 
        for(int iy=0; iy<SecTile2::Ny*(1 - abs(sy))+abs(sy); ++iy) 
            for(int iz=0; iz<SecTile2::Nz*(1 - abs(sz))+abs(sz); ++iz) {
                buf[buf_sz].m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile2::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile2::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile2::Nz-1)] = 
                            m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
                buf[buf_sz].m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile2::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile2::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile2::Nz-1)] = 
                            m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
    }

    //buf[buf_sz].m1 = m1; // при массивах будем делать поэлементно, причем в cast будем подавать сторону, с какой подходим.
    return buf+buf_sz++;
}

  void SecTile1::start(const Model& model){  
    for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
      m1[ix][iy][iz] = model.m1_init;
      m2[ix][iy][iz] = model.m2_init;
      H1[ix][iy][iz] = Vctr(0.,0.,0.);
      H2[ix][iy][iz] = Vctr(0.,0.,0.);
    }
  }

void SecTile1::step_H(const Model& model, indx<3> pos){
  // ТОЛЬКО(!!!) если нам нужны соседи
  SecTile1 *nb[3][3][3], buf[27]; int buf_sz = 0;
  for(int ix=-1; ix<=1; ix++) for(int iy=-1; iy<=1; iy++) for(int iz=-1; iz<=1; iz++) // смотреть за границами области!!!
      nb[ix+1][iy+1][iz+1] = model.data[pos+Indx(ix, iy, iz)]->cast(buf, buf_sz,ix,iy,iz);
  // теперь в nb лежат акутальные пойнтеры

  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    H1[ix][iy][iz] = model.J*(
      nb[1          ][1          ][(iz-1)/Nz+1] -> m2[ix       ][iy       ][(iz-1)%Nz] + 
      nb[(ix-1)/Nx+1][1          ][(iz-1)/Nz+1] -> m2[(ix-1)%Nx][iy       ][(iz-1)%Nz] + 
      nb[1          ][(iy-1)/Ny+1][(iz-1)/Nz+1] -> m2[ix       ][(iy-1)%Ny][(iz-1)%Nz] + 
      nb[(ix-1)/Nx+1][(iy-1)/Ny+1][(iz-1)/Nz+1] -> m2[(ix-1)%Nx][(iy-1)%Ny][(iz-1)%Nz] +
      nb[1          ][1          ][1          ] -> m2[ix       ][iy       ][iz       ] +
      nb[(ix-1)/Nx+1][1          ][1          ] -> m2[(ix-1)%Nx][iy       ][iz       ] + 
      nb[1          ][(iy-1)/Ny+1][1          ] -> m2[ix       ][(iy-1)%Ny][iz       ] + 
      nb[(ix-1)/Nx+1][(iy-1)/Ny+1][1          ] -> m2[(ix-1)%Nx][(iy-1)%Ny][iz       ] ) + model.H_ext;
      //m1[0,0,-1] + m1[-1,0,-1] + m1[0,-1,-1] + m1[-1,-1,-1] + m1[0,0,0] + m1[-1,0,0] + m1[0,-1,0] + m1[-1,-1,0]

    H2[ix][iy][iz] = model.J*(
      nb[1          ][1          ][1          ] -> m1[ix       ][iy       ][iz       ] +
      nb[(ix+1)/Nx+1][1          ][1          ] -> m1[(ix+1)%Nx][iy       ][iz       ] +
      nb[1          ][1          ][(iz+1)/Nz+1] -> m1[ix       ][iy       ][(iz+1)%Nz] + 
      nb[(ix+1)/Nx+1][1          ][(iz+1)/Nz+1] -> m1[(ix+1)%Nx][iy       ][(iz+1)%Nz] +
      nb[1          ][(iy+1)/Ny+1][1          ] -> m1[ix       ][(iy+1)%Ny][iz       ] +
      nb[(ix+1)/Nx+1][(iy+1)/Ny+1][1          ] -> m1[(ix+1)%Nx][(iy+1)%Ny][iz       ] +
      nb[1          ][(iy+1)/Ny+1][(iz+1)/Nz+1] -> m1[ix       ][(iy+1)%Ny][(iz+1)%Nz] + 
      nb[(ix+1)/Nx+1][(iy+1)/Ny+1][(iz+1)/Nz+1] -> m1[(ix+1)%Nx][(iy+1)%Ny][(iz+1)%Nz] ) + model.H_ext;
      //m[0,0,0]+m[1,0,0]+m[0,0,1]+m[1,0,1]+m[0,1,0]+m[1,1,0]+m[0,1,1]+m[1,1,1]
  }

    

}
void SecTile1::step_m(const Model& model, indx<3> pos){ 
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    m1[ix][iy][iz] -=  model.h * (model.gamma * (m1[ix][iy][iz]%H1[ix][iy][iz]) +model.alpha * (m1[ix][iy][iz]%(m1[ix][iy][iz]%H1[ix][iy][iz])));
    m2[ix][iy][iz] -=  model.h * (model.gamma * (m2[ix][iy][iz]%H2[ix][iy][iz]) +model.alpha * (m2[ix][iy][iz]%(m2[ix][iy][iz]%H2[ix][iy][iz])));
    m1[ix][iy][iz]/=m1[ix][iy][iz].abs();
    m2[ix][iy][iz]/=m2[ix][iy][iz].abs();
  }
 }
//----------------------------------------------------------------------
//--------------------------SecTile2------------------------------------
//----------------------------------------------------------------------

SecTile1* SecTile2::cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    // копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile1::Nx*(1 - abs(sx))+abs(sx); ++ix) 
        for(int iy=0; iy<SecTile1::Ny*(1 - abs(sy))+abs(sy); ++iy) 
            for(int iz=0; iz<SecTile1::Nz*(1 - abs(sz))+abs(sz); ++iz) {
                buf[buf_sz].m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile1::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile1::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile1::Nz-1)] = 
                            m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
                buf[buf_sz].m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile1::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile1::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile1::Nz-1)] = 
                            m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
    }
    // buf[buf_sz].m1 = m1;
    return buf+buf_sz++;
}
SecTile2* SecTile2::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { return this; } 
SecTile3* SecTile2::cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    // копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile3::Nx*(1 - abs(sx))+abs(sx); ++ix) 
        for(int iy=0; iy<SecTile3::Ny*(1 - abs(sy))+abs(sy); ++iy) 
            for(int iz=0; iz<SecTile3::Nz*(1 - abs(sz))+abs(sz); ++iz) {
                buf[buf_sz].m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile3::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile3::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile3::Nz-1)] = 
                            m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
                buf[buf_sz].m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile3::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile3::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile3::Nz-1)] = 
                            m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
    }
    // buf[buf_sz].m1 = m1;
    return buf+buf_sz++;
}
void SecTile2::start(const Model& model){ 
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
      m1[ix][iy][iz] = model.m1_init;
      m2[ix][iy][iz] = model.m2_init;
      H1[ix][iy][iz] = Vctr(0.,0.,0.);
      H2[ix][iy][iz] = Vctr(0.,0.,0.);
  }
} 

void SecTile2::step_H(const Model& model, indx<3> pos){
  // ТОЛЬКО(!!!) если нам нужны соседи
  SecTile2 *nb[3][3][3], buf[27]; int buf_sz = 0;
  for(int ix=-1; ix<=1; ix++) for(int iy=-1; iy<=1; iy++) for(int iz=-1; iz<=1; iz++) // смотреть за границами области!!!
    nb[ix+1][iy+1][iz+1] = model.data[pos+Indx(ix, iy, iz)]->cast(buf, buf_sz,ix,iy,iz);
  // теперь в nb лежат акутальные пойнтеры
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    H1[ix][iy][iz] = model.J*(
      nb[(ix-1)/Nx+1][1          ][1          ] -> m1[(ix-1)%Nx][iy       ][iz       ] + 
      nb[(ix+1)/Nx+1][1          ][1          ] -> m1[(ix+1)%Nx][iy       ][iz       ] +
      nb[1          ][(iy-1)/Ny+1][1          ] -> m1[ix       ][(iy-1)%Ny][iz       ] + 
      nb[1          ][(iy+1)/Ny+1][1          ] -> m1[ix       ][(iy+1)%Ny][iz       ] +
      nb[1          ][1          ][(iz+1)/Nz+1] -> m1[ix       ][iy       ][(iz+1)%Nz] + 
      
      nb[1          ][1          ][(iz-1)/Nz+1] -> m2[ix       ][iy       ][(iz-1)%Nz] + 
      nb[(ix-1)/Nx+1][1          ][(iz-1)/Nz+1] -> m2[(ix-1)%Nx][iy       ][(iz-1)%Nz] + 
      nb[1          ][(iy-1)/Ny+1][(iz-1)/Nz+1] -> m2[ix       ][(iy-1)%Ny][(iz-1)%Nz] + 
      nb[(ix-1)/Nx+1][(iy-1)/Ny+1][(iz-1)/Nz+1] -> m2[(ix-1)%Nx][(iy-1)%Ny][(iz-1)%Nz] ) + model.H_ext;
      //m[-1,0,0]+m[1,0,0]+m[0,-1,0]+m[0,1,0]+m[0,0,1] + m1[0,0,-1] + m1[-1,0,-1] + m1[0,-1,-1] + m1[-1,-1,-1]
  }
}
void SecTile2::step_m(const Model& model, indx<3> pos){
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    m1[ix][iy][iz] = m1[ix][iy][iz] - model.h * (model.gamma * (m1[ix][iy][iz]%H1[ix][iy][iz]) +model.alpha * (m1[ix][iy][iz]%(m1[ix][iy][iz]%H1[ix][iy][iz])));
    m1[ix][iy][iz]/=m1[ix][iy][iz].abs();
  }
}

//----------------------------------------------------------------------
//--------------------------SecTile3------------------------------------
//----------------------------------------------------------------------


SecTile2* SecTile3::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    // копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile2::Nx*(1 - abs(sx))+abs(sx); ++ix) 
        for(int iy=0; iy<SecTile2::Ny*(1 - abs(sy))+abs(sy); ++iy) 
            for(int iz=0; iz<SecTile2::Nz*(1 - abs(sz))+abs(sz); ++iz) {
                buf[buf_sz].m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile2::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile2::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile2::Nz-1)] = 
                            m1[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
                buf[buf_sz].m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(SecTile2::Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(SecTile2::Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(SecTile2::Nz-1)] = 
                            m2[(1-abs(sx))*ix + abs(sx) * (int)((1-sx)*0.5)*(Nx-1)]
                              [(1-abs(sy))*iy + abs(sy) * (int)((1-sy)*0.5)*(Ny-1)]
                              [(1-abs(sz))*iz + abs(sz) * (int)((1-sz)*0.5)*(Nz-1)];
    }
    // buf[buf_sz].m1 = m1;
    return buf+buf_sz++;
}
SecTile3* SecTile3::cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { return this; } 
  
void SecTile3::start(const Model& model){
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
      m1[ix][iy][iz] = model.m1_init;
      m2[ix][iy][iz] = model.m2_init;
      H1[ix][iy][iz] = Vctr(0.,0.,0.);
      H2[ix][iy][iz] = Vctr(0.,0.,0.);
  }
}
void SecTile3::step_H(const Model& model, indx<3> pos){
  // ТОЛЬКО(!!!) если нам нужны соседи
  SecTile3 *nb[3][3][3], buf[27]; int buf_sz = 0;
  for(int ix=-1; ix<=1; ix++) for(int iy=-1; iy<=1; iy++) for(int iz=-1; iz<=1; iz++) // смотреть за границами области!!!
    nb[ix+1][iy+1][iz+1] = model.data[pos+Indx(ix, iy, iz)]->cast(buf, buf_sz,ix,iy,iz);
  // теперь в nb лежат акутальные пойнтеры
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    H1[ix][iy][iz] = model.J*(
      nb[(ix-1)/Nx+1][1          ][1          ] -> m1[(ix-1)%Nx][iy       ][iz       ] + 
      nb[(ix+1)/Nx+1][1          ][1          ] -> m1[(ix+1)%Nx][iy       ][iz       ] +
      nb[1          ][(iy-1)/Ny+1][1          ] -> m1[ix       ][(iy-1)%Ny][iz       ] + 
      nb[1          ][(iy+1)/Ny+1][1          ] -> m1[ix       ][(iy+1)%Ny][iz       ] +
      nb[1          ][1          ][(iz-1)/Nz+1] -> m1[ix       ][iy       ][(iz-1)%Nz] + 
      nb[1          ][1          ][(iz+1)/Nz+1] -> m1[ix       ][iy       ][(iz+1)%Nz] ) + model.H_ext;
  }

}
void SecTile3::step_m(const Model& model, indx<3> pos){ 
  for (int ix = 0; ix < Nx; ++ix) for (int iy = 0; iy < Ny; ++iy)for (int iz = 0; iz < Nz; ++iz){
    m1[ix][iy][iz] = m1[ix][iy][iz] - model.h * (model.gamma * (m1[ix][iy][iz]%H1[ix][iy][iz]) +model.alpha * (m1[ix][iy][iz]%(m1[ix][iy][iz]%H1[ix][iy][iz])));
    m1[ix][iy][iz]/=m1[ix][iy][iz].abs();
  }
 }
//----------------------------------------------------------------------
//--------------------------Model---------------------------------------
//----------------------------------------------------------------------

Model::Model(int nx,int ny,int nz1,int nz2){
    Nx = nx;
    Ny = ny;
    Nz1 = nz1;
    Nz2 = nz2;
    data.init(Indx(Nx+2,Ny+2,Nz1+Nz2+3));
    for (int ix = 0; ix < Nx+2; ++ix) for (int iy = 0; iy < Ny+2; ++iy){
      for (int iz = 0; iz < Nz1+1; ++iz){
        if ((ix==0)||(ix==Nx+1)||(iy==0)||(iy==Ny+1)||(iz==0)) { data[Indx(ix,iy,iz)] = new EmptyTile;} 
        else{data[Indx(ix,iy,iz)] = new SecTile1;}
      }
      for (int iz = Nz1+1; iz < Nz1+2; ++iz){
        if ((ix==0)||(ix==Nx+1)||(iy==0)||(iy==Ny+1)) { data[Indx(ix,iy,iz)] = new EmptyTile;} 
        else{data[Indx(ix,iy,iz)] = new SecTile2;}
      }
      for (int iz = Nz1+2; iz < Nz1+Nz2+3; ++iz){
        if ((ix==0)||(ix==Nx+1)||(iy==0)||(iy==Ny+1)||(iz==Nz1+Nz2+2)) { data[Indx(ix,iy,iz)] = new EmptyTile;} 
        else{data[Indx(ix,iy,iz)] = new SecTile3;}
      }
    }   
  }
Model::~Model(){
    for (int ix = 0; ix < Nx+2; ++ix) for (int iy = 0; iy < Ny+2; ++iy)for (int iz = 0; iz < Nz1+Nz2+3; ++iz){
      delete data[Indx(ix,iy,iz)];
    }   
  }

void Model::start(){
    for (int ix = 1; ix < Nx+1; ++ix) for (int iy = 1; iy < Ny+1; ++iy)for (int iz = 1; iz < Nz1+Nz2+2; ++iz){
      data[Indx(ix,iy,iz)]->start(*this);
    }   

}

void Model::step(int cnt){
    for (int i=0;i<cnt;++i){
        for (int ix = 1; ix < Nx+1; ++ix) for (int iy = 1; iy < Ny+1; ++iy)for (int iz = 1; iz < Nz1+Nz2+2; ++iz){
          data[Indx(ix,iy,iz)]->step_H(*this,Indx(ix,iy,iz));
          data[Indx(ix,iy,iz)]->step_m(*this,Indx(ix,iy,iz));
        }
      time += h;   
    }
}

// void Model::m1_av_calc(){
//   m1_av=Vctr(0,0,0);
//   cnt = 0;
//   for (int ix = 1; ix < Nx+1; ++ix) for (int iy = 1; iy < Ny+1; ++iy)for (int iz = 1; iz < Nz1+Nz2+2; ++iz){
//           data[Indx(ix,iy,iz)]->step_H(*this,Indx(ix,iy,iz));
//           data[Indx(ix,iy,iz)]->step_m(*this,Indx(ix,iy,iz));
//         }
// }


int main()
{
    Model model(6,4,2,2);
    model.H_ext = Vctr(0.,0.,1.);
    model.m1_init = Vctr(1.,0.,0.);
    model.m2_init = Vctr(1.,0.,0.);
    model.J= 1;

    model.alpha= 0.01;
    model.h= 0.05;
    model.gamma= 0.1;

    model.start();
    for (double t = 0; t<5; t+=model.h){
        model.step(1);
    }

  return 0;
}


//g++ --std=c++0x model.cpp -o model.x -laiv -lz