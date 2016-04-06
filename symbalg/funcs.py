# -*- encoding: utf-8 -*-
import inspect
from expressions import BaseOp, spaceOp, Var
from statements import NamespaceStm, _exec, BaseStm 


def get(members, types=[], pubpriv=""):
    return filter(lambda x : ((x.__class__.__name__ in types) if types else True) and (x.pubpriv == pubpriv if pubpriv else True), members).sorted(cmp=lambda a,b:cmp(a.counter,b.counter))

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
        if "private" in options: 
            pubpriv = "private"
            options.remove("private")
        return Method(func.__name__, localNS.stack[0], [Var(v,t) for v,t in zip(fargs.args,fargs.defaults)]if fargs.defaults else[], preffixes= options, pubpriv=pubpriv, counter=inspect.getsourcelines(func)[1])
    return funcwrap

def myfield(func): #decorator
    def fieldwrap(*args, **kw_args):
        # globalNS = dict(func.func_globals); globalNS.update(spaceOp)
        # localNS = NamespaceStm(kw_args, globalNS) #set args, kw_args
        # lines = inspect.getsource(func).split('\n')
        # _exec('\n'.join(['if 1:']+lines[2:]), globalNS, localNS )
        pubpriv = "public"
        options = []
        if "#:" in lines[1]:
            options = lines[1].split('#:')[-1].strip().split()
        if "private" in options: 
            pubpriv = "private"
            options.remove("private")
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
            if "[" in ttype:
                return "%s %s %s%s%s;"%(" ".join(self.preffixes), self.ttype.split("[")[0], self.name, self.ttype[self.ttype.find("["):], " = %s"%self.value if self.value else "" )
            else: return "%s %s %s%s;"%(" ".join(self.preffixes), self.ttype, self.name, " = %s"%self.value if self.value else "")
        else: raise SymbalgError("Unknown output format for Field : '%s'"%to)    

class Method(Container):
    def __init__(self, name, body, args, preffixes = [], pubpriv = "public", ttype = "void"):   
        self.name = name
        self.body = body
        self.args = args
        self.preffixes = preffixes
        self.pubpriv = pubpriv
        self.ttype = ttype

    def out(to, cl_name = ""):
        if to == "cpp" and self.body is None: return ""
        out_str = "%s %s %s%s(%s)"%(" ".join(self.preffixes), self.ttype, cl_name+("::" if cl_name else ""), self.name, ",".join(["%s %s"%(c._type,c._name) for c in self.args]))
        if self.body is None : return out_str + " = 0;"
        if to in ["full", "cpp"] : return out_str+ "{\n%s}"%self.body.__cpp__
        if to == "hpp" : return out_str + ";"
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
                out_str+= (pubpriv + ":\n" + tmp_str) if tmp_str else ""

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

            # if inspect.ismethod(member[1]):  
            #     if inspect.getsourcefile(member[1]) == inspect.getsourcefile(module):
            #         if member[1].__name__ == 'funcwrap' : members.append(method[1](member[1]()))        
            #         if member[1].__name__ == 'fieldwrap' : members.append(method[1](member[1]()))            

        for i,line in enumerate(inspect.getsourcelines(module)[0]):
            if line[:2]=="#:" :
                self.members[(line.strip(),i)] = Stuff(line.strip()[2:],counter=i)

    def __cpp__(self):
        L = self.members.values()
        L.sort(lambda a,b:cmp(a.counter,b.counter))
        return  "%s\n%s"%('\n'.join(map(str,self.hashes)),'\n'.join(map(str,L)))

    def __pyt__(self):return "This is python output of Module"


    def out(self,to):
        old_format,BaseOp._format = BaseOp._format,'cpp'
        out_str = ''
        if to == 'cpp':   out_str += '#include "model.hpp"' + "%s"
        elif to == 'hpp': out_str += '#ifndef MODEL_HPP\n#define MODEL_HPP\n'+'\n'.join(map(str,self.hashes))+'\nusing namespace aiv;\n' + "%s" + '\n#endif'

        L = self.members
        L.sort(lambda a,b:cmp(a.counter,b.counter))

        out_str=out_str % '\n'.join([c.out(to) for c in L])

        BaseOp._format = old_format
        return out_str


