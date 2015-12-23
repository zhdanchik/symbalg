# -*- encoding: utf-8 -*-
import sys, inspect, expressions
from expressions import SymbalgError, spaceOp, Var, EmptyVar, BaseOp, _op_list, UnaryOp, BinaryOp, OrOp, AndOp, AddOp, SubOp, IndexOp, AttrOp
#-----------------------------------------------------------------------------------------------------------
#   Lambdas
#-----------------------------------------------------------------------------------------------------------
_st_expand = lambda x, **kw_args: x(**kw_args) if isinstance(x,BaseStm) or isinstance(x,BaseOp) else x 
#-----------------------------------------------------------------------------------------------------------
class BaseStm: 
    _level = -1
    _last_stack_frame = None
    def __add__(self, other): return ListStm( *sum([ x._list if x.__class__ is ListStm else [x] for x in (self, other) ], []) ) #check other type?
    def __mul__(self, n): return ListStm( *(( self._list if isinstance(self, ListStm) else [self] )*n) ) #check other type?
    def __call__(self, *args, **kw_args):
        if args : raise SymbalgError("There are no possibility to use positioned arguments in BaseStm.__call__ ")
        return kw_args.get('_conv', lambda x:x)( self.__expand__(**kw_args))
    def __hash__(self) : return hash(repr(self))
    def __eq__(self, other): return repr(self)==repr(other)
    # def __cmp__(self, other) : return cmp(repr(self),repr(other))
#-----------------------------------------------------------------------------------------------------------
#   INC&DEC
#-----------------------------------------------------------------------------------------------------------
class PIncOp(UnaryOp, BaseStm): _p_cpp, _p_pyt = '++%s', None
class PDecOp(UnaryOp, BaseStm): _p_cpp, _p_pyt = '--%s', None
class IIncOp(UnaryOp, BaseStm): _p_cpp, _p_pyt = '%s++', None
class IDecOp(UnaryOp, BaseStm): _p_cpp, _p_pyt = '%s--', None
EmptyVar.__add__ = lambda self, other: PIncOp(other)
EmptyVar.__sub__ = lambda self, other: PDecOp(other)
EmptyVar.__radd__ = lambda self, other: IIncOp(other)
EmptyVar.__rsub__ = lambda self, other: IDecOp(other)
BaseOp.__add__ = lambda self, other: IIncOp(self) if isinstance(other, EmptyVar) else AddOp(self, other)
BaseOp.__sub__ = lambda self, other: IDecOp(self) if isinstance(other, EmptyVar) else SubOp(self, other)
#-----------------------------------------------------------------------------------------------------------
#   STM CLASSES
#-----------------------------------------------------------------------------------------------------------
class ListStm(BaseStm):
    def __init__(self, *args): self._list = list(args) #check args types?
    def __expand__(self,  **kw_args): return ListStm(*[ _st_expand(x,**kw_args) for x in self._list ])
    def __str__(self): 
        try: BaseStm._level += 1; return ''.join([ '    '*BaseStm._level+'%s;\n'%s for s in self._list if s])
        finally: BaseStm._level -= 1
    def __repr__(self): return "ListStm( %s )"%(", ".join(map(repr,self._list)))
    def append(self, x): self._list.append(x)
    def extend(self, x): return ListStm(self._list.extend(x))
    def __nonzero__(self): return bool(self._list)
expressions.ListStm = ListStm
#-----------------------------------------------------------------------------------------------------------
class SetStm(BaseStm):
    def __init__(self, lvalue, expr, op='='): self.lvalue, self.expr, self.op = lvalue, expr, op #check args types?
    def __repr__(self): return "SetStm( lvalue=%r, expr=%r, op=%r )"%(self.lvalue,self.expr,self.op)
    def __expand__(self, **kw_args): return SetStm(*[_st_expand(x,**kw_args) for x in [self.lvalue,self.expr,self.op]])
    def __str__(self): return '%(lvalue)s %(op)s %(expr)s'%self.__dict__
#-----------------------------------------------------------------------------------------------------------
class DefVarStm(BaseStm):
    def __init__(self, name, type, value): self.name, self.type, self.value = name, type, value
    def __expand__(self, **kw_args): return DefVarStm(*[_st_expand(x,**kw_args) for x in [self.name,self.type,self.value]])
    def __str__(self): return '%(type)s %(name)s'%self.__dict__ + " = %s"%self.value*(self.value<>None)

expressions.DefVarStm = DefVarStm
#-----------------------------------------------------------------------------------------------------------
class IfStm(BaseStm):
    def __init__(self, cond, _then, _else): self.cond, self.mode, self._then, self._else = cond, True, _then, _else
    def __expand__(self, **kw_args): return IfStm(*[_st_expand(x,**kw_args) for x in [self.cond,self._then,self._else]])
    def __getitem__(self, cond): 
        if self.cond: raise SymbalgError('If[%s] denied: the cond="%s" has already set!'%(cond, self.cond))
        self.cond = cond
    def Else(self):
        if not self.mode: raise SymbalgError('If[%s].Else() denied!'%self.cond)
        self.mode = False
    def append(self, x): (self._then if self.mode else self._else).append(x)
    def __str__(self): return  'if(%s){\n%s%s}'%(self.cond, self._then, '    '*self._level) + ( 'else{\n%s%s}\n'%(self._else, '    '*self._level) if self._else else '\n' )
