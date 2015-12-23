%module model
%exception { try{ $action }catch( const char *e ){ PyErr_SetString( PyExc_RuntimeError, e ); return NULL; }catch(...){ return NULL; } }
%pythoncode %{def _setstate( self, state ):
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
%}
%typemap(out) bool&   %{ $result = PyBool_FromLong    ( *$1 ); %}
%typemap(out) char&   %{ $result = PyInt_FromLong     ( *$1 ); %}
%typemap(out) short&  %{ $result = PyInt_FromLong     ( *$1 ); %}
%typemap(out) int&    %{ $result = PyInt_FromLong     ( *$1 ); %}
%typemap(out) long&   %{ $result = PyInt_FromLong     ( *$1 ); %}
%typemap(out) float&  %{ $result = PyFloat_FromDouble ( *$1 ); %}
%typemap(out) double& %{ $result = PyFloat_FromDouble ( *$1 ); %}
%feature("autodoc","1");
%inline %{namespace aiv{}; %}

%ignore data_header; %ignore base_data;
%{
#include <aivlib/indexD.hpp>
#include <aivlib/vectorD.hpp>
#include <aivlib/memT.hpp>
#include <aivlib/arrayTD.hpp>
#include <aivlib/meshTD.hpp>
#include <aivlib/lrCubeTD.hpp>
#include <aivlib/base_sphere.hpp>
#include <aivlib/sphereT.hpp>
%}
%include "aivlib/indexD.hpp"
%include "aivlib/vectorD.hpp"
%include "aivlib/memT.hpp"
%include "aivlib/arrayTD.hpp"
%include "aivlib/meshTD.hpp"
%include "aivlib/lrCubeTD.hpp"
%include "aivlib/base_sphere.hpp"
%include "aivlib/sphereT.hpp"
%{
#include "model.hpp"
#include "/usr/include/aivlib/meshTD.hpp"
%}
%include "model.hpp"
%include "/usr/include/aivlib/meshTD.hpp"
%{
#include <aivlib/indexD.hpp>
%}
%include "aivlib/indexD.hpp"
%template(indx1) aiv::indx<1>;
%pythoncode %{ 
def Indx( *L ) : v = getattr( import_aivlib( 'indx%i'%len(L) ), 'indx%i'%len(L) )(); v[:] = tuple(L); return v
indx1.__rcmp__=lambda a,b : -b.__cmp__(a) 
def _indx1__xor__( a,b ) :  
  try : return Indx(*map( int.__mul__, tuple(a),tuple(b) ) )  
  except : return  Indx(*(tuple(a)[:b]+tuple(a)[b+1:]))
indx1.__xor__ = _indx1__xor__ 
indx1.__or__ =lambda a,b : Indx(*(tuple(a)+tuple(((b,),b)[b.__class__.__name__.startswith('indx')])))  
indx1.__ror__=lambda a,b : Indx(*(tuple(((b,),b)[b.__class__.__name__.startswith('indx')])+tuple(a)))  
indx1.__setstate__ = _setstate 
%}
%{
#include <aivlib/indexD.hpp>
#include <aivlib/vectorD.hpp>
%}
%include "aivlib/indexD.hpp"
%include "aivlib/vectorD.hpp"
%template(vctr1) aiv::vctr<1,double>;
%pythoncode %{ 
def Vctr( *L ) : v = getattr( import_aivlib( 'vctr%i'%len(L) ), 'vctr%i'%len(L) )(); v[:] = tuple(L); return v
def _vctr1__xor__( a,b ) :  
  try : return Vctr(*map( float.__mul__, tuple(a),tuple(b) ) )  
  except : return  Vctr(*(tuple(a)[:b]+tuple(a)[b+1:]))
vctr1.__xor__ = _vctr1__xor__ 
vctr1.__or__ =lambda a,b : Vctr(*(tuple(a)+tuple(((b,),b)[b.__class__.__name__.startswith('vctr')])))  
vctr1.__ror__=lambda a,b : Vctr(*(tuple(((b,),b)[b.__class__.__name__.startswith('vctr')])+tuple(a)))  
vctr1.__setstate__ = _setstate 
%}
%{
#include <aivlib/memT.hpp>
#include <aivlib/arrayTD.hpp>
#include <aivlib/meshTD.hpp>
#include <aivlib/multiarrayT.hpp>
%}
%include "aivlib/memT.hpp"
%include "aivlib/arrayTD.hpp"
%include "aivlib/meshTD.hpp"
%include "aivlib/multiarrayT.hpp"
%template(arrP1) aiv::array<part,1>; %template(meshP1) aiv::mesh<part,1>; %template(mult_arrP1) aiv::multiarray< aiv::array<part,1> >;
%pythoncode %{arrP1.__setstate__, meshP1.__setstate__ = _setstate, _setstate %}
%pythoncode %{from aivlib.vctr1 import * %}
%pythoncode %{from aivlib.mystream import * %}
%pythoncode%{ from aivlib.mystream import *; %}

