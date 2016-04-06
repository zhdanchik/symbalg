#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.magnu import *

def_type = "vctr<3>"

@statement
def step1():
    m = m - h *( gamma*(m%Heff)+alpha*(m%(m%Heff)))
    m /= m.abs()
    m._type = def_type



mk_module("magnu_test", globals())