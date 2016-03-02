# -*- encoding: utf-8 -*-

from statements import *
from ast_funcs import collect_deps,offset

def dict_str(_dict):
    return "\n".join([ str(x)+" : "+str(y) for x,y in _dict.items()])

class section():
    def __init__(self, obj, in_sec, sec_id): self.obj, self.in_sec, self.index = obj, in_sec, sec_id
    # def in_sec(self,indx): return self.in_sec(indx)

class scheme():
    def diag(self):
        print 80*"-"
        print "step_d = ", self.step_d
        print 80*"-"
        print "acts = "
        for i, act in enumerate(self.acts): print i,":\n", "\n".join([str(a[0]) + "\n\ttgts : " + str(a[1]) + "\n\tdeps : " + str(a[2]) for a in act])
        print 80*"-"
        print "tiers = "
        for i, sec in enumerate(self.tiers): print i,":\n", dict_str(sec)
        print 80*"-"
        print "tgtsD = "
        for i, sec in enumerate(self.tgtsD): print i,":\n", dict_str(sec)
        print 80*"-"
        print "depsD = "
        for i, sec in enumerate(self.depsD): print i,":\n", dict_str(sec)
        print 80*"-"

    def abs_var(self, did) : return (did[0],) + tuple( a%b for a,b in zip(did[1:], self.step_d))
    def tier(self, did): return self.tiers[self.cur_sec][self.abs_var(did)]
    def abs_only_tier(self, did): return did[:-1] + (did[-1] % self.tier(did[:-1]),)
    def abs_with_tier(self, did): return self.abs_var(did[:-1]) + (did[-1] % self.tier(did[:-1]),)
    def abs_n_delta(self, did): return self.abs_with_tier(did), tuple([a-b for a,b in zip(self.abs_with_tier(did)[1:],did[1:])])
    def var_offset(self, did, delta): return (did[0],) + tuple([a+b for a,b in zip(did[1:],delta)])

    def __init__(self, sections, step_d):
        self.step_d, self.acts, self.tiers, self.tgtsD, self.depsD = step_d, [], [], [], []
        self.sections, self.cur_sec = sections, -1

        for self.cur_sec in range(len(sections)):
            self.acts.append([])
            self.tiers.append({})
            self.tgtsD.append({})
            self.depsD.append({})
            def mk_did(x, is_lv = False) : 
                did = (x._a._name,) + x._b
                self.tiers[self.cur_sec][self.abs_var(did)] = self.tiers[self.cur_sec].get(self.abs_var(did), 0) + bool(is_lv)
                return did + (self.tier(did),)

            tgtsDtmp, depsDtmp, actstmp = {}, {}, []

            def get_scheme_info(x):
                if isinstance(x, SetStm):
                    if isinstance(x.lvalue, IndexOp):
                        # deps = map(mk_did, tuple(list(collect_deps(x.expr))  + [x.lvalue] if (x.op[-1] and len(x.op) > 1) =="=" else [] ))
                        # deps = map(mk_did, tuple(list(collect_deps(x.expr))  + [x.lvalue] if (x.op[-1] and len(x.op) > 1) =="=" else [] ))
                        deps = map(mk_did, collect_deps(x.expr)) + ([mk_did(x.lvalue)] if (x.op[-1]=="=" and len(x.op) > 1) else [])
                        tgt = mk_did(x.lvalue,is_lv=True)
                        actstmp.append((x, [tgt], deps))
                        tgtsDtmp[tgt] = [ (dep , len(actstmp) -1 ) for dep in deps]
                        for dep in deps : depsDtmp.setdefault(dep,[]).append((tgt, len(actstmp)-1)) 
                return x


            self.sections[self.cur_sec].obj(_conv=get_scheme_info)
            
            for act in actstmp:
                self.acts[self.cur_sec].append((act[0], [self.abs_with_tier(c) for c in act[1]], [self.abs_only_tier(c) for c in act[2]]))

            def updateD(Dtmp):
                D={}
                for k,v in Dtmp.items():
                    td = self.abs_only_tier(k)
                    tds = [(self.abs_only_tier(d[0]),d[1]) for d in v]
                    abs_td, delta_td = self.abs_n_delta(td)
                    D.setdefault(abs_td, set()).update([ (self.var_offset(d,delta_td),n,delta_td) for d,n in tds])
                return D

            self.tgtsD[self.cur_sec] = dict(updateD(tgtsDtmp))
            self.depsD[self.cur_sec] = dict(updateD(depsDtmp))        

    def set_sct(self, x):
        self.cur_sec = self.get_sec_num(x)
        if self.cur_sec == -1: raise SymbalgError ("Error: Variable %s is not located in any section."%(x[:-1], ))

    def get_sec_num(self, x):
        sec_num = -1
        for sct in self.sections:
            if sct.in_sec(x[1:-1]):
                if sec_num != -1 :
                    raise SymbalgError ("Error: Variable %s is located in section #%s and section #%s."%(x[:-1], sec_num, sct.index))
                sec_num = sct.index
        
        return sec_num
  

    def get_cone(self, base, dir, t_count):
        def tup_sum(t1,t2):return tuple([a+b for a,b in zip(t1,t2)])
        def inv_tup(t): return tuple([-a for a in t])

        res_set, tmp_set = set(), set()
        for v in base: 

            self.set_sct(v) #Устанавливаем текущую секцию, соответствующуу очередному вару в цикле
            abs_v, delta_v = self.abs_n_delta(v) #
            new_time = t_count-1 if dir==-1 else 0
            tmp_set.update([(new_time,      #t
                             i[1],          #N
                             self.cur_sec,  #sec_num
                             tup_sum(i[2],inv_tup(delta_v))) for i in self.tgtsD[self.cur_sec][abs_v]]) #offset
            print base,self.tgtsD[self.cur_sec]
        # act :  ( t, N, sec_num, offset )
        #        ( 0, 1,    2   ,   3    )
        #
        # D : {v1:set([ (u1, act_num, offset), (), ... ]), v2:...}
        #
        
        # ii = 0
        while res_set!=tmp_set :
            # cone2pdf(tmp_set,self.acts,"test_%s_%s"%(ii,dir),"LR")
            # ii+=1
            res_set = set(tmp_set)
            for act in res_set:
                tgts_deps = [ self.var_offset(td,act[3]) for td in self.acts[act[2]][act[1]][1 if dir == 1 else 2]]
                for td in tgts_deps:

                    self.set_sct(td) #!!!!!
                    abs_v, delta_v = self.abs_n_delta(td)

                    for self.cur_sec in (range(len(self.sections)) if dir==1 else [self.get_sec_num(td)]):
                    # for self.cur_sec in range(len(self.sections)):
                        D = self.tgtsD[self.cur_sec] if dir==-1 else self.depsD[self.cur_sec]

                        for i in D.get(abs_v,[]):
                            # print td, i, tup_sum(i[2],inv_tup(delta_v)), self.var_offset(i[0],inv_tup(delta_v))
                            flag = True
                            if dir == 1: flag = False
                            if self.get_sec_num(self.var_offset(i[0],inv_tup(delta_v)))==self.cur_sec : flag = True
                            if flag:
                                if_gap = bool(dir*(i[1]-act[1])<=0)
                                new_time = (act[0] + dir*if_gap)
                                if new_time in range(t_count): 
                                    tmp_set.add(( new_time, i[1], self.cur_sec, tup_sum(i[2],inv_tup(delta_v))))

        return res_set

    def top_bottom(self, bottom_base, top_base, t_count):

        top_cone = self.get_cone(top_base, -1, t_count)  
        bottom_cone = self.get_cone(bottom_base, 1, t_count)
        # return self.get_cone(bottom_base, 1, t_count) & self.get_cone(top_base, -1, t_count)
        # cone2pdf(bottom_cone,self.acts,"LRnLA/sections/FDTD_2D_CF_bottom.pdf", "BT")
        # cone2pdf(top_cone,self.acts,"LRnLA/sections/FDTD_2D_CF_top.pdf", "BT")
        print "-----------top_cone:\n",cone2obj(top_cone, self.acts, time = "time", h = "h")
        print "--------bottom_cone:\n",cone2obj(bottom_cone, self.acts, time = "time", h = "h")
        # print "--------top_bottom_cone:\n",cone2obj(top_cone&bottom_cone, self.acts, time = "time", h = "h")
        return top_cone&bottom_cone
        #return bottom_cone

    def top_cone(self,  top_base, t_count): return self.get_cone(top_base, -1, t_count)  
    def bottom_cone(self, bottom_base, t_count): return self.get_cone(bottom_base, 1, t_count)

