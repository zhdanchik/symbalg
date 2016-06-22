#include "new_geometry.hpp"


struct RotatedFigure: public BaseFigure{
    BaseFigure* child;
    aiv::vctr<3> center;
    aiv::vctr<3> n_phi;

    RotatedFigure(BaseFigure* tmp, const aiv::vctr<3> &_center, const aiv::vctr<3> &_n_phi):child(tmp), center(_center), n_phi(_n_phi){counter=1;printf("Create Rotated, counter = %d\n",counter);}  
    ~RotatedFigure(){ }  
    void free(){
        child->free();
        counter--;
        printf("Rotated counter dec = %d\n", counter);
        if (counter == 0){
            printf("Delete Rotated\n");
            delete this;
        }
    }

};

BaseFigure* BaseFigure::rotate(const aiv::vctr<3> &center, const aiv::vctr<3> &n_phi) {
    BaseFigure* tmpFigure = new RotatedFigure(this, center, n_phi);    
    counter++;
    printf("Rotate child counter inc = %d\n", counter);
    return tmpFigure;
}

struct Cylinder: public BaseFigure{
    aiv::vctr<3> center; // центр нижней грани
    double R, H;    // радиус и высота
    aiv::vctr<3> n; // направляющая вдоль оси z


    
    Cylinder(const aiv::vctr<3> _center, const aiv::vctr<3> &_n, double _R, double _H):center(_center), n(_n), R(_R), H(_H) {counter=1; printf("Create Cylinder, counter = %d\n",counter);}  
    ~Cylinder(){ }  
    void free(){
        counter--;
        printf("Cylinder counter dec = %d\n", counter);
        if (counter == 0){
            printf("Delete Cylinder\n");
            delete this;
        }
    }

};



BaseFigure* cylinder(const aiv::vctr<3> center, const aiv::vctr<3> &n, double R, double H){
    Cylinder* tmpFigure = new Cylinder(center, n, R, H);
    return tmpFigure;
}

int main(){

    BaseFigure* f1 = cylinder(Vctr(0.,0.,0.),Vctr(0.,0.,1.), 20., 20.);
    BaseFigure* f2 = f1->rotate(Vctr(0.,0.,0.), Vctr(1.,1.,1));
    
    f2->free();
    f1->free();
    

    return 0;
}