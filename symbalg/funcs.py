# -*- encoding: utf-8 -*-
import inspect
import collections
from expressions import BaseOp, spaceOp, Var
from statements import NamespaceStm, _exec, BaseStm 


def get(members, types=[], pubpriv=""):
    return sorted(filter(lambda x : ((x.__class__.__name__ in types) if types else True) and (x.pubpriv == pubpriv if pubpriv else True), members), cmp=lambda a,b:cmp(a.counter,b.counter))

def mymethod(func): #decorator
    def funcwrap(*args, **kw_args):
        globalNS = dict(func.func_globals); globalNS.update(spaceOp)
        localNS = NamespaceStm(kw_args, globalNS) #set args, kw_args
        lines = inspect.getsource(func).split('\n')
        _exec('\n'.join(['if 1:']+lines[2:]), globalNS, localNS )
        fargs = inspect.getargspec(func)
        pubpriv = "public"
        options = []
        if "#:" in lines[1]:
            options = lines[1].split('#:')[-1].strip().split()
        if "public" in options: options.remove("private")
        if "private" in options: 
            pubpriv = "private"
            options.remove("private")

        fargs = inspect.getargspec(func)
        dictargs = collections.OrderedDict(zip(fargs.args,fargs.defaults)) if fargs.defaults else {}
        
        ttype = dictargs.pop("_type", "void")

        return Method(func.__name__, localNS.stack[0], [Var(v,t) for v,t in dictargs.items()], ttype = ttype, preffixes= options, pubpriv=pubpriv, counter=inspect.getsourcelines(func)[1])
    return funcwrap

def myfield(func): #decorator
    def fieldwrap(*args, **kw_args):
        lines = inspect.getsource(func).split('\n')
        
        pubpriv = "public"
        options = []
        if "#:" in lines[1]:
            options = lines[1].split('#:')[-1].strip().split()
        if "public" in options: options.remove("private")
        if "private" in options: 
            pubpriv = "private"
            options.remove("private")

        fargs = inspect.getargspec(func)
        dictargs = collections.OrderedDict(zip(fargs.args,fargs.defaults)) if fargs.defaults else {}

        ttype = dictargs["_type"] if "_type" in dictargs else "double"
        value = dictargs["_value"] if "_value" in dictargs else None

        return Field(func.__name__, ttype, value, preffixes= options, pubpriv=pubpriv, counter=inspect.getsourcelines(func)[1])
    return fieldwrap


class Container():
    def __str__(self): return getattr( self, '__%s__'%BaseOp._format )()
    def __cpp__(self) : return self.out("full")
    def __pyt__(self) : return "This is python output of %s"%(self.__class__.__name__)

class Field(Container):
    def __init__(self, name, ttype, value = "", preffixes = [], pubpriv = "public", counter=0):
        self.name = name
        self.ttype = ttype
        self.value = value
        self.preffixes = preffixes
        self.pubpriv = pubpriv
        self.counter = counter

    def out(self,to):
        if to == "cpp": return ""
        elif to in ['hpp', 'full']:
            if "[" in self.ttype:
                return "%s %s %s%s%s;"%(" ".join(self.preffixes), self.ttype.split("[")[0], self.name, self.ttype[self.ttype.find("["):], " = %s"%self.value if self.value else "" )
            else: return "%s %s %s%s;"%(" ".join(self.preffixes), self.ttype, self.name, " = %s"%self.value if self.value else "")
        else: raise SymbalgError("Unknown output format for Field : '%s'"%to)    

