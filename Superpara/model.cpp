#include "model.hpp"
void Model::calc(){
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        p.m = rotop(p.m)(-alpha*dt*(Hext+A*sin(Omega*time)+k*pow((k*p.m), 2))).val;
        p.m -= gamma*dt*p.m%(p.m%(Hext+A*sin(Omega*time)+k*pow((k*p.m), 2)));
        p.m = rotate(rotate(p.m, rand_alpha2PI*random(), p.m%ort(p.m)/(p.m%ort(p.m)).abs()), 2*sqrt(gamma*dt*T)*rand_gauss(), p.m);
    };
    time += dt;
}
void Model::means(){
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        M1 += p.m;
        M2 += p.m*p.m;
        f[p.m] += One;
    };
    M1 /= partarr.N[0];
    M2 /= partarr.N[0];
    for(auto i = 0; i<f.N; ++i){
        f[i] /= 4*M_PI*partarr.N[0]/(240^f.R);
    };
}
void Model::start(){
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        p.m = Vctr(0, 0, 1);
    };
}