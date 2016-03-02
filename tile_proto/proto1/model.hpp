#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>

using namespace aiv;

class Base_cell{
};

class Cell1: public Base_cell{
public:
    aiv::vctr<3,double> m;
    aiv::vctr<3,double> H;
};

class Cell2: public Base_cell{
public:
    aiv::vctr<3,double> m1;
    aiv::vctr<3,double> H1;
    aiv::vctr<3,double> m2;
    aiv::vctr<3,double> H2;
};

typedef Base_cell* pcell;

class Base_tile{
    public:
        double J;
        aiv::vctr<3,double> H_ext;
        typedef Base_tile* ptile;
        double h;
        double gamma;
        double alpha;   
        aiv::array<pcell,3> tile_data;
        aiv::vctr<3,double> m_init;
        aiv::vctr<3,double> m1_init;
        aiv::vctr<3,double> m2_init;

        virtual void start() = 0;
        virtual void step_H(ptile mmm, ptile zmm, ptile pmm, ptile pzm, ptile ppm, ptile zpm, ptile mpm, ptile mzm,
                ptile mmz, ptile zmz, ptile pmz, ptile pzz, ptile ppz, ptile zpz, ptile mpz, ptile mzz,
                ptile mmp, ptile zmp, ptile pmp, ptile pzp, ptile ppp, ptile zpp, ptile mpp, ptile mzp,
                ptile zzm, ptile zzp) = 0;
        virtual void step_m() = 0;
};

typedef Base_tile* ptile;
class Sec1_tale : public Base_tile{

    public:

    void start(){
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H = Vctr(0.,0.,0.);
        
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m = m_init;
    };
    // void step_H(ptile xp,ptile xm,ptile yp,ptile ym,ptile zp,ptile zm  ){
    void step_H(ptile mmm, ptile zmm, ptile pmm, ptile pzm, ptile ppm, ptile zpm, ptile mpm, ptile mzm,
                ptile mmz, ptile zmz, ptile pmz, ptile pzz, ptile ppz, ptile zpz, ptile mpz, ptile mzz,
                ptile mmp, ptile zmp, ptile pmp, ptile pzp, ptile ppp, ptile zpp, ptile mpp, ptile mzp,
                ptile zzm, ptile zzp){
       dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,0,0)]) -> m+
               dynamic_cast<Cell1*>(zmz->tile_data[Indx(0,1,0)]) -> m+
               dynamic_cast<Cell1*>(zzm->tile_data[Indx(0,0,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])  -> m
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)]) -> m+
               dynamic_cast<Cell1*>(zmz->tile_data[Indx(1,0,0)]) -> m+
               dynamic_cast<Cell1*>(zzm->tile_data[Indx(1,0,0)]) -> m+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,0,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])  -> m
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)]) -> m+
               dynamic_cast<Cell1*>(zzm->tile_data[Indx(1,1,1)]) -> m+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,0)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(1,0,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])  -> m
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,1,0)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)]) -> m+
               dynamic_cast<Cell1*>(zzm->tile_data[Indx(0,1,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(0,0,0)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])  -> m
              )+H_ext;     

        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,0,1)]) -> m+
               dynamic_cast<Cell1*>(zmz->tile_data[Indx(0,1,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])  -> m+
               dynamic_cast<Cell1*>(zzp->tile_data[Indx(0,0,0)])  -> m
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)]) -> m+
               dynamic_cast<Cell1*>(zmz->tile_data[Indx(1,1,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)]) -> m+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,0,1)])  -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])  -> m+
               dynamic_cast<Cell1*>(zzp->tile_data[Indx(1,0,0)])  -> m
              )+H_ext;
 
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)]) -> m+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,1)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(1,0,1)])  -> m+
               dynamic_cast<Cell1*>(zzp->tile_data[Indx(1,1,0)])  -> m
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,1,1)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)]) -> m+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(0,0,1)])  -> m+
               dynamic_cast<Cell1*>(zzp->tile_data[Indx(0,1,0)])  -> m
              )+H_ext;

    }
    void step_m(){
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,0)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,0)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H));
    };  

};

/*----------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
----------------------------------------------------*/

class Sec3_tale : public Base_tile{

    public:

        
    void start(){
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H1 = Vctr(0.,0.,0.);
        
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H2 = Vctr(0.,0.,0.);

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m1 = m1_init;
        
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m2 = m2_init;


    };
    void step_H(ptile mmm, ptile zmm, ptile pmm, ptile pzm, ptile ppm, ptile zpm, ptile mpm, ptile mzm,
                ptile mmz, ptile zmz, ptile pmz, ptile pzz, ptile ppz, ptile zpz, ptile mpz, ptile mzz,
                ptile mmp, ptile zmp, ptile pmp, ptile pzp, ptile ppp, ptile zpp, ptile mpp, ptile mzp,
                ptile zzm, ptile zzp){

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzm->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(mmm->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(1,0,1)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(1,1,1)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzm->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(mzm->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,1,1)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m2
            )+H_ext;

         dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2
            )+H_ext;

         dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m2
            )+H_ext;

         dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m2
            )+H_ext;

         dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m2
            )+H_ext;



        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m1+

             dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,0)]) -> m1+

             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,1)]) -> m1
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2 = 
          J*(dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(ppz->tile_data[Indx(0,0,0)]) -> m1+

             dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(ppz->tile_data[Indx(0,0,1)]) -> m1
            )+H_ext;


        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2 = 
          J*(dynamic_cast<Cell2*>(zpz->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,0)]) -> m1+

             dynamic_cast<Cell2*>(zpz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,1)]) -> m1
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H2 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+

             dynamic_cast<Cell2*>(zzp->tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,1,0)]) -> m1
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H2 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,1)]) -> m1+

             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzp->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzp->tile_data[Indx(0,1,0)]) -> m1
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H2 = 
          J*(dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(ppz->tile_data[Indx(0,0,1)]) -> m1+

             dynamic_cast<Cell2*>(zpp->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(pzp->tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(ppp->tile_data[Indx(0,0,0)]) -> m1
            )+H_ext;


        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H2 = 
          J*(dynamic_cast<Cell2*>(zpz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)]) -> m1+
             dynamic_cast<Cell2*>(zpz->tile_data[Indx(1,0,1)]) -> m1+

             dynamic_cast<Cell2*>(zpp->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(0,1,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,1,0)]) -> m1+
             dynamic_cast<Cell2*>(zpp->tile_data[Indx(1,0,0)]) -> m1
            )+H_ext;
   }
    void step_m(){
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H1));

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,1)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,1)])->H2));
    };  

};

class Sec2_tale : public Base_tile{

    public:
        
    void start(){
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1 = Vctr(0.,0.,0.);

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2 = Vctr(0.,0.,0.);
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2 = Vctr(0.,0.,0.);
 
        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H = Vctr(0.,0.,0.);
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H = Vctr(0.,0.,0.);

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1 = m1_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1 = m1_init;

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2 = m2_init;
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2 = m2_init;

        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m = m_init;
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m = m_init;

    }
        void step_H(ptile mmm, ptile zmm, ptile pmm, ptile pzm, ptile ppm, ptile zpm, ptile mpm, ptile mzm,
                ptile mmz, ptile zmz, ptile pmz, ptile pzz, ptile ppz, ptile zpz, ptile mpz, ptile mzz,
                ptile mmp, ptile zmp, ptile pmp, ptile pzp, ptile ppp, ptile zpp, ptile mpp, ptile mzp,
                ptile zzm, ptile zzp){

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzm->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(mmm->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1 = 
          J*(dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmm->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zzm->tile_data[Indx(1,0,1)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2 = 
          J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)]) -> m+

             dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)]) -> m
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2 = 
          J*(dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,0)]) -> m+

             dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,1)]) -> m
            )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)]) -> m+
               dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
               dynamic_cast<Cell2*>(zzm->tile_data[Indx(1,0,1)]) -> m2+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,0)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(1,0,0)])  -> m+

               dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)]) -> m+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,1)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(1,0,1)])  -> m
               
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(0,1,0)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,1,0)]) -> m+
               dynamic_cast<Cell2*>(mzm->tile_data[Indx(1,0,1)]) -> m2+
               dynamic_cast<Cell2*>(zzm->tile_data[Indx(0,0,1)]) -> m2+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])  -> m+
               dynamic_cast<Cell1*>(mpz->tile_data[Indx(0,0,0)])  -> m+

               dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,1,1)]) -> m+
               dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(0,0,1)])  -> m
               
              )+H_ext;




         dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+

             dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,1)]) -> m2+
             dynamic_cast<Cell2*>(mmz->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H1 = 
          J*(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,0)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(1,1,0)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2+

             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(0,1,1)]) -> m2+
             dynamic_cast<Cell2*>(zmz->tile_data[Indx(1,1,1)]) -> m2+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m2
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)])->H2 = 
          J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)]) -> m+

             dynamic_cast<Cell1*>(zzp->tile_data[Indx(0,1,0)]) -> m+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell1*>(zzp->tile_data[Indx(1,1,0)]) -> m
            )+H_ext;

        dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)])->H2 = 
          J*(dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)]) -> m+
             dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m1+
             dynamic_cast<Cell2*>(pzz->tile_data[Indx(0,0,1)]) -> m1+
             dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,1)]) -> m+

             dynamic_cast<Cell1*>(zzp->tile_data[Indx(1,1,0)]) -> m+
             dynamic_cast<Cell2*>(zzp->tile_data[Indx(1,0,0)]) -> m1+
             dynamic_cast<Cell2*>(pzp->tile_data[Indx(0,0,0)]) -> m1+
             dynamic_cast<Cell1*>(pzp->tile_data[Indx(0,1,0)]) -> m
            )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H = 
            J*(dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)]) -> m+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)]) -> m2+
               dynamic_cast<Cell1*>(pzz->tile_data[Indx(0,1,1)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(1,0,1)])  -> m+

               dynamic_cast<Cell1*>(zzp->tile_data[Indx(0,1,0)]) -> m+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(1,0,1)]) -> m2+
               dynamic_cast<Cell1*>(pzp->tile_data[Indx(0,1,0)])  -> m+
               dynamic_cast<Cell1*>(zpp->tile_data[Indx(1,0,0)])  -> m
               
              )+H_ext;

        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H = 
            J*(dynamic_cast<Cell1*>(mzz->tile_data[Indx(1,1,1)]) -> m+
               dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,0)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)]) -> m2+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])  -> m+
               dynamic_cast<Cell1*>(mpz->tile_data[Indx(0,0,1)])  -> m+

               dynamic_cast<Cell1*>(mzp->tile_data[Indx(1,1,0)]) -> m+
               dynamic_cast<Cell2*>(mzz->tile_data[Indx(1,0,1)]) -> m2+
               dynamic_cast<Cell2*>(tile_data[Indx(0,0,1)]) -> m2+
               dynamic_cast<Cell1*>(tile_data[Indx(1,1,0)])  -> m+
               dynamic_cast<Cell1*>(zpz->tile_data[Indx(0,0,0)])  -> m
               
              )+H_ext;
   }

       void step_m(){
        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H1));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m1%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H1));

        dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,0,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(0,1,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,0,0)])->H2));
        dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2 -= h*(gamma*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2+alpha*dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%(dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->m2%dynamic_cast<Cell2*>(tile_data[Indx(1,1,0)])->H2));

        dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,0,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(0,1,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,0,1)])->H));
        dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m -= h*(gamma*dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H+alpha*dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%(dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->m%dynamic_cast<Cell1*>(tile_data[Indx(1,1,1)])->H));

    };  

};
class Model{
    int Nx;
    int Ny; 
    int Nz1;
    int Nz2;
    int Nz3;
    int Mat1h;
    int Mat1n2h;
    int Mat2h;