# class Class(Container):
#     def __init__(self, name, fields, methods, parents = [], counter=0):
#         # fields: [ (var, "private/public", ["static","const", ...]) ]
#         self.name = name
#         self.fields = fields
#         self.methods = methods
#         self.counter = counter
#         self.parents = parents
#         self.members = []

#     def __cpp__(self) : 
#         out_str = ""
#         out_str+= "%s %s %s{\n"%("class" if self.methods else "struct", self.name,": %s"%(", ".join(["public %s"%c for c in self.parents])) if self.parents else "")
#         tmp_str=""
#         for stuff in sorted(filter(lambda x: x[2]=="private",self.members),cmp = lambda a,b: cmp(a[1],b[1])): tmp_str+= "\t%s;\n"%stuff[0]
#         for field in filter(lambda x: x[1]=="private",self.fields): tmp_str+= "\t%s %s;\n" %(" ".join(field[2]),cl_field_output(field[0]))
#         for method in filter(lambda x: x.pubpriv=="private",self.methods): tmp_str+= str(method)+"\n"
#         out_str+= ("private:\n"+tmp_str) if tmp_str else ""
#         tmp_str=""
#         for stuff in sorted(filter(lambda x: x[2]=="public",self.members),cmp = lambda a,b: cmp(a[1],b[1])): tmp_str+= "\t%s;\n"%stuff[0]
#         for field in filter(lambda x: x[1]=="public",self.fields): tmp_str+= "\t%s %s;\n" %(" ".join(field[2]),cl_field_output(field[0]))
#         for method in filter(lambda x: x.pubpriv=="public",self.methods): tmp_str+= str(method)+"\n"
#         out_str+= ("public:\n"+tmp_str) if tmp_str else "" 
#         out_str+="};"
#         return out_str

#     def __pyt__(self): return "This is python output of Class"

#     def out(self,to):
#         old_format,BaseOp._format = BaseOp._format,'cpp'
#         out_str = ''
#         if to == 'cpp':   out_str += "\n".join(map(lambda X:X.out("cpp",self.name),self.methods)) if self.methods else ""
#         elif to == 'hpp': 

#             out_str+= "%s %s %s{\n"%("class" if self.methods else "struct", self.name,": %s"%(", ".join(["public %s"%c for c in self.parents])) if self.parents else "")
#             tmp_str=""
#             for stuff in sorted(filter(lambda x: x[2]=="private",self.members),cmp = lambda a,b: cmp(a[1],b[1])): tmp_str+= "\t%s;\n"%stuff[0]
#             for field in filter(lambda x: x[1]=="private",self.fields): tmp_str+= "\t%s %s;\n" %(" ".join(field[2]),cl_field_output(field[0]))
#             for method in filter(lambda x: x.pubpriv=="private",self.methods): tmp_str+= str(method)+"\n"
#             out_str+= ("private:\n"+tmp_str) if tmp_str else ""
#             tmp_str=""
#             for stuff in sorted(filter(lambda x: x[2]=="public",self.members),cmp = lambda a,b: cmp(a[1],b[1])): tmp_str+= "\t%s;\n"%stuff[0]
#             for field in filter(lambda x: x[1]=="public",self.fields): tmp_str+= "\t%s %s;\n" %(" ".join(field[2]),cl_field_output(field[0]))
#             for method in filter(lambda x: x.pubpriv=="public",self.methods): tmp_str+= method.out("hpp")+"\n"
#             out_str+= ("public:\n"+tmp_str) if tmp_str else "" 
#             out_str+= "};"

#         BaseOp._format = old_format
#         return out_str
        



    