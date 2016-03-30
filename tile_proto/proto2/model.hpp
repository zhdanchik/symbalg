// вариант с виртуальными методами для стадий, размещенных в тэйлах

#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;

struct BaseTile;
struct SecTile1;
struct SecTile2;
struct SecTile3;
struct EmptyTile;

class Model{
public:
	array<BaseTile*, 3> data;
	void set_tile(BaseTile* tile, const aiv::indx<3> &pos){ data[pos] = tile; }
	// здесь всякие параметры
	aiv::vctr<3,double> H_ext;
	aiv::vctr<3,double> m1_init;
	aiv::vctr<3,double> m2_init;
	double J;
	double time;
	double alpha;
	double h;
	double gamma;

	int Nx,Ny,Nz1,Nz2;
	// инициализация и обход
	Model(int nx,int ny,int nz1,int nz2);
	~Model();
	void start();
	void step(int cnt);
	aiv::vctr<3,double> M1();
};


struct BaseTile{
	const int Np;

	BaseTile(int np = 0): Np(np) {}
	virtual ~BaseTile(){}
// интерфейсы для стадий и инициализации
	virtual void start(const Model& model) = 0;
	virtual void step_H(const Model& model, indx<3> pos) = 0;
	virtual void step_m(const Model& model, indx<3> pos) = 0;
	virtual aiv::vctr<3,double> M1() = 0;

// функции для приведения типов наследников
	virtual SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
	virtual SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
	virtual SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
};

struct EmptyTile: public BaseTile{
	const int Np = 0;
	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

	void start(const Model& model) {};
	void step_H(const Model& model, indx<3> pos) {} ;
	void step_m(const Model& model, indx<3> pos) {};
    aiv::vctr<3,double> M1() {return Vctr(0.0,0.0,0.0);}
};


struct SecTile1: public BaseTile{
// всякие данные
	static const int Nx=2, Ny=2, Nz=4;

#ifndef SWIG
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];
#endif	

	SecTile1() : BaseTile(32) {};

// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
	aiv::vctr<3,double> M1();
};

struct SecTile2: public BaseTile{
	static const int Nx=2, Ny=2, Nz=1;

// всякие данные
#ifndef SWIG
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];
#endif	

	SecTile2() : BaseTile(4) {};
// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
	aiv::vctr<3,double> M1();
};

struct SecTile3: public BaseTile{
	static const int Nx=2, Ny=2, Nz=3;
// всякие данные
#ifndef SWIG
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];
#endif	

	SecTile3() : BaseTile(12) {};
// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
	aiv::vctr<3,double> M1();
};

#endif


// комментарии и, возможно, спорные решения

// Хранить в каждом классе наследника тайлов Nx,Ny,Nz, как static const

// при касте от одного к другому нам, по сути, нужно заполнить не весь массив, а только прилегающий слой, шириной 1. Остальное оставляем нетронутым.

// Например, в интерфейсной части (sec2) есть связи с m2, которые лежат в нижей части (Sec1), хотя в ней сам m2 не содержится. 
// Т.е. мы будем кастить Sec1 в Sec2, надеясь, что там будет лежать m2. Получается, нам нужно хранить лишние поля m2 и во всей интерфейсной части.

// текущий, вычисляемый тайл тоже загоняем в массив соседей nb с индексом [0][0][0], чтобы оставить цикл в покое