    public:
        aiv::array<ptile,3> data;

    void start() {
      for (auto I = Indx(0,0,0); I.less(Indx(Nx, Ny, Mat2h)); ++I){
        data[I] = new Sec3_tale();
      }
      for (auto I = Indx(0,0,Mat2h); I.less(Indx(Nx, Ny, Mat2h+Mat1n2h)); ++I){
          data[I] = new Sec2_tale();
      }
      for (auto I = Indx(0,0,Mat2h+Mat1n2h); I.less(Indx(Nx, Ny, Mat2h+Mat1n2h+Mat1h)); ++I){
          data[I] = new Sec1_tale();
      }

      for (auto I = Indx(0,0,0); I.less(data.N); ++I){
        data[I]->start();
      }
    }  

      void calc() {
        for (auto I = Indx(1,1,1); I.less(data.N-Indx(1,1,1)); ++I){
          data[I]->step_H(
                data[I+Indx(-1,-1,-1)], data[I+Indx(0,-1,-1)], data[I+Indx(1,-1,-1)], data[I+Indx(1,0,-1)], data[I+Indx(1,1,-1)], data[I+Indx(0,1,-1)], data[I+Indx(-1,1,-1)], data[I+Indx(-1,0,-1)],
                data[I+Indx(-1,-1, 0)], data[I+Indx(0,-1, 0)], data[I+Indx(1,-1, 0)], data[I+Indx(1,0, 0)], data[I+Indx(1,1, 0)], data[I+Indx(0,1, 0)], data[I+Indx(-1,1, 0)], data[I+Indx(-1,0, 0)],
                data[I+Indx(-1,-1, 1)], data[I+Indx(0,-1, 1)], data[I+Indx(1,-1, 1)], data[I+Indx(1,0, 1)], data[I+Indx(1,1, 1)], data[I+Indx(0,1, 1)], data[I+Indx(-1,1, 1)], data[I+Indx(-1,0, 1)],
                data[I+Indx(0,0, -1)], data[I+Indx(0,0, 1)]);
          data[I]->step_m();
        }
      }

};

#endif