#ifndef MODEL_HPP
#define MODEL_HPP
#include <memory>
#include <array>

template <typename El_type, std::size_t Nx,std::size_t Ny,std::size_t Nz> 
using array3D = std::array<std::array<std::array<El_type, Nz>, Ny>, Nx>;

class Basetile{
    public:
        virtual void start() = 0;
        virtual void step() = 0;
};



class Sec1tale : Basetile{
    constexpr static int Nx = {3};
    constexpr static int Ny = {3};
    constexpr static int Nz = {3};
    array3D<mat1cell, Nx, Ny, Nz> data;

    public:
        virtual void start(){
            return;
        };
        virtual void step(){
            return;
        };  

};

class Sec2tale : Basetile{
    constexpr static int Nx = {3};
    constexpr static int Ny = {3};
    constexpr static int Nz = {3};
    array3D<ptale, Nx, Ny, Nz> data;

    public:
        virtual void start(){
            return;
        };
        virtual void step(){
            return;
        };  

};

class Sec3tale : Basetile{
    constexpr static int Nx = {3};
    constexpr static int Ny = {3};
    constexpr static int Nz = {3};
    array3D<mat2cell, Nx, Ny, Nz> data;

    public:
        virtual void start(){
            return;
        };
        virtual void step(){
            return;
        };  

};


struct mat1cell {
    aiv::vctr<3> H;
    aiv::vctr<3> m;

};

struct mat2cell {
    aiv::vctr<3> H1;
    aiv::vctr<3> m1;
    aiv::vctr<3> H2;
    aiv::vctr<3> m2;

};


class Model{
private:    
    using  ptale = std::unique_ptr<Basetile>; 

public:
    constexpr static int Nx = {3};
    constexpr static int Ny = {3};
    constexpr static int Nz = {3};
    array3D<ptale, Nx, Ny, Nz> data;

};


#endif