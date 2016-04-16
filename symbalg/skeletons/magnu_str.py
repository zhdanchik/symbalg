# -*- encoding: utf-8 -*-
import symbalg
from symbalg.expressions import *
from symbalg.statements import *
from symbalg.funcs import *
from symbalg.ast_funcs import *
from symbalg.cone_funcs import *
from symbalg.generating import *

templates_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "magnu_str")

folders = ["magnulib"]
files = ["model.cpp","model.hpp","model.mk", "magnulib/lattice.hpp", "magnulib/geometry.hpp", "magnulib/diag.hpp"]

Atom = lambda **kw_args : kw_args

def mk_module(path, lattice_name, atom, atom_m, **kw_args):

    old_format,BaseOp._format = BaseOp._format,'cpp'
    module = Module(eval(__name__))

    model_vars = filter(lambda x : x[1].__class__.__name__=="str", kw_args.items())
    model_methods = filter(lambda x : x[1].__class__.__name__=="list", kw_args.items())


    atom_stages_heads = ""
    atom_stages = ""
    model_steps_heads = ""
    model_steps = ""

    


    atom_st_m = atom_m
    def getncheckH(myobj, target):
        get_m = [None]
        ifH = [False]
        def _ifHexch(x):
            if isinstance(x,CallOp):
                if str(x._a._name) == target:
                    if isinstance(x._a,Var):
                        ifH[0]= True
                        get_m[0] = x._b
                        return x._a
            return x    
        return myobj(_conv=_ifHexch), get_m[0], ifH[0]

    for model_method_name, model_method in model_methods:
        model_steps_heads+="\tvoid %s();\n"%model_method_name
        model_steps+= "void Model::%s(){"%model_method_name
        for atom_method_name, atom_method in model_method:
           
            
            
            sts, get_m_exch, ifHexch  = getncheckH(atom_method(),"Hexch")
            sts, get_m_aniso, ifHaniso  = getncheckH(sts,"Haniso")
            
            atom_stages_heads += "\tinline void %s(const Model &model"%atom_method_name
            if ifHexch: atom_stages_heads += ", const vctr<3> &Hexch"
            if ifHaniso: atom_stages_heads += ", const vctr<3> &Haniso"
            atom_stages_heads += ");\n"


            atom_stages += "\tinline void Atom::%s(const Model &model"%atom_method_name
            if ifHexch: atom_stages += ", const vctr<3> &Hexch"
            if ifHaniso: atom_stages += ", const vctr<3> &Haniso"
            atom_stages += "){\n"


            Var.__cpp__ = lambda X: ("model."+X._name) if X._name in [a[0] for a in model_vars] else X._name

            lvalues = []
            for st in sts._list:
                if isinstance(st,SetStm):
                    if isinstance(st.lvalue,Var):
                        if (st.lvalue._name not in lvalues) and (st.lvalue._name not in atom):
                            atom_stages+= "auto "
                            lvalues.append(st.lvalue._name)
                atom_stages += str(st)+";\n"

            atom_stages += "}\n"

            
            model_steps+='''
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            if(!cell.usage[l]) continue;
            Atom &atom = cell.atoms[l];''' 

            

            if ifHexch:
                Var.__cpp__ = lambda X: ("atom2."+X._name) if X._name in atom else X._name
                model_steps+='''
            vctr<3> Hexch;    
            for(int i=0; i<nb_counts[l]; ++i){ 
                const NbCR &nb = nb_arr[l][i];
                const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
                if(cell2.usage[nb.lattice]) {
                    const Atom &atom2 = cell2.atoms[nb.lattice];
                    Hexch += (%s)*arrJ[l][nb.lattice];
                }
            }'''%get_m_exch

            if ifHaniso:
                Var.__cpp__ = lambda X: ("atom."+X._name) if X._name in atom else X._name
                model_steps+='''
            vctr<3> Haniso = calc_Haniso(%s, l);'''%get_m_aniso

            model_steps+="\n\t\t\tatom.%s(*this"%atom_method_name
            if ifHexch:  model_steps+=", Hexch"
            if ifHaniso:  model_steps+=", Haniso"
            model_steps+=''');
        }
    }'''

        model_steps+= "\n\ttime+=h;}\n"

    
    DD = {}   

    DD["atom_data"] = "\n".join(["\t%s %s;"%(v,k) for k,v in atom.items()])
    DD["model_params"] = "\n".join(["\t%s %s;"%(v,k) for k,v in model_vars])

    #--------------------------------------------------------------------------                                             
    DD["atom_stages_heads"] = atom_stages_heads
    DD["atom_stages"] = atom_stages
    DD["model_steps_heads"] = model_steps_heads
    DD["model_steps"] = model_steps

    
    DD["atom_m"] = "atom."+atom_m
    DD["atom_st_m"] = "atom."+atom_st_m

    DD["lattice_name"] = lattice_name
    generate_1_module_from_str(DD, templates_path, folders, files, path, True)
    BaseOp._format = old_format
 