#-----------------------------------------------------------------------------------------------------------
class ForStm(BaseStm):
    def __init__(self, init, cond, step, code): self.init, self.cond, self.step, self.code = init, cond, step, code
    def __expand__(self, **kw_args): return ForStm(*[_st_expand(x,**kw_args) for x in [self.init,self.cond,self.step,self.code]])
    def __str__(self): return 'for(%s; %s; %s){\n%s%s}'%(self.init, self.cond, self.step, self.code, '    '*self._level)
    def __getitem__(self, args): 
        if len(args)==2 and type(args[0]) is slice: args = ['auto', args[0].start, args[0].stop, args[0].start<args[1], PIncOp(args[0].start) ]
        elif len(args)==3 and type(args[0]) is slice: args = ['auto', args[0].start, args[0].stop, args[0].start<args[1], SetStm(args[0].start, args[2], '+=')]
        elif len(args)==3 and isinstance(args[0],DefVarStm): args = [args[0].type, args[0].name, args[0].value, args[1], args[2]]
        elif len(args)==4: args = ('auto',)+args
        elif len(args)!=5: raise SymbalgError('Unexpected count of arguments')
        self.init, self.cond, self.step = DefVarStm(args[1], args[0], args[2]), args[3], args[4]
    def append(self, x):  self.code.append(x)
#-----------------------------------------------------------------------------------------------------------
#   DEKORATOR
#-----------------------------------------------------------------------------------------------------------
def _mk_frame(stack, fr): stack[-1].append(fr); stack.append(fr); return fr
class NamespaceStm:
    def __init__(self, localNS, globalNS): 
        self.stack, self.globalNS, self.space = [ListStm()], globalNS, dict(localNS)
        self.vars = dict([ i for i in localNS.items() if isinstance(i[1], Var) ])
    def __getitem__(self, name):
        BaseStm._last_stack_frame = self.stack[-1]
        if name=='_': return EmptyVar(_last_stack_fr=self.stack[-1])
        if name=='End': return self.stack.pop(-1) # открывает возможности для читерства с последним кадром трассы выполнения
        if name=='If': return _mk_frame(self.stack, IfStm('', ListStm(), ListStm()))
        if name=='Else': self.stack[-1].Else(); return self.stack[-1]
        if name=='For': return _mk_frame(self.stack, ForStm('', '', '', ListStm()))
        if name in self.space: return self.space[name]
        if name in self.globalNS or name in __builtins__: raise KeyError(name)
        if name[0]!='_': v = Var(name); self.vars[name] = self.space[name] = v; return v
        raise KeyError(name)
    def __setitem__(self, name, value):
        BaseStm._last_stack_frame = self.stack[-1]        
        if name[0]=='_': self.space[name] = value
        else: v = self.vars.setdefault(name, Var(name)); self.space[name] = v; self.stack[-1].append( value if isinstance(value, BaseStm) else SetStm( v, value ))
    def __delitem__(self, name): 
        if name in self.vars: raise Exception("Can't delete var(%r) from local namespace"%name)
        del self.space[name]
#-----------------------------------------------------------------------------------------------------------
def _exec(expr, G, L): exec(expr, G, L)
def statement(func, *args1): #decorator
    def wrap(*args, **kw_args):
        globalNS = dict(func.func_globals); globalNS.update(spaceOp)
        localNS = NamespaceStm(kw_args, globalNS) #set args, kw_args
        _exec( '\n'.join(['if 1:']+inspect.getsource(func).split('\n')[2:]), globalNS, localNS ) 
        return localNS.stack[0]
    return wrap
#-----------------------------------------------------------------------------------------------------------
for op, name, base, _priority, _nocmm in _op_list: 
    if base is BinaryOp and op not in('**', '//') and _priority<9: setattr(BaseOp, '__i%s__'%name, lambda self, other, op='%s='%op: SetStm(self, other, op))

BaseOp.__setitem__ = lambda a, b, c: BaseStm._last_stack_frame.append(c if isinstance(c, SetStm) else SetStm(IndexOp(a, b), c, '='))
BaseOp.__setattr__ = lambda a, b, c: BaseStm._last_stack_frame.append(c if isinstance(c, SetStm) else SetStm(AttrOp(a, b), c, '=') ) if b[0]!='_' else object.__setattr__(a,b,c)
BaseOp.__ifloordiv__ = lambda self, other: SetStm(self, other, '/=')
del op, name, base, _priority, _nocmm #, spaceOp, Var, BaseOp, _op_list, BinaryOp, OrOp, AndOp
#-----------------------------------------------------------------------------------------------------------
