# -*- encoding: utf-8 -*-
#-----------------------------------------------------------------------------------------------------------
#   PARSE
#-----------------------------------------------------------------------------------------------------------
class SymbalgError(Exception): pass
_bra, _ket, nan = '%s%%', '%%%s', float('nan')
#---------------------------------------------------------------------------------------------------------
def parse_bk(ev):
    'convert ?%...%? ===> (?_bk(...))'
    for bk in '() {} <> [] ||'.split() :
        if ev.count(_bra%bk[0])!=ev.count(_ket%bk[1]): raise SymbalgError('uncomplete brackets %s'%bk)
    return reduce( lambda S, bk: S.replace( _bra%bk[0], '('+bk[1:-1]+'(' ).replace( _ket%bk[-1], '))' ), '(crc_bk) {fig_bk} <ang_bk> |fabs| [rm_bk]'.split(), ev )
_N2P = lambda x: ( '%g'%x if abs(x)>=1 or x==0 else ('%g'%x)[1:] if x>0 else '-'+('%g'%x)[2:] ) if x.__class__ in (int,float,long) else str(x)
#---------------------------------------------------------------------------------------------------------
#   BASE
#-----------------------------------------------------------------------------------------------------------
class BaseOp(object):
    _priority, _nocmm, _format = -1, 0, 'pyt' # приоритет, не-коммутативность и формат вывода по умолчанию
    def __hash__(self) : return hash(repr(self))
    def __eq__(self,other) : return repr(self) == repr(other)
    def __str__(self): 
        # print id(self),self.__class__, repr(self.expr_y), repr(self.cond), repr(self.expr_n)
        return getattr( self, '__%s__'%BaseOp._format )() 
    def __pyt__(self): return self._p_pyt%self._bk( '(%s)', _N2P)
    def __txt__(self): return getattr( self, '_p_txt', self._p_pyt )%self._bk( '(%s)', _N2P )
    def __call__(self, *args, **kw_args):
        if args and kw_args : raise SymbalgError("There are no possibility to use positioned and named arguments in __call__ in the same time!")
        if kw_args: return kw_args.get('_conv', lambda x:x)( self.__expand__(**kw_args))
        return CallOp(self, args)
#-----------------------------------------------------------------------------------------------------------
#   Lambdas
#-----------------------------------------------------------------------------------------------------------
_op_expand = lambda x, **kw_args: x(**kw_args) if isinstance(x,BaseOp) else x 
_bk_prior = lambda x, y, patt, if_nocmm, f : f(x) if getattr(x, '_priority', 0) <= y._priority - y._nocmm * if_nocmm else patt%f(x) 
#-----------------------------------------------------------------------------------------------------------
#   CONTAINERS
#-----------------------------------------------------------------------------------------------------------
class UnaryOp(BaseOp):
    def __init__(self, a): self._a = a
    def __repr__(self): return '%s( %r )'%(self.__class__.__name__, self._a)
    def _bk( self, patt, f=lambda x:x ): return _bk_prior (self._a, self, patt, 0, f)
    def __expand__(self, **kw_args): return self.__class__( _op_expand(self._a, **kw_args) )
#-----------------------------------------------------------------------------------------------------------
class BinaryOp(BaseOp):
    def __init__(self, a, b): self._a, self._b = a, b
    def __repr__(self): return '%s( %r, %r )'%(self.__class__.__name__, self._a, self._b)
    def _bk( self, patt, f=lambda x:x ): return ( _bk_prior (self._a, self, patt, 0, f), 
                                                  _bk_prior (self._b, self, patt, 1, f) ) 
    def __expand__(self, **kw_args): return self.__class__(*[_op_expand(x,**kw_args) for x in ( self._a, self._b) ])
#-----------------------------------------------------------------------------------------------------------
#   OPERATIONS
#-----------------------------------------------------------------------------------------------------------
_op_list = [ (p[0] if p[1].isalpha() else p[:2], p[1+(not p[1].isalpha()):-3], (UnaryOp,BinaryOp)[p[-3]==':'], int(p[-2]), p[-1]=='n') for p in 
             '''-neg.2c +pos.2c ~inv.2c **pow:1n *mul:3c /div:3n //floordiv:3n %%mod:3n +add:4c -sub:4n <<lshift:5n >>rshift:5n &and:6c |or:7c ^xor:8c 
                 ==eq:9c !=ne:9c <lt:9n <=le:9n >gt:9n >=ge:9n'''.split() ] #[(op, name, Unary|Binary, _priority, _nocmm)]
