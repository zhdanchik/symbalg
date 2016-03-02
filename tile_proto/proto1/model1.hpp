#ifndef MODEL_HPP
#define MODEL_HPP

class Basetile{
    public:
        virtual void start() = 0;
        virtual void step() = 0;
};

typedef *Basetile ptale

class Model{
    public:
        aiv:array<ptale,3> data;
};

#endif