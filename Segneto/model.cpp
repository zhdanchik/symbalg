#include "model.hpp"
void Model::calc(){
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        p.X += dt*0.5*p.Vx;
        p.Vx += -dt*(a*p.X+b*p.X*p.X*p.X-alpha*M1X-A*sin(Omega*time)+gamma*p.Vx)+sqrt(2.0*gamma*T*dt)*rand_gauss();
        p.X += dt*0.5*p.Vx;
    };
    time += dt;
}
void Model::means(){
    M1X = 0;
    M2X = 0;
    M4X = 0;
    M1V = 0;
    M2V = 0;
    for(auto i = 0; i<f.N; ++i){
        f[i] = 0;
    };
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        M1X += p.X;
        M2X += p.X*p.X;
        M4X += p.X*p.X*p.X*p.X;
        M1V += p.Vx;
        M2V += p.Vx*p.Vx;
        f[Vctr(p.X, p.Vx)] += 1;
    };
    M1X /= partarr.N[0];
    M2X /= partarr.N[0];
    M4X /= partarr.N[0];
    M1V /= partarr.N[0];
    M2V /= partarr.N[0];
    for(auto i = 0; i<f.N; ++i){
        f[i] /= partarr.N[0];
        f[i] /= f.step[0];
        f[i] /= f.step[1];
    };
}
void Model::start(){
    for(auto i = 0; i<partarr.N; ++i){
        part& p = partarr[i];
        p.X = 1.0;
        p.Vx = 0.0;
    };
}