for op, name, base, _priority, _nocmm in _op_list:
    cname = name.capitalize()+'Op'; cobj = type(cname, (base,), {'_priority':_priority, '_nocmm':_nocmm, '_p_pyt':'%s'*(base is BinaryOp)+op+'%s'}) 
    globals()[cname] = cobj
    if base is BinaryOp: setattr( BaseOp, '__%s__'%name, lambda a, b, cobj=cobj: cobj(a, b) ); setattr( BaseOp, '__r%s__'%name, lambda a, b, cobj=cobj: cobj(b, a) )
    else: setattr( BaseOp, '__%s__'%name, lambda self, cobj=cobj: cobj(self) )
class BoolAndOp(BinaryOp): _priority, _nocmm, _p_pyt = 11, 0, '%s and %s'
class BoolOrOp(BinaryOp):  _priority, _nocmm, _p_pyt = 11, 0, '%s or %s'
class Not(UnaryOp): _priority, _nocmm, _p_pyt = 10, 0, 'not %s'
BaseOp.And, BaseOp.Or = lambda a, b: BoolAndOp(a, b), lambda a, b: BoolOrOp(a, b)
#-----------------------------------------------------------------------------------------------------------
#--------------------------------Index, Call and Attr operations-------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------
class IndexOp(BinaryOp): 
    _p_pyt = '%s[%s]'
    def __init__(self, a, b): self._a, self._b = a, b if type(b) is tuple else (b,)
    def _bk(self, patt, f=lambda x:x): return ( _bk_prior (self._a, self, patt, 0, f) ,  ', '. join([ str(x) for x in self._b ]))
    def __expand__(self, **kw_args): return IndexOp(_op_expand(self._a, **kw_args), tuple([_op_expand(x,**kw_args) for x in self._b]))
BaseOp.__getitem__ = lambda a, b: IndexOp(a, b)
#-----------------------------------------------------------------------------------------------------------
class CallOp(BinaryOp):
    _p_pyt = '%s(%s)'
    def __init__(self, a, b): self._a, self._b = a, b if type(b) is tuple else (b,)
    def _bk(self, patt, f=lambda x:x): return ( _bk_prior (self._a, self, patt, 0, f) ,  ', '. join([ str(x) for x in self._b ]))
    def __expand__(self, **kw_args): return CallOp(_op_expand(self._a, **kw_args), tuple([_op_expand(x,**kw_args) for x in self._b]))
#-----------------------------------------------------------------------------------------------------------
class AttrOp(BinaryOp):
    _p_pyt = '%s.%s'
    def _bk(self, patt, f=lambda x:x): return ( _bk_prior (self._a, self, patt, 0, f) ,  self._b)
    def __expand__(self, **kw_args): 
            attr = kw_args.get(self._b, self._b) 
            return AttrOp( _op_expand(self._a, **kw_args), attr._name if isinstance(attr, Var) else attr)
BaseOp.__getattr__ = lambda a, b : AttrOp(a, Var(b))    
#-----------------------------------------------------------------------------------------------------------
#   FUNCS
#-----------------------------------------------------------------------------------------------------------
spaceOp = dict([ ( n, type( n, (UnaryOp,), { '_priority':0, '_p_pyt':n+'(%s)', '_p_txt':n+'%s', '_bk':( lambda self, patt, f=(lambda x:x): f(self._a) ) }) ) for n in 
                 'acos acosh asin asinh atan atanh cos cosh exp fabs floor log log10 sin sinh sqrt tan tanh'.split() ])
brakets = { '()':'crc_bk', '{}':'fig_bk', '<>':'ang_bk', '[]':'rm_bk' }
for bk, n in brakets.items(): 
    spaceOp[n] = type( n, (UnaryOp,), { '_priority':0, '_p_pyt':n+'(%s)', '_p_txt':'%s'.join(bk), '_bk':( lambda self, patt, f=(lambda x:x): f(self._a) ) } )
spaceOp['fabs']._p_txt, spaceOp['Not'] = '|%s|', Not
#-----------------------------------------------------------------------------------------------------------
#  VARIABLE
#-----------------------------------------------------------------------------------------------------------
class Var(BaseOp):
    def __init__(self, name, type="double"): self._name, self._type = name, type
    def __pyt__(self): return self._name
    def __txt__(self): return self._name
    def __repr__(self): return 'Var(%r)'%self._name
