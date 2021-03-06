import sys; sys.setdlopenflags(0x00100|sys.getdlopenflags())
# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_model', [dirname(__file__)])
        except ImportError:
            import _model
            return _model
        if fp is not None:
            try:
                _mod = imp.load_module('_model', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _model = swig_import_helper()
    del swig_import_helper
else:
    import _model
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


def _setstate( self, state ):
    if not hasattr( self, 'this' ) : self.__init__()
    self.__C_setstate__(state)
def import_aivlib(tgt) :
    name = tgt.split('-')[0]
    try : exec('import aivlib.'+name)
    except ImportError, e : import os; os.system('make-aivlib %r'%tgt); exec('import aivlib.'+name)
    return eval('aivlib.'+name)
def _swig_setattr(self,class_type,name,value):
    if name in class_type.__swig_setmethods__ : value = getattr( self, name ).__class__(value)
    return _swig_setattr_nondynamic(self,class_type,name,value,0)
__makefile__='model.mk'

class aiv_convert_for_compare_float(_object):
    """Proxy of C++ std::aiv_convert_for_compare_float class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, aiv_convert_for_compare_float, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, aiv_convert_for_compare_float, name)
    __repr__ = _swig_repr
    __swig_setmethods__["flt"] = _model.aiv_convert_for_compare_float_flt_set
    __swig_getmethods__["flt"] = _model.aiv_convert_for_compare_float_flt_get
    if _newclass:flt = _swig_property(_model.aiv_convert_for_compare_float_flt_get, _model.aiv_convert_for_compare_float_flt_set)
    __swig_setmethods__["fix"] = _model.aiv_convert_for_compare_float_fix_set
    __swig_getmethods__["fix"] = _model.aiv_convert_for_compare_float_fix_get
    if _newclass:fix = _swig_property(_model.aiv_convert_for_compare_float_fix_get, _model.aiv_convert_for_compare_float_fix_set)
    def __init__(self): 
        """__init__(std::aiv_convert_for_compare_float self) -> aiv_convert_for_compare_float"""
        this = _model.new_aiv_convert_for_compare_float()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete_aiv_convert_for_compare_float
    __del__ = lambda self : None;
aiv_convert_for_compare_float_swigregister = _model.aiv_convert_for_compare_float_swigregister
aiv_convert_for_compare_float_swigregister(aiv_convert_for_compare_float)

class _base_mem(_object):
    """Proxy of C++ aiv::_base_mem class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _base_mem, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _base_mem, name)
    __repr__ = _swig_repr
    __swig_getmethods__["D"] = _model._base_mem_D_get
    if _newclass:D = _swig_property(_model._base_mem_D_get)
    __swig_getmethods__["szT"] = _model._base_mem_szT_get
    if _newclass:szT = _swig_property(_model._base_mem_szT_get)
    __swig_setmethods__["N"] = _model._base_mem_N_set
    __swig_getmethods__["N"] = _model._base_mem_N_get
    if _newclass:N = _swig_property(_model._base_mem_N_get, _model._base_mem_N_set)
    __swig_setmethods__["owners"] = _model._base_mem_owners_set
    __swig_getmethods__["owners"] = _model._base_mem_owners_get
    if _newclass:owners = _swig_property(_model._base_mem_owners_get, _model._base_mem_owners_set)
    def __init__(self, *args): 
        """__init__(aiv::_base_mem self, int AszT, int AD, int * AN) -> _base_mem"""
        this = _model.new__base_mem(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete__base_mem
    __del__ = lambda self : None;
    def len(self):
        """len(_base_mem self) -> size_t"""
        return _model._base_mem_len(self)

_base_mem_swigregister = _model._base_mem_swigregister
_base_mem_swigregister(_base_mem)

class arr_head(_object):
    """Proxy of C++ aiv::arr_head class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arr_head, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arr_head, name)
    __repr__ = _swig_repr
    __swig_getmethods__["D"] = _model.arr_head_D_get
    if _newclass:D = _swig_property(_model.arr_head_D_get)
    __swig_getmethods__["szT"] = _model.arr_head_szT_get
    if _newclass:szT = _swig_property(_model.arr_head_szT_get)
    __swig_getmethods__["N"] = _model.arr_head_N_get
    if _newclass:N = _swig_property(_model.arr_head_N_get)
    def load(self, *args):
        """load(arr_head self, aiv::Istream & S)"""
        return _model.arr_head_load(self, *args)

    def __init__(self, *args): 
        """
        __init__(aiv::arr_head self) -> arr_head
        __init__(aiv::arr_head self, aiv::Istream & S) -> arr_head
        __init__(aiv::arr_head self, arr_head H) -> arr_head
        """
        this = _model.new_arr_head(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete_arr_head
    __del__ = lambda self : None;
arr_head_swigregister = _model.arr_head_swigregister
arr_head_swigregister(arr_head)

class lrc_head(_object):
    """Proxy of C++ aiv::lrc_head class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, lrc_head, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, lrc_head, name)
    __repr__ = _swig_repr
    __swig_getmethods__["D"] = _model.lrc_head_D_get
    if _newclass:D = _swig_property(_model.lrc_head_D_get)
    __swig_getmethods__["D2"] = _model.lrc_head_D2_get
    if _newclass:D2 = _swig_property(_model.lrc_head_D2_get)
    __swig_getmethods__["szT"] = _model.lrc_head_szT_get
    if _newclass:szT = _swig_property(_model.lrc_head_szT_get)
    __swig_getmethods__["R"] = _model.lrc_head_R_get
    if _newclass:R = _swig_property(_model.lrc_head_R_get)
    __swig_getmethods__["N"] = _model.lrc_head_N_get
    if _newclass:N = _swig_property(_model.lrc_head_N_get)
    __swig_destroy__ = _model.delete_lrc_head
    __del__ = lambda self : None;
    def load(self, *args):
        """load(lrc_head self, aiv::Istream & S)"""
        return _model.lrc_head_load(self, *args)

    def __init__(self, *args): 
        """
        __init__(aiv::lrc_head self) -> lrc_head
        __init__(aiv::lrc_head self, aiv::Istream & S) -> lrc_head
        __init__(aiv::lrc_head self, lrc_head H) -> lrc_head
        """
        this = _model.new_lrc_head(*args)
        try: self.this.append(this)
        except: self.this = this
