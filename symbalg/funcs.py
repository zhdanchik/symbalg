# -*- encoding: utf-8 -*-
import inspect
from expressions import BaseOp, spaceOp, Var
from statements import NamespaceStm, _exec, BaseStm 

def function(func): #decorator
    def funcwrap(*args, **kw_args):
        globalNS = dict(func.func_globals); globalNS.update(spaceOp)
        localNS = NamespaceStm(kw_args, globalNS) #set args, kw_args
        _exec('\n'.join(['if 1:']+inspect.getsource(func).split('\n')[2:]), globalNS, localNS )
        fargs = inspect.getargspec(func)
        return MethodContainer(func.__name__, localNS.stack[0], [Var(v,t) for v,t in zip(fargs.args,fargs.defaults)]if fargs.defaults else[])
    return funcwrap

class Container():
    def __str__(self): return getattr( self, '__%s__'%BaseOp._format )()


class MethodContainer(Container):
    def __init__(self, name, body, args, preffixes = [], pubpriv = "public", ttype = "void"):   
        self.name = name
        self.body = body
        self.args = args
        self.preffixes = preffixes
        self.pubpriv = pubpriv
        self.ttype = ttype

    def __cpp__(self): return "%s %s %s(%s){\n%s}"%(" ".join(self.preffixes),self.ttype,self.name, ",".join(["%s %s"%(c._type,c._name) for c in self.args]), self.body)
    def __pyt__(self): return "This is python output for VoidContaier"

    def to_hpp(self):
        old_format,BaseOp._format = BaseOp._format,'cpp'
        out_str = "%s %s %s(%s);"%(" ".join(self.preffixes),self.ttype,self.name, ",".join(["%s %s"%(c._type,c._name) for c in self.args]))
        BaseOp._format = old_format
        return out_str
    def to_cpp(self,cl_name):
        old_format,BaseOp._format = BaseOp._format,'cpp';BaseStm._level+=1
        out_str = "%s %s %s::%s(%s){\n%s}"%(" ".join(self.preffixes),self.ttype,cl_name,self.name, ",".join(["%s %s"%(c._type,c._name) for c in self.args]), self.body)
        
        BaseOp._format = old_format;BaseStm._level-=1
        return out_str

class StuffContainer(Container):
    def __init__(self, body, counter=0):
        self.body = body
        self.counter = counter
    def __cpp__(self): return self.body
    def __pyth__(self): return "#:"+self.body

    def out(self,to):
        if to == 'cpp': return ""
        elif to == 'hpp': return self.__cpp__()

