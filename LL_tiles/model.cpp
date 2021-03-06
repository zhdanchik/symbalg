#include "model.hpp"






 void tile0::start(){
    H[0, 0, 0] = Vctr(0.0, 0.0, 0.0);
    m[0, 0, 0] = Model::m_init;
}
 void tile0::step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp){
    H[0, 0, 0] = Model::J*(m1[0, 0, -1]+m1[-1, 0, -1]+m1[0, -1, -1]+m1[-1, -1, -1]+m1[0, 0, 0]+m1[-1, 0, 0]+m1[0, -1, 0]+m1[-1, -1, 0])+Model::H_ext;
    H[0, 0, 1] = Model::J*(m1[0, 0, 0]+m1[-1, 0, 0]+m1[0, -1, 0]+m1[-1, -1, 0]+m1[0, 0, 1]+m1[-1, 0, 1]+m1[0, -1, 1]+m1[-1, -1, 1])+Model::H_ext;
    H[0, 1, 0] = Model::J*(m1[0, 1, -1]+m1[-1, 1, -1]+m1[0, 0, -1]+m1[-1, 0, -1]+m1[0, 1, 0]+m1[-1, 1, 0]+m1[0, 0, 0]+m1[-1, 0, 0])+Model::H_ext;
    H[0, 1, 1] = Model::J*(m1[0, 1, 0]+m1[-1, 1, 0]+m1[0, 0, 0]+m1[-1, 0, 0]+m1[0, 1, 1]+m1[-1, 1, 1]+m1[0, 0, 1]+m1[-1, 0, 1])+Model::H_ext;
    H[1, 0, 0] = Model::J*(m1[1, 0, -1]+m1[0, 0, -1]+m1[1, -1, -1]+m1[0, -1, -1]+m1[1, 0, 0]+m1[0, 0, 0]+m1[1, -1, 0]+m1[0, -1, 0])+Model::H_ext;
    H[1, 0, 1] = Model::J*(m1[1, 0, 0]+m1[0, 0, 0]+m1[1, -1, 0]+m1[0, -1, 0]+m1[1, 0, 1]+m1[0, 0, 1]+m1[1, -1, 1]+m1[0, -1, 1])+Model::H_ext;
    H[1, 1, 0] = Model::J*(m1[1, 1, -1]+m1[0, 1, -1]+m1[1, 0, -1]+m1[0, 0, -1]+m1[1, 1, 0]+m1[0, 1, 0]+m1[1, 0, 0]+m1[0, 0, 0])+Model::H_ext;
    H[1, 1, 1] = Model::J*(m1[1, 1, 0]+m1[0, 1, 0]+m1[1, 0, 0]+m1[0, 0, 0]+m1[1, 1, 1]+m1[0, 1, 1]+m1[1, 0, 1]+m1[0, 0, 1])+Model::H_ext;
    H1[0, 0, 0] = Model::J*(m[0, 0, 0]+m[1, 0, 0]+m[0, 0, 1]+m[1, 0, 1]+m[0, 1, 0]+m[1, 1, 0]+m[0, 1, 1]+m[1, 1, 1])+Model::H_ext;
    H1[0, 0, 1] = Model::J*(m[0, 0, 1]+m[1, 0, 1]+m[0, 0, 2]+m[1, 0, 2]+m[0, 1, 1]+m[1, 1, 1]+m[0, 1, 2]+m[1, 1, 2])+Model::H_ext;
    H1[0, 1, 0] = Model::J*(m[0, 1, 0]+m[1, 1, 0]+m[0, 1, 1]+m[1, 1, 1]+m[0, 2, 0]+m[1, 2, 0]+m[0, 2, 1]+m[1, 2, 1])+Model::H_ext;
    H1[0, 1, 1] = Model::J*(m[0, 1, 1]+m[1, 1, 1]+m[0, 1, 2]+m[1, 1, 2]+m[0, 2, 1]+m[1, 2, 1]+m[0, 2, 2]+m[1, 2, 2])+Model::H_ext;
    H1[1, 0, 0] = Model::J*(m[1, 0, 0]+m[2, 0, 0]+m[1, 0, 1]+m[2, 0, 1]+m[1, 1, 0]+m[2, 1, 0]+m[1, 1, 1]+m[2, 1, 1])+Model::H_ext;
    H1[1, 0, 1] = Model::J*(m[1, 0, 1]+m[2, 0, 1]+m[1, 0, 2]+m[2, 0, 2]+m[1, 1, 1]+m[2, 1, 1]+m[1, 1, 2]+m[2, 1, 2])+Model::H_ext;
    H1[1, 1, 0] = Model::J*(m[1, 1, 0]+m[2, 1, 0]+m[1, 1, 1]+m[2, 1, 1]+m[1, 2, 0]+m[2, 2, 0]+m[1, 2, 1]+m[2, 2, 1])+Model::H_ext;
    H1[1, 1, 1] = Model::J*(m[1, 1, 1]+m[2, 1, 1]+m[1, 1, 2]+m[2, 1, 2]+m[1, 2, 1]+m[2, 2, 1]+m[1, 2, 2]+m[2, 2, 2])+Model::H_ext;
}
 void tile0::step_m(){
    m[0, 0, 0] = m[0, 0, 0]-Model::h*(Model::gamma*m[0, 0, 0]%H[0, 0, 0]+Model::alpha*m[0, 0, 0]%(m[0, 0, 0]%H[0, 0, 0]));
    m[0, 0, 1] = m[0, 0, 1]-Model::h*(Model::gamma*m[0, 0, 1]%H[0, 0, 1]+Model::alpha*m[0, 0, 1]%(m[0, 0, 1]%H[0, 0, 1]));
    m[0, 1, 0] = m[0, 1, 0]-Model::h*(Model::gamma*m[0, 1, 0]%H[0, 1, 0]+Model::alpha*m[0, 1, 0]%(m[0, 1, 0]%H[0, 1, 0]));
    m[0, 1, 1] = m[0, 1, 1]-Model::h*(Model::gamma*m[0, 1, 1]%H[0, 1, 1]+Model::alpha*m[0, 1, 1]%(m[0, 1, 1]%H[0, 1, 1]));
    m[1, 0, 0] = m[1, 0, 0]-Model::h*(Model::gamma*m[1, 0, 0]%H[1, 0, 0]+Model::alpha*m[1, 0, 0]%(m[1, 0, 0]%H[1, 0, 0]));
    m[1, 0, 1] = m[1, 0, 1]-Model::h*(Model::gamma*m[1, 0, 1]%H[1, 0, 1]+Model::alpha*m[1, 0, 1]%(m[1, 0, 1]%H[1, 0, 1]));
    m[1, 1, 0] = m[1, 1, 0]-Model::h*(Model::gamma*m[1, 1, 0]%H[1, 1, 0]+Model::alpha*m[1, 1, 0]%(m[1, 1, 0]%H[1, 1, 0]));
    m[1, 1, 1] = m[1, 1, 1]-Model::h*(Model::gamma*m[1, 1, 1]%H[1, 1, 1]+Model::alpha*m[1, 1, 1]%(m[1, 1, 1]%H[1, 1, 1]));
    m[0, 0, 0] /= m[0, 0, 0].abs();
    m[0, 0, 1] /= m[0, 0, 1].abs();
    m[0, 1, 0] /= m[0, 1, 0].abs();
    m[0, 1, 1] /= m[0, 1, 1].abs();
    m[1, 0, 0] /= m[1, 0, 0].abs();
    m[1, 0, 1] /= m[1, 0, 1].abs();
    m[1, 1, 0] /= m[1, 1, 0].abs();
    m[1, 1, 1] /= m[1, 1, 1].abs();
    m1[0, 0, 0] = m1[0, 0, 0]-Model::h*(Model::gamma*m1[0, 0, 0]%H1[0, 0, 0]+Model::alpha*m1[0, 0, 0]%(m1[0, 0, 0]%H1[0, 0, 0]));
    m1[0, 0, 1] = m1[0, 0, 1]-Model::h*(Model::gamma*m1[0, 0, 1]%H1[0, 0, 1]+Model::alpha*m1[0, 0, 1]%(m1[0, 0, 1]%H1[0, 0, 1]));
    m1[0, 1, 0] = m1[0, 1, 0]-Model::h*(Model::gamma*m1[0, 1, 0]%H1[0, 1, 0]+Model::alpha*m1[0, 1, 0]%(m1[0, 1, 0]%H1[0, 1, 0]));
    m1[0, 1, 1] = m1[0, 1, 1]-Model::h*(Model::gamma*m1[0, 1, 1]%H1[0, 1, 1]+Model::alpha*m1[0, 1, 1]%(m1[0, 1, 1]%H1[0, 1, 1]));
    m1[1, 0, 0] = m1[1, 0, 0]-Model::h*(Model::gamma*m1[1, 0, 0]%H1[1, 0, 0]+Model::alpha*m1[1, 0, 0]%(m1[1, 0, 0]%H1[1, 0, 0]));
    m1[1, 0, 1] = m1[1, 0, 1]-Model::h*(Model::gamma*m1[1, 0, 1]%H1[1, 0, 1]+Model::alpha*m1[1, 0, 1]%(m1[1, 0, 1]%H1[1, 0, 1]));
    m1[1, 1, 0] = m1[1, 1, 0]-Model::h*(Model::gamma*m1[1, 1, 0]%H1[1, 1, 0]+Model::alpha*m1[1, 1, 0]%(m1[1, 1, 0]%H1[1, 1, 0]));
    m1[1, 1, 1] = m1[1, 1, 1]-Model::h*(Model::gamma*m1[1, 1, 1]%H1[1, 1, 1]+Model::alpha*m1[1, 1, 1]%(m1[1, 1, 1]%H1[1, 1, 1]));
    m1[0, 0, 0] /= m1[0, 0, 0].abs();
    m1[0, 0, 1] /= m1[0, 0, 1].abs();
    m1[0, 1, 0] /= m1[0, 1, 0].abs();
    m1[0, 1, 1] /= m1[0, 1, 1].abs();
    m1[1, 0, 0] /= m1[1, 0, 0].abs();
    m1[1, 0, 1] /= m1[1, 0, 1].abs();
    m1[1, 1, 0] /= m1[1, 1, 0].abs();
    m1[1, 1, 1] /= m1[1, 1, 1].abs();
}
 void tile1::start(){
    H[0, 0, 0] = Vctr(0.0, 0.0, 0.0);
    H1[0, 0, 0] = Vctr(0.0, 0.0, 0.0);
    m[0, 0, 0] = Model::m_init;
    m1[0, 0, 0] = Model::m1_init;
}
 void tile1::step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp){
    H[0, 0, 0] = Model::J*(m1[0, 0, -1]+m1[-1, 0, -1]+m1[0, -1, -1]+m1[-1, -1, -1]+m1[0, 0, 0]+m1[-1, 0, 0]+m1[0, -1, 0]+m1[-1, -1, 0])+Model::H_ext;
    H[0, 1, 0] = Model::J*(m1[0, 1, -1]+m1[-1, 1, -1]+m1[0, 0, -1]+m1[-1, 0, -1]+m1[0, 1, 0]+m1[-1, 1, 0]+m1[0, 0, 0]+m1[-1, 0, 0])+Model::H_ext;
    H[1, 0, 0] = Model::J*(m1[1, 0, -1]+m1[0, 0, -1]+m1[1, -1, -1]+m1[0, -1, -1]+m1[1, 0, 0]+m1[0, 0, 0]+m1[1, -1, 0]+m1[0, -1, 0])+Model::H_ext;
    H[1, 1, 0] = Model::J*(m1[1, 1, -1]+m1[0, 1, -1]+m1[1, 0, -1]+m1[0, 0, -1]+m1[1, 1, 0]+m1[0, 1, 0]+m1[1, 0, 0]+m1[0, 0, 0])+Model::H_ext;
    H[0, 0, 1] = Model::J*(m[-1, 0, 1]+m[1, 0, 1]+m[0, -1, 1]+m[0, 1, 1]+m[0, 0, 2]+m1[0, 0, 0]+m1[-1, 0, 0]+m1[0, -1, 0]+m1[-1, -1, 0])+Model::H_ext;
    H[0, 1, 1] = Model::J*(m[-1, 1, 1]+m[1, 1, 1]+m[0, 0, 1]+m[0, 2, 1]+m[0, 1, 2]+m1[0, 1, 0]+m1[-1, 1, 0]+m1[0, 0, 0]+m1[-1, 0, 0])+Model::H_ext;
    H[1, 0, 1] = Model::J*(m[0, 0, 1]+m[2, 0, 1]+m[1, -1, 1]+m[1, 1, 1]+m[1, 0, 2]+m1[1, 0, 0]+m1[0, 0, 0]+m1[1, -1, 0]+m1[0, -1, 0])+Model::H_ext;
    H[1, 1, 1] = Model::J*(m[0, 1, 1]+m[2, 1, 1]+m[1, 0, 1]+m[1, 2, 1]+m[1, 1, 2]+m1[1, 1, 0]+m1[0, 1, 0]+m1[1, 0, 0]+m1[0, 0, 0])+Model::H_ext;
    H1[0, 0, 0] = Model::J*(m[0, 0, 0]+m[1, 0, 0]+m[0, 0, 1]+m[1, 0, 1]+m[0, 1, 0]+m[1, 1, 0]+m[0, 1, 1]+m[1, 1, 1])+Model::H_ext;
    H1[0, 1, 0] = Model::J*(m[0, 1, 0]+m[1, 1, 0]+m[0, 1, 1]+m[1, 1, 1]+m[0, 2, 0]+m[1, 2, 0]+m[0, 2, 1]+m[1, 2, 1])+Model::H_ext;
    H1[1, 0, 0] = Model::J*(m[1, 0, 0]+m[2, 0, 0]+m[1, 0, 1]+m[2, 0, 1]+m[1, 1, 0]+m[2, 1, 0]+m[1, 1, 1]+m[2, 1, 1])+Model::H_ext;
    H1[1, 1, 0] = Model::J*(m[1, 1, 0]+m[2, 1, 0]+m[1, 1, 1]+m[2, 1, 1]+m[1, 2, 0]+m[2, 2, 0]+m[1, 2, 1]+m[2, 2, 1])+Model::H_ext;
}
 void tile1::step_m(){
    m[0, 0, 0] = m[0, 0, 0]-Model::h*(Model::gamma*m[0, 0, 0]%H[0, 0, 0]+Model::alpha*m[0, 0, 0]%(m[0, 0, 0]%H[0, 0, 0]));
    m[0, 1, 0] = m[0, 1, 0]-Model::h*(Model::gamma*m[0, 1, 0]%H[0, 1, 0]+Model::alpha*m[0, 1, 0]%(m[0, 1, 0]%H[0, 1, 0]));
    m[1, 0, 0] = m[1, 0, 0]-Model::h*(Model::gamma*m[1, 0, 0]%H[1, 0, 0]+Model::alpha*m[1, 0, 0]%(m[1, 0, 0]%H[1, 0, 0]));
    m[1, 1, 0] = m[1, 1, 0]-Model::h*(Model::gamma*m[1, 1, 0]%H[1, 1, 0]+Model::alpha*m[1, 1, 0]%(m[1, 1, 0]%H[1, 1, 0]));
    m[0, 0, 1] = m[0, 0, 1]-Model::h*(Model::gamma*m[0, 0, 1]%H[0, 0, 1]+Model::alpha*m[0, 0, 1]%(m[0, 0, 1]%H[0, 0, 1]));
    m[0, 1, 1] = m[0, 1, 1]-Model::h*(Model::gamma*m[0, 1, 1]%H[0, 1, 1]+Model::alpha*m[0, 1, 1]%(m[0, 1, 1]%H[0, 1, 1]));
    m[1, 0, 1] = m[1, 0, 1]-Model::h*(Model::gamma*m[1, 0, 1]%H[1, 0, 1]+Model::alpha*m[1, 0, 1]%(m[1, 0, 1]%H[1, 0, 1]));
    m[1, 1, 1] = m[1, 1, 1]-Model::h*(Model::gamma*m[1, 1, 1]%H[1, 1, 1]+Model::alpha*m[1, 1, 1]%(m[1, 1, 1]%H[1, 1, 1]));
    m[0, 0, 0] /= m[0, 0, 0].abs();
    m[0, 1, 0] /= m[0, 1, 0].abs();
    m[1, 0, 0] /= m[1, 0, 0].abs();
    m[1, 1, 0] /= m[1, 1, 0].abs();
    m[0, 0, 1] /= m[0, 0, 1].abs();
    m[0, 1, 1] /= m[0, 1, 1].abs();
    m[1, 0, 1] /= m[1, 0, 1].abs();
    m[1, 1, 1] /= m[1, 1, 1].abs();
    m1[0, 0, 0] = m1[0, 0, 0]-Model::h*(Model::gamma*m1[0, 0, 0]%H1[0, 0, 0]+Model::alpha*m1[0, 0, 0]%(m1[0, 0, 0]%H1[0, 0, 0]));
    m1[0, 1, 0] = m1[0, 1, 0]-Model::h*(Model::gamma*m1[0, 1, 0]%H1[0, 1, 0]+Model::alpha*m1[0, 1, 0]%(m1[0, 1, 0]%H1[0, 1, 0]));
    m1[1, 0, 0] = m1[1, 0, 0]-Model::h*(Model::gamma*m1[1, 0, 0]%H1[1, 0, 0]+Model::alpha*m1[1, 0, 0]%(m1[1, 0, 0]%H1[1, 0, 0]));
    m1[1, 1, 0] = m1[1, 1, 0]-Model::h*(Model::gamma*m1[1, 1, 0]%H1[1, 1, 0]+Model::alpha*m1[1, 1, 0]%(m1[1, 1, 0]%H1[1, 1, 0]));
    m1[0, 0, 0] /= m1[0, 0, 0].abs();
    m1[0, 1, 0] /= m1[0, 1, 0].abs();
    m1[1, 0, 0] /= m1[1, 0, 0].abs();
    m1[1, 1, 0] /= m1[1, 1, 0].abs();
}
 void tile2::start(){
    H[0, 0, 0] = Vctr(0.0, 0.0, 0.0);
    m[0, 0, 0] = Model::m_init;
}
 void tile2::step_H(ptile mmm,ptile zmm,ptile pmm,ptile mzm,ptile zzm,ptile pzm,ptile mpm,ptile zpm,ptile ppm,ptile mmz,ptile zmz,ptile pmz,ptile mzz,ptile zzz,ptile pzz,ptile mpz,ptile zpz,ptile ppz,ptile mmp,ptile zmp,ptile pmp,ptile mzp,ptile zzp,ptile pzp,ptile mpp,ptile zpp,ptile ppp){
    H[0, 0, 0] = Model::J*(m[-1, 0, 0]+m[1, 0, 0]+m[0, -1, 0]+m[0, 1, 0]+m[0, 0, -1]+m[0, 0, 1])+Model::H_ext;
    H[0, 0, 1] = Model::J*(m[-1, 0, 1]+m[1, 0, 1]+m[0, -1, 1]+m[0, 1, 1]+m[0, 0, 0]+m[0, 0, 2])+Model::H_ext;
    H[0, 1, 0] = Model::J*(m[-1, 1, 0]+m[1, 1, 0]+m[0, 0, 0]+m[0, 2, 0]+m[0, 1, -1]+m[0, 1, 1])+Model::H_ext;
    H[0, 1, 1] = Model::J*(m[-1, 1, 1]+m[1, 1, 1]+m[0, 0, 1]+m[0, 2, 1]+m[0, 1, 0]+m[0, 1, 2])+Model::H_ext;
    H[1, 0, 0] = Model::J*(m[0, 0, 0]+m[2, 0, 0]+m[1, -1, 0]+m[1, 1, 0]+m[1, 0, -1]+m[1, 0, 1])+Model::H_ext;
    H[1, 0, 1] = Model::J*(m[0, 0, 1]+m[2, 0, 1]+m[1, -1, 1]+m[1, 1, 1]+m[1, 0, 0]+m[1, 0, 2])+Model::H_ext;
    H[1, 1, 0] = Model::J*(m[0, 1, 0]+m[2, 1, 0]+m[1, 0, 0]+m[1, 2, 0]+m[1, 1, -1]+m[1, 1, 1])+Model::H_ext;
    H[1, 1, 1] = Model::J*(m[0, 1, 1]+m[2, 1, 1]+m[1, 0, 1]+m[1, 2, 1]+m[1, 1, 0]+m[1, 1, 2])+Model::H_ext;
}
 void tile2::step_m(){
    m[0, 0, 0] = m[0, 0, 0]-Model::h*(Model::gamma*m[0, 0, 0]%H[0, 0, 0]+Model::alpha*m[0, 0, 0]%(m[0, 0, 0]%H[0, 0, 0]));
    m[0, 0, 1] = m[0, 0, 1]-Model::h*(Model::gamma*m[0, 0, 1]%H[0, 0, 1]+Model::alpha*m[0, 0, 1]%(m[0, 0, 1]%H[0, 0, 1]));
    m[0, 1, 0] = m[0, 1, 0]-Model::h*(Model::gamma*m[0, 1, 0]%H[0, 1, 0]+Model::alpha*m[0, 1, 0]%(m[0, 1, 0]%H[0, 1, 0]));
    m[0, 1, 1] = m[0, 1, 1]-Model::h*(Model::gamma*m[0, 1, 1]%H[0, 1, 1]+Model::alpha*m[0, 1, 1]%(m[0, 1, 1]%H[0, 1, 1]));
    m[1, 0, 0] = m[1, 0, 0]-Model::h*(Model::gamma*m[1, 0, 0]%H[1, 0, 0]+Model::alpha*m[1, 0, 0]%(m[1, 0, 0]%H[1, 0, 0]));
    m[1, 0, 1] = m[1, 0, 1]-Model::h*(Model::gamma*m[1, 0, 1]%H[1, 0, 1]+Model::alpha*m[1, 0, 1]%(m[1, 0, 1]%H[1, 0, 1]));
    m[1, 1, 0] = m[1, 1, 0]-Model::h*(Model::gamma*m[1, 1, 0]%H[1, 1, 0]+Model::alpha*m[1, 1, 0]%(m[1, 1, 0]%H[1, 1, 0]));
    m[1, 1, 1] = m[1, 1, 1]-Model::h*(Model::gamma*m[1, 1, 1]%H[1, 1, 1]+Model::alpha*m[1, 1, 1]%(m[1, 1, 1]%H[1, 1, 1]));
    m[0, 0, 0] /= m[0, 0, 0].abs();
    m[0, 0, 1] /= m[0, 0, 1].abs();
    m[0, 1, 0] /= m[0, 1, 0].abs();
    m[0, 1, 1] /= m[0, 1, 1].abs();
    m[1, 0, 0] /= m[1, 0, 0].abs();
    m[1, 0, 1] /= m[1, 0, 1].abs();
    m[1, 1, 0] /= m[1, 1, 0].abs();
    m[1, 1, 1] /= m[1, 1, 1].abs();
}