def print_cone(cone,acts): 
    for c in sorted(cone):
        print acts[c[2]][c[1]][0](_conv=offset(c[3]))

def cone2obj(cone,acts, time = "time", h="h"):
    obj = ListStm()
    if cone :
        tmp_time = sorted(cone)[0][0]
    else: return obj

    for c in sorted(cone):
        if c[0] > tmp_time:
            obj.append("%s+=%s"%(time,h))
        obj.append(acts[c[2]][c[1]][0](_conv=offset(c[3])))
        tmp_time = c[0]

    return obj

def cone2list(cone,acts):
    obj = ListStm()

    for c in sorted(cone):
        obj.append(acts[c[2]][c[1]][0](_conv=offset(c[3])))

    return obj

def cone2pdf(cone,acts,name, rankdir):
    import gv,math
    from symbalg.ast_funcs import collect_deps
    _G, nodes = gv.digraph("G"), {}
    gv.setv( _G, 'rankdir', rankdir )
    gv.setv( _G, 'margin', '0' )
    gv.setv( _G, 'ranksep', "0.7 equally"  )
    colorarr=["pink","lightblue"]#,"darkseagreen1"]
    N = gv.protonode(_G)
    gv.setv(N,"penwidth","1.0")
    gv.setv(N,"fontsize","14")
    gv.setv(N,"fontname","verdana")
    gv.setv(N,"style","filled")
    gv.setv(N,"gradientangle","90" if rankdir == "BT" else "0")
    E = gv.protoedge(_G)
    gv.setv(E,"penwidth","1.0")

    subgraphs = {}
    D= {}
    def mknode( n, t=None ) :
        # t=int(t*2)
        k = str(n) + ("" if t == None else str(t))
        # print k 
        if k in nodes:
            node = nodes[k]
        else:
            if not t in subgraphs: 
                subgraphs[t] = gv.graph(_G, "sub"+str(t))
                gv.setv(subgraphs[t],"rank", str(t))#"same")
            node = nodes.setdefault( k, gv.node( subgraphs[t], k ) )
            gv.setv(node,"label",str(n))
            if t!=None: gv.setv(node,"fillcolor", str(colorarr[int(math.floor(t-0.5)) % len(colorarr)]) +":" + str(colorarr[int(math.floor(t)) % len(colorarr)]) )
        return node


    for c in sorted(cone):
        act = acts[c[2]][c[1]][0](_conv=offset(c[3]))
        
        max_t = max([ D.get(d,0) for d in collect_deps(act.expr)])

        t = max_t + 0.5

        act_node = mknode(act,t)
        gv.setv(act_node,"shape","box")
        gv.setv(act_node,"fontsize","18")
        gv.setv(act_node,"penwidth","3.0")
        for d in collect_deps(act.expr):
            t = D.setdefault(d,max_t)
            dep_node = mknode(d,t)
            gv.edge(dep_node,act_node)

        D[act.lvalue] = max(D.get(act.lvalue,0) + 1,max_t+1)
        # t = max(D[act.lvalue],max_t+1)
        t = D[act.lvalue]
        lvalue_node = mknode(act.lvalue,t)
        gv.edge(act_node,lvalue_node)

    gv.layout( _G, 'dot')
    gv.render( _G, 'pdf', name)


