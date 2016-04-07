#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.magnu_str import *

Atom = lambda **kw_args : kw_args

def_type = "vctr<3>"

# Opisanie structurw Atom
# Opisanie poley Model???

@statement
def stage1():
    Heff = Hext + Hexch(m0)
    m1 = m0 - h *( gamma*(m0%Heff)+alpha*(m0%(m0%Heff)))
    m1 /= m1.abs()

@statement
def stage2():
    m0 = m1

@statement
def foo():
    m1 = m0 #fignya dlya primera



mk_module("magnu_test", Atom(m0='vctr<3>', m1='vctr<3>'),
	h='double', Hext='vctr<3>', gamma='double', alpha='double', # opisanie poley Model
	step=[("stage1", stage1), ("stage2", stage2)], foo=[("foo",foo)] # opisanie metdow Model	
	 )
'''
struct Atom{
	vctr<3> m0;
	vctr<3> m1;

	inline void stage1(Model& model, const vctr<3> &Hexch){
		auto Heff = model.Hext + Hexch;
    	m1 = m0 - model.h *( model.gamma*(m0%Heff)+model.alpha*(m0%(m0%Heff)))
    	m1 /= m1.abs()
	}
	inline void stage2(Model& model, const vctr<3> &Hexch){
		m0 = m1;
	}
	inline void foo(Model& model, const vctr<3> &Hexch){
		m1 = m0;
	}
};
'''