class ClassContainer(Container):
    def __init__(self, name, fields, methods, parents = [], counter=0):
        # fields: [ (var, "private/public", "static const ...") ]
        self.name = name
        self.fields = fields
        self.methods = methods
        self.counter = counter
        self.parents = parents

    def __cpp__(self) : 
        out_str = ""
        out_str+= "%s %s %s{\n"%("class" if self.methods else "struct", self.name,": %s"%(", ".join(["public %s"%c for c in self.parents])) if self.parents else "")
        tmp_str=""
        for field in filter(lambda x: x[1]=="private",self.fields): tmp_str+= "\t%s %s %s;\n" %(field[2],field[0]._type,field[0]._name)
        for method in filter(lambda x: x.pubpriv=="private",self.methods): tmp_str+= str(method)+"\n"
        out_str+= ("private:\n"+tmp_str) if tmp_str else ""
        tmp_str=""
        for field in filter(lambda x: x[1]=="public",self.fields): tmp_str+= "\t%s %s %s;\n" %(field[2],field[0]._type,field[0]._name)
        for method in filter(lambda x: x.pubpriv=="public",self.methods): tmp_str+= str(method)+"\n"
        out_str+= ("public:\n"+tmp_str) if tmp_str else "" 
        out_str+="\t\n".join(map(str,self.methods))
        out_str+="\n};"
        return out_str

    def __pyt__(self): return "This is python output of ClassContainer"

    def out(self,to):
        old_format,BaseOp._format = BaseOp._format,'cpp'
        out_str = ''
        if to == 'cpp':   out_str += "\n".join(map(lambda X:X.to_cpp(self.name),self.methods)) if self.methods else ""
        elif to == 'hpp': 

            out_str+= "%s %s %s{\n"%("class" if self.methods else "struct", self.name,": %s"%(", ".join(["public %s"%c for c in self.parents])) if self.parents else "")
            tmp_str=""
            for field in filter(lambda x: x[1]=="private",self.fields): tmp_str+= "\t%s %s %s;\n" %(field[2],field[0]._type,field[0]._name)
            for method in filter(lambda x: x.pubpriv=="private",self.methods): tmp_str+= str(method)+"\n"
            out_str+= ("private:\n"+tmp_str) if tmp_str else ""
            tmp_str=""
            for field in filter(lambda x: x[1]=="public",self.fields): tmp_str+= "\t%s %s %s;\n" %(field[2],field[0]._type,field[0]._name)
            for method in filter(lambda x: x.pubpriv=="public",self.methods): tmp_str+= method.to_hpp()+"\n"
            out_str+= ("public:\n"+tmp_str) if tmp_str else "" 
            
            out_str+= "\n};"

        BaseOp._format = old_format
        return out_str
        

class ModuleContainer(Container):
    hashes = []
    stuffs = {}
    # classes = {}
    def __init__(self, module):
        if inspect.getcomments(module):
            for line in inspect.getcomments(module).split("\n")[:-1]:
                if line[1:].split()[0] in 'include define'.split() : self.hashes.append(line)
        for cl in inspect.getmembers(module, lambda X: inspect.isclass(X) and inspect.getsourcefile(X) == inspect.getsourcefile(module) ):
            funcs = []
            fields = []
            for method in filter(lambda X : X[0] not in "__doc__ __module__".split(), inspect.getmembers(cl[1])):
                if inspect.ismethod(method[1]):
                    if method[1].__name__ == 'funcwrap' : funcs.append(method[1](cl[1]()))
                else:
                    if method[1].__class__.__name__ == 'str': fields.append(Var(method[0],method[1]))
           
            self.stuffs[(cl[0],inspect.getsourcelines(cl[1])[1])]=ClassContainer(cl[0],fields ,funcs, parents = [c.__name__ for c in cl[1].__bases__], counter = inspect.getsourcelines(cl[1])[1])
            # self.classes[cl[0]]=ClassContainer(cl[0],fields ,funcs, parents = [c.__name__ for c in cl[1].__bases__], counter = inspect.getsourcelines(cl[1])[1])
        for i,line in enumerate(inspect.getsourcelines(module)[0]):
            if line[:2]=="#:" :
                self.stuffs[(line.strip(),i)] = StuffContainer(line.strip()[2:],counter=i)

    def __cpp__(self):
        L = self.stuffs.values()
        L.sort(lambda a,b:cmp(a.counter,b.counter))
        return  "%s\n%s"%('\n'.join(map(str,self.hashes)),'\n'.join(map(str,L)))

    def __pyt__(self):return "This is python output of ModuleContainer"


    def out(self,to):
        old_format,BaseOp._format = BaseOp._format,'cpp'
        out_str = ''
        if to == 'cpp':   out_str += '#include "model.hpp"' + "%s"
        elif to == 'hpp': out_str += '#ifndef MODEL_HPP\n#define MODEL_HPP\n'+'\n'.join(map(str,self.hashes))+'\nusing namespace aiv;\n' + "%s" + '\n#endif'

        L = self.stuffs.values()
        L.sort(lambda a,b:cmp(a.counter,b.counter))

        out_str=out_str % '\n'.join([c.out(to) for c in L])

        BaseOp._format = old_format
        return out_str
    