#    def __call__(self, *args, **kw_args): return DefVarStm(self._name, args[0], kw_args.get("value")) if args else Var(kw_args.get(self._name,self._name), self._type)
    def __expand__(self, **kw_args): v = kw_args.get(self._name, self._name); return v if isinstance(v, BaseOp) else Var(v, self._type)
    def __hash__(self) : return hash(self._name) #!!!!!
#-----------------------------------------------------------------------------------------------------------
#   EXPAND SYNTAX
#-----------------------------------------------------------------------------------------------------------
class IfElseOp(BaseOp):
    _priority, _p_pyt = 12, '%s if %s else %s'
    def __init__(self, expr_y, cond, expr_n): self._expr_y, self._cond, self._expr_n = expr_y, cond, expr_n
    def __repr__(self): return 'IfElseOp( %r, %r, %r )'%(self._expr_y, self._cond, self._expr_n)

    def _bk(self, patt, f=lambda x:x):return ( _bk_prior (self._expr_y, self, patt, 0, f), _bk_prior (self._cond, self, patt, 0, f), _bk_prior (self._expr_n, self, patt, 0, f))     
    def __expand__(self, **kw_args): return IfElseOp(*[ _op_expand(x, **kw_args) for x in (self._expr_y, self._cond, self._expr_n) ])

def _ifch(*args):    
    chain = []
    def wrap(*args):
        if len(args)==2: chain.append(args); return wrap
        elif len(args)==3: return reduce( lambda R, a: IfElseOp(a[0], a[1], R), reversed(chain), IfElseOp(*args) )
        else: raise Exception('incorrect args count in if_chain')
    return wrap(*args)
spaceOp['ifch'] = _ifch
#-----------------------------------------------------------------------------------------------------------
class JoinOp(BaseOp):
    def __init__(self, *args): self._args = args
    def __str__(self): return ''.join(map(str, self._args))
    def __repr__(self): return 'JoinOp(%s)'%', '.join(map(repr, self._args))
    def __expand__(self, **kw_args): return JoinOp(*[_op_expand(x, **kw_args) for x in self._args ])    
#-----------------------------------------------------------------------------------------------------------
class EmptyVar(BaseOp):
    def __init__(self, _last_stack_fr=None): self._last_stack_fr = _last_stack_fr
    def __str__(self): raise Exception('can not convert to string EmptyVar object!')
    def __repr__(self): return '_'
    def __getitem__(self, args):
        if self._last_stack_fr is None: return JoinOp(*args) if type(args) is tuple else JoinOp(args)
        if args.__class__ is ListStm:
            for i in args._list: self._last_stack_fr.append(i)
        elif args.__class__ is tuple: self._last_stack_fr.append(JoinOp(*args))
        else: self._last_stack_fr.append(args)
    def __call__(self, arg, bk='()'): return spaceOp['%s_bk'%brakets[str(bk)]](arg)
#-----------------------------------------------------------------------------------------------------------    
OrOp.__or__ = lambda self, other : self._a.Or(other) if isinstance(self._b, EmptyVar) else OrOp(self,other)
AndOp.__and__ = lambda self, other : self._a.And(other) if isinstance(self._b, EmptyVar) else AndOp(self,other)
spaceOp['_'] = EmptyVar()
#-----------------------------------------------------------------------------------------------------------
#   C++ OUT RULES
#---------------------------------------- -------------------------------------------------------------------
BaseOp.__cpp__ = lambda self: getattr(self, '_p_cpp' if hasattr(self.__class__, '_p_cpp') else '_p_pyt')%self._bk('(%s)')
PowOp._p_cpp, BoolAndOp._p_cpp, BoolOrOp._p_cpp, Not._p_cpp = 'pow(%s, %s)', '(%s)&&(%s)', '(%s)||(%s)', '!(%s)'
Var.__cpp__ = lambda self: self._name
IfElseOp.__cpp__ =  lambda self: '(%s)?(%s):(%s)'%(self._cond, self._expr_y, self._expr_n)
#-----------------------------------------------------------------------------------------------------------
class LocalNamespace:
    def __init__(self, Var=Var): self.Var = Var
    def __getitem__(self, key): return spaceOp[key] if key in spaceOp else self.Var(key)
#-----------------------------------------------------------------------------------------------------------
convert = lambda expr, Var=Var: eval( parse_bk(expr), {}, LocalNamespace() )
#-----------------------------------------------------------------------------------------------------------
del op, name, base, _priority, _nocmm, bk, n, brakets
#-----------------------------------------------------------------------------------------------------------
#-----setattr 
# _a, _b, _args, _name, 
# Какая разница между Call и Index в смысле expand и bk???