lrc_head_swigregister = _model.lrc_head_swigregister
lrc_head_swigregister(lrc_head)

class base_sphere(_object):
    """Proxy of C++ aiv::base_sphere class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, base_sphere, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, base_sphere, name)
    __repr__ = _swig_repr
    __swig_getmethods__["R"] = _model.base_sphere_R_get
    if _newclass:R = _swig_property(_model.base_sphere_R_get)
    __swig_getmethods__["N"] = _model.base_sphere_N_get
    if _newclass:N = _swig_property(_model.base_sphere_N_get)
    def get_ref_count(self):
        """get_ref_count(base_sphere self) -> int"""
        return _model.base_sphere_get_ref_count(self)

    def __init__(self, *args): 
        """
        __init__(aiv::base_sphere self, int AR=-1) -> base_sphere
        __init__(aiv::base_sphere self) -> base_sphere
        __init__(aiv::base_sphere self, base_sphere S) -> base_sphere
        """
        this = _model.new_base_sphere(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete_base_sphere
    __del__ = lambda self : None;
    def init(self, *args):
        """init(base_sphere self, int AR)"""
        return _model.base_sphere_init(self, *args)

    def get_cell_id(self, *args):
        """get_cell_id(base_sphere self, aiv::vctr< 3,double > const & r) -> int"""
        return _model.base_sphere_get_cell_id(self, *args)

    def get_cell_vertex(self, *args):
        """get_cell_vertex(base_sphere self, int cid) -> aiv::indx< 3 > const &"""
        return _model.base_sphere_get_cell_vertex(self, *args)

    def get_vertex(self, *args):
        """get_vertex(base_sphere self, int vid) -> aiv::vctr< 3,double > const &"""
        return _model.base_sphere_get_vertex(self, *args)

    def get_cell_neighbours(self, *args):
        """get_cell_neighbours(base_sphere self, int cid) -> aiv::indx< 3 > const &"""
        return _model.base_sphere_get_cell_neighbours(self, *args)

    def get_vertex_cells(self, *args):
        """get_vertex_cells(base_sphere self, int vid) -> aiv::indx< 6 > const &"""
        return _model.base_sphere_get_vertex_cells(self, *args)

    def get_cell_area(self, *args):
        """get_cell_area(base_sphere self, int cid) -> double"""
        return _model.base_sphere_get_cell_area(self, *args)

    def get_coord(self, *args):
        """get_coord(base_sphere self, aiv::vctr< 3,double > * x, long i, int AR)"""
        return _model.base_sphere_get_coord(self, *args)

    def get_nb(self, *args):
        """get_nb(base_sphere self, long * nb, long i, int AR)"""
        return _model.base_sphere_get_nb(self, *args)

    def get_cell_center(self, *args):
        """
        get_cell_center(base_sphere self, int cid) -> aiv::vctr< 3,double > const
        get_cell_center(base_sphere self, long cid, int AR) -> aiv::vctr< 3,double >
        """
        return _model.base_sphere_get_cell_center(self, *args)

base_sphere_swigregister = _model.base_sphere_swigregister
base_sphere_swigregister(base_sphere)
cvar = _model.cvar
MAX_RANK = cvar.MAX_RANK


def barecentr(*args):
  """barecentr(aiv::vctr< 3,double > const & x, aiv::vctr< 3,double > const [3] r) -> aiv::vctr< 3,double >"""
  return _model.barecentr(*args)
class Model(_object):
    """Proxy of C++ Model class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Model, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Model, name)
    __repr__ = _swig_repr
    __swig_setmethods__["data"] = _model.Model_data_set
    __swig_getmethods__["data"] = _model.Model_data_get
    if _newclass:data = _swig_property(_model.Model_data_get, _model.Model_data_set)
    def set_tile(self, *args):
        """set_tile(Model self, BaseTile tile, aiv::indx< 3 > const & pos)"""
        return _model.Model_set_tile(self, *args)

    __swig_setmethods__["H_ext"] = _model.Model_H_ext_set
    __swig_getmethods__["H_ext"] = _model.Model_H_ext_get
    if _newclass:H_ext = _swig_property(_model.Model_H_ext_get, _model.Model_H_ext_set)
    __swig_setmethods__["m1_init"] = _model.Model_m1_init_set
    __swig_getmethods__["m1_init"] = _model.Model_m1_init_get
    if _newclass:m1_init = _swig_property(_model.Model_m1_init_get, _model.Model_m1_init_set)
    __swig_setmethods__["m2_init"] = _model.Model_m2_init_set
    __swig_getmethods__["m2_init"] = _model.Model_m2_init_get
    if _newclass:m2_init = _swig_property(_model.Model_m2_init_get, _model.Model_m2_init_set)
    __swig_setmethods__["J"] = _model.Model_J_set
    __swig_getmethods__["J"] = _model.Model_J_get
    if _newclass:J = _swig_property(_model.Model_J_get, _model.Model_J_set)
    __swig_setmethods__["time"] = _model.Model_time_set
    __swig_getmethods__["time"] = _model.Model_time_get
    if _newclass:time = _swig_property(_model.Model_time_get, _model.Model_time_set)
    __swig_setmethods__["alpha"] = _model.Model_alpha_set
    __swig_getmethods__["alpha"] = _model.Model_alpha_get
    if _newclass:alpha = _swig_property(_model.Model_alpha_get, _model.Model_alpha_set)
    __swig_setmethods__["h"] = _model.Model_h_set
    __swig_getmethods__["h"] = _model.Model_h_get
    if _newclass:h = _swig_property(_model.Model_h_get, _model.Model_h_set)
    __swig_setmethods__["gamma"] = _model.Model_gamma_set
    __swig_getmethods__["gamma"] = _model.Model_gamma_get
    if _newclass:gamma = _swig_property(_model.Model_gamma_get, _model.Model_gamma_set)
    __swig_setmethods__["Nx"] = _model.Model_Nx_set
    __swig_getmethods__["Nx"] = _model.Model_Nx_get
    if _newclass:Nx = _swig_property(_model.Model_Nx_get, _model.Model_Nx_set)
    __swig_setmethods__["Ny"] = _model.Model_Ny_set
    __swig_getmethods__["Ny"] = _model.Model_Ny_get
    if _newclass:Ny = _swig_property(_model.Model_Ny_get, _model.Model_Ny_set)
    __swig_setmethods__["Nz1"] = _model.Model_Nz1_set
    __swig_getmethods__["Nz1"] = _model.Model_Nz1_get
    if _newclass:Nz1 = _swig_property(_model.Model_Nz1_get, _model.Model_Nz1_set)
    __swig_setmethods__["Nz2"] = _model.Model_Nz2_set
    __swig_getmethods__["Nz2"] = _model.Model_Nz2_get
    if _newclass:Nz2 = _swig_property(_model.Model_Nz2_get, _model.Model_Nz2_set)
    def __init__(self, *args): 
        """__init__(Model self, int nx, int ny, int nz1, int nz2) -> Model"""
        this = _model.new_Model(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete_Model
    __del__ = lambda self : None;
    def start(self):
        """start(Model self)"""
        return _model.Model_start(self)

    def step(self, *args):
        """step(Model self, int cnt)"""
        return _model.Model_step(self, *args)

    def M1(self):
        """M1(Model self) -> aiv::vctr< 3,double >"""
        return _model.Model_M1(self)

Model_swigregister = _model.Model_swigregister
Model_swigregister(Model)

class BaseTile(_object):
    """Proxy of C++ BaseTile class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, BaseTile, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, BaseTile, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_getmethods__["Np"] = _model.BaseTile_Np_get
    if _newclass:Np = _swig_property(_model.BaseTile_Np_get)
    __swig_destroy__ = _model.delete_BaseTile
    __del__ = lambda self : None;
    def start(self, *args):
        """start(BaseTile self, Model model)"""
        return _model.BaseTile_start(self, *args)

    def step_H(self, *args):
        """step_H(BaseTile self, Model model, aiv::indx< 3 > pos)"""
        return _model.BaseTile_step_H(self, *args)

    def step_m(self, *args):
        """step_m(BaseTile self, Model model, aiv::indx< 3 > pos)"""
        return _model.BaseTile_step_m(self, *args)

    def M1(self):
        """M1(BaseTile self) -> aiv::vctr< 3,double >"""
        return _model.BaseTile_M1(self)

    def cast(self, *args):
        """
        cast(BaseTile self, SecTile1 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile1
        cast(BaseTile self, SecTile2 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile2
        cast(BaseTile self, SecTile3 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile3
        """
        return _model.BaseTile_cast(self, *args)

BaseTile_swigregister = _model.BaseTile_swigregister
BaseTile_swigregister(BaseTile)

class EmptyTile(BaseTile):
    """Proxy of C++ EmptyTile class"""
    __swig_setmethods__ = {}
    for _s in [BaseTile]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, EmptyTile, name, value)
    __swig_getmethods__ = {}
    for _s in [BaseTile]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, EmptyTile, name)
    __repr__ = _swig_repr
    __swig_getmethods__["Np"] = _model.EmptyTile_Np_get
    if _newclass:Np = _swig_property(_model.EmptyTile_Np_get)
    def cast(self, *args):
        """
        cast(EmptyTile self, SecTile1 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile1
        cast(EmptyTile self, SecTile2 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile2
        cast(EmptyTile self, SecTile3 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile3
        """
        return _model.EmptyTile_cast(self, *args)

    def start(self, *args):
        """start(EmptyTile self, Model model)"""
        return _model.EmptyTile_start(self, *args)

    def step_H(self, *args):
        """step_H(EmptyTile self, Model model, aiv::indx< 3 > pos)"""
        return _model.EmptyTile_step_H(self, *args)

    def step_m(self, *args):
        """step_m(EmptyTile self, Model model, aiv::indx< 3 > pos)"""
        return _model.EmptyTile_step_m(self, *args)

    def M1(self):
        """M1(EmptyTile self) -> aiv::vctr< 3,double >"""
        return _model.EmptyTile_M1(self)

    def __init__(self): 
        """__init__(EmptyTile self) -> EmptyTile"""
        this = _model.new_EmptyTile()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _model.delete_EmptyTile
    __del__ = lambda self : None;
EmptyTile_swigregister = _model.EmptyTile_swigregister
EmptyTile_swigregister(EmptyTile)

class SecTile1(BaseTile):
    """Proxy of C++ SecTile1 class"""
    __swig_setmethods__ = {}
    for _s in [BaseTile]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, SecTile1, name, value)
    __swig_getmethods__ = {}
    for _s in [BaseTile]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, SecTile1, name)
    __repr__ = _swig_repr
    Nx = _model.SecTile1_Nx
    Ny = _model.SecTile1_Ny
    Nz = _model.SecTile1_Nz
    def __init__(self): 
        """__init__(SecTile1 self) -> SecTile1"""
        this = _model.new_SecTile1()
        try: self.this.append(this)
        except: self.this = this
    def cast(self, *args):
        """
        cast(SecTile1 self, SecTile1 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile1
        cast(SecTile1 self, SecTile2 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile2
        """
        return _model.SecTile1_cast(self, *args)

    def start(self, *args):
        """start(SecTile1 self, Model model)"""
        return _model.SecTile1_start(self, *args)

    def step_H(self, *args):
        """step_H(SecTile1 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile1_step_H(self, *args)

    def step_m(self, *args):
        """step_m(SecTile1 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile1_step_m(self, *args)

    def M1(self):
        """M1(SecTile1 self) -> aiv::vctr< 3,double >"""
        return _model.SecTile1_M1(self)

    __swig_destroy__ = _model.delete_SecTile1
    __del__ = lambda self : None;
SecTile1_swigregister = _model.SecTile1_swigregister
SecTile1_swigregister(SecTile1)

class SecTile2(BaseTile):
    """Proxy of C++ SecTile2 class"""
    __swig_setmethods__ = {}
    for _s in [BaseTile]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, SecTile2, name, value)
    __swig_getmethods__ = {}
    for _s in [BaseTile]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, SecTile2, name)
    __repr__ = _swig_repr
    Nx = _model.SecTile2_Nx
    Ny = _model.SecTile2_Ny
    Nz = _model.SecTile2_Nz
    def __init__(self): 
        """__init__(SecTile2 self) -> SecTile2"""
        this = _model.new_SecTile2()
        try: self.this.append(this)
        except: self.this = this
    def cast(self, *args):
        """
        cast(SecTile2 self, SecTile1 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile1
        cast(SecTile2 self, SecTile2 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile2
        cast(SecTile2 self, SecTile3 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile3
        """
        return _model.SecTile2_cast(self, *args)

    def start(self, *args):
        """start(SecTile2 self, Model model)"""
        return _model.SecTile2_start(self, *args)

    def step_H(self, *args):
        """step_H(SecTile2 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile2_step_H(self, *args)

    def step_m(self, *args):
        """step_m(SecTile2 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile2_step_m(self, *args)

    def M1(self):
        """M1(SecTile2 self) -> aiv::vctr< 3,double >"""
        return _model.SecTile2_M1(self)

    __swig_destroy__ = _model.delete_SecTile2
    __del__ = lambda self : None;
SecTile2_swigregister = _model.SecTile2_swigregister
SecTile2_swigregister(SecTile2)

class SecTile3(BaseTile):
    """Proxy of C++ SecTile3 class"""
    __swig_setmethods__ = {}
    for _s in [BaseTile]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, SecTile3, name, value)
    __swig_getmethods__ = {}
    for _s in [BaseTile]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, SecTile3, name)
    __repr__ = _swig_repr
    Nx = _model.SecTile3_Nx
    Ny = _model.SecTile3_Ny
    Nz = _model.SecTile3_Nz
    def __init__(self): 
        """__init__(SecTile3 self) -> SecTile3"""
        this = _model.new_SecTile3()
        try: self.this.append(this)
        except: self.this = this
    def cast(self, *args):
        """
        cast(SecTile3 self, SecTile2 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile2
        cast(SecTile3 self, SecTile3 buf, int & buf_sz, int sx, int sy, int sz) -> SecTile3
        """
        return _model.SecTile3_cast(self, *args)

    def start(self, *args):
        """start(SecTile3 self, Model model)"""
        return _model.SecTile3_start(self, *args)

    def step_H(self, *args):
        """step_H(SecTile3 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile3_step_H(self, *args)

    def step_m(self, *args):
        """step_m(SecTile3 self, Model model, aiv::indx< 3 > pos)"""
        return _model.SecTile3_step_m(self, *args)

    def M1(self):
        """M1(SecTile3 self) -> aiv::vctr< 3,double >"""
        return _model.SecTile3_M1(self)

    __swig_destroy__ = _model.delete_SecTile3
    __del__ = lambda self : None;
SecTile3_swigregister = _model.SecTile3_swigregister
SecTile3_swigregister(SecTile3)

from aivlib.mystream import *; 
# This file is compatible with both classic and new-style classes.


