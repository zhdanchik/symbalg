// вариант с виртуальными методами для стадий, размещенных в тэйлах

#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
#include <typeinfo>
using namespace aiv;

struct BaseTile;
struct SecTile1;
struct SecTile2;
struct SecTile3;
struct EmptyTile;

class Model{
public:
	array<BaseTile*, 3> data;
	// здесь всякие параметры

	aiv::vctr<3,double> H_ext;
	aiv::vctr<3,double> m1_init;
	aiv::vctr<3,double> m2_init;
	aiv::vctr<3,double> m1_av;
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
	// void m1_av_calc();
};


struct BaseTile{
// интерфейсы для стадий и инициализации
	virtual void start(const Model& model) = 0;
	virtual void step_H(const Model& model, indx<3> pos) = 0;
	virtual void step_m(const Model& model, indx<3> pos) = 0;
	
// функции для приведения типов наследников
	virtual SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
	virtual SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
	virtual SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz) /*const ???*/ { raise("oops..."); }
};

struct EmptyTile: public BaseTile{

	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

	void start(const Model& model) {};
	void step_H(const Model& model, indx<3> pos) {} ;
	void step_m(const Model& model, indx<3> pos) {};

};


struct SecTile1: public BaseTile{
// всякие данные
	static const int Nx=2, Ny=2, Nz=4;
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];

// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
};

struct SecTile2: public BaseTile{
	static const int Nx=2, Ny=2, Nz=1;
// всякие данные
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];

// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile1* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
};

struct SecTile3: public BaseTile{
	static const int Nx=2, Ny=2, Nz=3;
// всякие данные
	vctr<3> m1[Nx][Ny][Nz];
	vctr<3> m2[Nx][Ny][Nz];
	vctr<3> H1[Nx][Ny][Nz];
	vctr<3> H2[Nx][Ny][Nz];

// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile2* cast(SecTile2* buf, int &buf_sz, int sx, int sy, int sz);
	SecTile3* cast(SecTile3* buf, int &buf_sz, int sx, int sy, int sz);

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model);
	void step_H(const Model& model, indx<3> pos);
	void step_m(const Model& model, indx<3> pos);
};

#endif


// комментарии и, возможно, спорные решения

// Хранить в каждом классе наследника тайлов Nx,Ny,Nz, как static const

// при касте от одного к другому нам, по сути, нужно заполнить не весь массив, а только прилегающий слой, шириной 1. Остальное оставляем нетронутым.

// пока не учитываем угловые касты, только по соседней грани. Если нужно будет учитывать в дальнейшем, нужно пересмотреть формулы

// Например, в интерфейсной части (sec2) есть связи с m2, которые лежат в нижей части (Sec1), хотя в ней сам m2 не содержится. 
// Т.е. мы будем кастить Sec1 в Sec2, надеясь, что там будет лежать m2. Получается, нам нужно хранить лишние поля m2 и во всей интерфейсной части.

// текущий, вычисляемый тайл тоже загоняем в массив соседей nb с индексом [0][0][0], чтобы оставить цикл в покое