class Method(Container):
    def __init__(self, name, body, args, ttype = "void", preffixes = [], pubpriv = "public", counter=0):   
        self.name = name
        self.body = body
        self.args = args
        self.ttype = ttype
        self.preffixes = preffixes
        self.pubpriv = pubpriv
        self.counter = counter

    def out(self, to, cl_name = ""):
        if to == "cpp" and self.body is None: return ""

        out_str = "%s %s %s%s(%s)%s"%(" ".join([pr for pr in self.preffixes if pr != 'const']), self.ttype, cl_name+("::" if cl_name else ""), self.name, 
                                       ",".join(["%s %s"%(c._type,c._name) for c in self.args]), " const" if "const" in self.preffixes else "")
        if self.body is None : return out_str + " = 0;"
        
        if to in ["full","cpp"]: return out_str+ "{\n%s}"%self.body
        elif to == "hpp" : return out_str+ ";"
        else: raise SymbalgError("Unknown output format for Method : '%s'"%to)

class Class(Container):
    def __init__(self, name, members, parents = [], counter=0):
        self.name = name
        self.members = members
        self.parents = parents
        self.counter = counter

    def out(self,to):
        out_str = ''

        if to == 'cpp':
            for member in get(self.members,["Method"]): out_str+="\n" + member.out(to,self.name)
        elif to in ['hpp', 'full']:
            out_str+= "class %s %s{"%(self.name,": %s"%(", ".join(["public %s"%c for c in self.parents])) if self.parents else "")
            
            for pubpriv in ["private","public"]:
                tmp_str=""
                for member in get(self.members, pubpriv = pubpriv):
                    tmp_str1 = member.out(to)
                    tmp_str += ("\n\t"+tmp_str1) if tmp_str1 else ""
                out_str+= ("\n"+pubpriv + ":" + tmp_str) if tmp_str else ""

            out_str+="\n};"
        else: raise SymbalgError("Unknown output format for Class : '%s'"%to)

        return out_str

class Stuff(Container):
    def __init__(self, body, counter=0):
        self.body = body
        self.counter = counter
        self.pubpriv = "public"

    def out(self,to):
        if to == "cpp": return ""
        elif to in ['hpp', 'full']:return self.body
        else: raise SymbalgError("Unknown output format for Stuff : '%s'"%to)    

class Module(Container):
    hashes = []
    members = []

    def __init__(self, module):
        if inspect.getcomments(module):
            for line in inspect.getcomments(module).split("\n")[:-1]:
                if line[1:].split()[0] in 'include define'.split() : self.hashes.append(line)
        
        for member in inspect.getmembers(module):
            if inspect.isclass(member[1]):  
                if inspect.getsourcefile(member[1]) == inspect.getsourcefile(module) :
                    members = []
                    for method in filter(lambda X : X[0] not in "__doc__ __module__".split(), inspect.getmembers(member[1])):
                        if inspect.ismethod(method[1]):
                            if method[1].__name__ == 'funcwrap' : members.append(method[1](member[1]()))
                            if method[1].__name__ == 'fieldwrap' : members.append(method[1](member[1]()))

                    self.members.append(Class(member[0], members , parents = [c.__name__ for c in member[1].__bases__], counter = inspect.getsourcelines(member[1])[1]))


            if inspect.isfunction(member[1]):  
                if member[1].__name__ == 'funcwrap' : self.members.append(member[1]())        
                if member[1].__name__ == 'fieldwrap' : self.members.append(member[1]())            

        for i,line in enumerate(inspect.getsourcelines(module)[0]):
            if line[:2]=="#:" :
                self.members.append( Stuff(line.strip()[2:],counter=i))

    def out(self,to):
        old_format,BaseOp._format = BaseOp._format,'cpp'
        out_str = ''
        if to == 'cpp':    out_str += '#include "model.hpp"' + "%s"
        elif to == 'hpp':  out_str += '#ifndef MODEL_HPP\n#define MODEL_HPP\n'+'\n'.join(map(str,self.hashes))+'\nusing namespace aiv;\n' + "%s" + '\n#endif'
        elif to == 'full': out_str += '\n'.join(map(str,self.hashes)) + "%s"

        out_str=out_str % '\n'.join([c.out(to) for c in get(self.members)])
                        
        BaseOp._format = old_format
        return out_str
