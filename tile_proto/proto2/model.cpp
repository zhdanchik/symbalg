#include "model.hpp"


// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!

SecTile1* SecTile1::cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { return this; } 
SecTile2* SecTile1::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 

    if ((sy+sz)*(Nx-SecTile2::Nx) + (sx+sz)*(Ny-SecTile2::Ny) + (sx+sy)*(Nz-SecTile2::Nz) != 0 ) {raise("Incorrect cast from SecTile1 to SecTile2")}
    // копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile2::Nx*(abs(sy) + abs(sz)); ix++) 
        for(int iy=0; iy<=SecTile2::Ny*(abs(sx) + abs(sz)); iy++) 
            for(int iz=0; iz<=SecTile2::Nz*(abs(sx) + abs(sy)); iz++) {
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


SecTile1* SecTile2::cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    if ((sy+sz)*(Nx-SecTile1::Nx) + (sx+sz)*(Ny-SecTile1::Ny) + (sx+sy)*(Nz-SecTile1::Nz) != 0 ) {raise("Incorrect cast from SecTile1 to SecTile2")}
    // копируем данные в buf[buf_sz]
    for(int ix=0; ix<SecTile1::Nx*(abs(sy) + abs(sz)); ix++) 
        for(int iy=0; iy<=SecTile1::Ny*(abs(sx) + abs(sz)); iy++) 
            for(int iz=0; iz<=SecTile1::Nz*(abs(sx) + abs(sy)); iz++) {
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
SecTile2* SecTile2::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { return this; } 
SecTile3* SecTile2::cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    // копируем данные в buf[buf_sz]
    if ((sy+sz)*(Nx-SecTile3::Nx) + (sx+sz)*(Ny-SecTile3::Ny) + (sx+sy)*(Nz-SecTile3::Nz) != 0 ) {raise("Incorrect cast from SecTile1 to SecTile2")}
    for(int ix=0; ix<SecTile3::Nx*(abs(sy) + abs(sz)); ix++) 
        for(int iy=0; iy<=SecTile3::Ny*(abs(sx) + abs(sz)); iy++) 
            for(int iz=0; iz<=SecTile3::Nz*(abs(sx) + abs(sy)); iz++) {
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

SecTile2* SecTile3::cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { 
    // копируем данные в buf[buf_sz]
    if ((sy+sz)*(Nx-SecTile2::Nx) + (sx+sz)*(Ny-SecTile2::Ny) + (sx+sy)*(Nz-SecTile2::Nz) != 0 ) {raise("Incorrect cast from SecTile1 to SecTile2")}
    for(int ix=0; ix<SecTile2::Nx*(abs(sy) + abs(sz)); ix++) 
        for(int iy=0; iy<=SecTile2::Ny*(abs(sx) + abs(sz)); iy++) 
            for(int iz=0; iz<=SecTile2::Nz*(abs(sx) + abs(sy)); iz++) {
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


int main()
{
  return 0;
}


//g++ --std=c++0x model.cpp -o model.x -laiv -lz