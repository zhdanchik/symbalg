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

struct Model{
	array<BaserTile*, 3> data;
	// здесь всякие параметры
};


struct BaseTile{
// интерфейсы для стадий и инициализации
	virtual void start(const Model& model) = 0;
	virtual void step_H(const Model& model, indx<3> pos) = 0;
	virtual void step_m(const Model& model, indx<3> pos) = 0;

// функции для приведения типов наследников
	virtual SecTile1* cast(SecTile1* buf, int &buf_sz) /*const ???*/ { raise("oops..."); }
	virtual SecTile2* cast(SecTile2* buf, int &buf_sz) /*const ???*/ { raise("oops..."); }
};


struct SecTile1: public BaseTile{
// всякие данные
	vctr<3> m1, m2;
// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile1* buf, int &buf_sz) /*const ???*/ { return this; } 
	SecTile2* cast(SecTile2* buf, int &buf_sz) /*const ???*/ { 
		// копируем данные в buf[buf_sz]
		buf[buf_sz].m1 = m1;
		return buf+buf_sz++;
	}

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model){ ... }
	void step_H(const Model& model, indx<3> pos){
		// ТОЛЬКО(!!!) если нам нужны соседи
		SecTile1 *nb[3][3][3], buf[26]; int buf_sz = 0;
		for(int ix=-1; ix<=1; ix++) for(int iy=-1; iy<=1; iy++) for(int iz=-1; iz<=1; iz++) // смотреть за границами области!!!
			nb[ix][iy][iz] = model.data[pos+Indx(ix, iy, iz)].cast(buf, buf_sz);
		// тперь в nb лежат акутальные пойнтеры
	}
	void step_m(const Model& model, indx<3> pos){ ... }
};

struct SecTile2: public BaseTile{
// всякие данные
	vctr<3> m1;
// функции для приведения типов наследников - должны определяться потом, в .cpp, после объявления всех SecTile!!!
	SecTile1* cast(SecTile2* buf, int &buf_sz) /*const ???*/ { 
		// копируем данные в buf[buf_sz]
		buf[buf_sz].m1 = m1;
		return buf+buf_sz++;
	}
	SecTile2* cast(SecTile2* buf, int &buf_sz) /*const ???*/ { return this; } 

// интерфейсы для стадий и инициализации - могут определяться и здесь, но лучше в .cpp
	void start(const Model& model){ ... }
	void step_H(const Model& model, indx<3> pos){
		// ТОЛЬКО(!!!) если нам нужны соседи
		SecTile2 *nb[3][3][3], buf[26]; int buf_sz = 0;
		for(int ix=-1; ix<=1; ix++) for(int iy=-1; iy<=1; iy++) for(int iz=-1; iz<=1; iz++) // смотреть за границами области!!!
			nb[ix][iy][iz] = model.data[pos+Indx(ix, iy, iz)].cast(buf, buf_sz);
		// тперь в nb лежат акутальные пойнтеры
	}
	void step_m(const Model& model, indx<3> pos){ ... }

};


#endif