def get_square(obj, ifdeps=False):

    dim = len(obj._list[0].lvalue._b)
    
    sq = (obj._list[0].lvalue._b,obj._list[0].lvalue._b) #(Xlb, Xrt)

    for c in obj._list:
        indxs = [c.lvalue._b] + ifdeps * [x._b for x in collect_deps(c)]
        tmpmin = []
        tmpmax = []
        for d in range(dim) : 
            # print (indxs+[sq[0]])
            tmpmin.append(min([x[d] for x in (indxs+[sq[0]])]))
            tmpmax.append(max([x[d] for x in (indxs+[sq[1]])]))
        sq = (tuple(tmpmin), tuple(tmpmax))
    return sq

def get_rmb(obj, ifdeps=False):

    dim = len(obj._list[0].lvalue._b)
    if dim != 2 : raise SymbalgError("there is allowed only 2 dimensions")

    sq = (obj._list[0].lvalue._b,obj._list[0].lvalue._b) #(Xlb, Xrt)
    sqmin = (sq[0][0]-sq[0][1],sq[0][0]+sq[0][1])
    sqmax = (sq[0][0]-sq[0][1],sq[0][0]+sq[0][1])
    for c in obj._list:
        indxs = [c.lvalue._b] + ifdeps * [x._b for x in collect_deps(c)]
        indxs = map(lambda x: (x[0]-x[1],x[0]+x[1]),indxs)
        # print indxs
        # print sqmin,"-", sqmax,"1"

        sqmin = (min([x[0] for x in indxs]+[sqmin[0]]), min([x[1] for x in indxs]+[sqmin[1]]))
        sqmax = (max([x[0] for x in indxs]+[sqmax[0]]), max([x[1] for x in indxs]+[sqmax[1]]))
        # print sqmin,"-", sqmax,"2"
    return (((sqmin[0]+sqmin[1])*.5,(-sqmin[0]+sqmin[1])*.5),((sqmax[0]+sqmax[1])*.5,(-sqmax[0]+sqmax[1])*.5))

def S_sq(sq): return reduce(lambda x,y : x*y, [abs(x-y) for x,y in zip(sq[0],sq[1])],1)
def S_rmb(sq): 
    if len(sq[0])!=2 : raise SymbalgError("there is allowed only 2 dimensions")
    return 0.5*reduce(lambda x,y : x*y, [abs(x-y) for x,y in ((sq[0][0]-sq[0][1],sq[1][0]-sq[1][1] ),(sq[0][0]+sq[0][1],sq[1][0]+sq[1][1]))],1)

    # for 
#1.   ищем макс фигуру.
#1.5. ищем плотность
#2. ищем мин фигуру - как??? мин фигура по 
#3. куда заваливать? по времени.  