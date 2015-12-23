# -*- encoding: utf-8 -*-
from expressions import *
from statements import *
def ExportDot(obj, name, no_stms=False, only_indxs=False):
    'рисует граф в доте'
    import gv
    _G, nodes = gv.digraph("G"), {}
    gv.setv( _G, 'rankdir', 'TB' )
    def export_to_dot():
        def export(x):
            def mknode( n ) :
                k = str(n); node = nodes[k] if k in nodes else nodes.setdefault( k, gv.node( _G, k ) )
                return node
            me = mknode(x)
            if isinstance(x,BinaryOp):
                gv.edge(me, mknode(x._a))
                gv.edge(me, mknode(x._b))
            if isinstance(x, ListStm):
                for l in x._list: gv.edge(me, mknode(l))
            if isinstance(x, SetStm):
                gv.setv( me, 'shape', 'box' )
                gv.setv( gv.edge(me, mknode(x.lvalue)), 'label','lvalue')
                gv.setv( gv.edge(me, mknode(x.expr)), 'label','expr')
            return x
        return export
    obj()(_conv = export_to_dot())
    gv.layout( _G, 'dot')
    gv.render( _G, 'pdf', name)

#собирает все зависимости (с индексами)
def collect_deps(obj):
    deps = []
    def _collect_deps(x):
        if isinstance(x, IndexOp): deps.append(x)
        return x
    if isinstance(obj, BaseOp) or isinstance(obj, BaseStm) : obj(_conv=_collect_deps)
    return tuple(deps)


def collect_not_vars(obj):
    'собирает левые части у a(b) и правые у a.b'
    _list = set()
    def go_collect(x):
        if isinstance(x,CallOp) and isinstance(x._a,Var): _list.add(x._a)
        if isinstance(x,AttrOp) and isinstance(x._b,Var): _list.add(x._b)

        return x
    if isinstance(obj, BaseOp) or isinstance(obj, BaseStm) : obj(_conv = go_collect)
    return _list

def collect_lvalues(obj):
    'собирает левые части у SetStm'
    _list = set()
    def go_collect(x):
        if isinstance(x,SetStm):
            if isinstance(x.lvalue,Var):_list.add(x.lvalue)
            if isinstance(x.lvalue, IndexOp): _list.add(x.lvalue._a)
        return x
    if isinstance(obj, BaseOp) or isinstance(obj, BaseStm) : obj(_conv = go_collect)
    return _list

def collect_vars(obj):
    _list = set()
    def go_collect(x):
        if isinstance(x, IndexOp): _list.add(x._a)
        if isinstance(x,Var): _list.add(x)
        return x
    if isinstance(obj, BaseOp) or isinstance(obj, BaseStm) : obj(_conv = go_collect)
    return _list

def offset(step):
    'смещение на step'
    def _offset(x):
        if isinstance(x,IndexOp):
            return x._a[tuple([x1+x2 for x1,x2 in zip(x._b,step)])]
        return x
    return _offset

def filter(x, names):
    NewList = ListStm()
    for c in x._list:
        if isinstance(c.lvalue,IndexOp):
            if c.lvalue._a._name in names:
                NewList.append(c)
    return NewList
