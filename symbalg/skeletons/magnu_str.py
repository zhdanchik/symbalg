# -*- encoding: utf-8 -*-
import symbalg
from symbalg.expressions import *
from symbalg.statements import *
from symbalg.funcs import *
from symbalg.ast_funcs import *
from symbalg.cone_funcs import *
from symbalg.generating import *

templates_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "magnu_str")
files = ["model.cpp","model.hpp","model.mk"]

Atom = lambda **kw_args : kw_args

# %(atom_data)s
# %(atom_get_m)s
# %(cell_sz)i // число атомов в ячейке
# %(stage_count)i // число стадий
# %(calc_exch)i // битовая маска, указывающая на каких стадиях считать обменное поле
# %(model_params)s // параметры модели
# %(atom_steps)s

# %(max_nb_count); // максимальное количество соседей у атома
# %(nb_counts)i; // количество соседей у атомов различных подрешеток
# %(nb_arr)s


def mk_module(path, atom, **kw_args):

    old_format,BaseOp._format = BaseOp._format,'cpp'
    module = Module(eval(__name__))

    model_vars = filter(lambda x : x[1].__class__.__name__=="str", kw_args.items())
    model_methods = filter(lambda x : x[1].__class__.__name__=="list", kw_args.items())


    atom_stages_heads = ""
    atom_stages = ""
    model_steps_heads = ""
    model_steps = ""


    def getncheckHexch(myobj):
        get_m = [None]
        ifHexch = [False]
        def _ifHexch(x):
            if isinstance(x,CallOp):
                if str(x._a._name) == "Hexch":
                    ifHexch[0]= True
                    get_m[0] = x._b
                    return x._a
            return x    
        return myobj(_conv=_ifHexch), get_m[0], ifHexch[0]

    for model_method_name, model_method in model_methods:
        model_steps_heads+="\tvoid %s();\n"%model_method_name
        model_steps+= "void Model::%s(){"%model_method_name
        for atom_method_name, atom_method in model_method:
           
            
            
            sts, get_m, ifHexch  = getncheckHexch(atom_method())
            if ifHexch:
                atom_stages_heads += "\tinline void %s(const Model &model, const vctr<3> &Hexch);\n"%(atom_method_name)
                atom_stages += "inline void Atom::%s(const Model &model, const vctr<3> &Hexch){\n"%(atom_method_name)
            else: 
                atom_stages_heads += "\tinline void %s(const Model &model);\n"%(atom_method_name)
                atom_stages += "inline void Atom::%s(const Model &model){\n"%(atom_method_name)


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
            }'''%get_m
                model_steps+="\n\t\t\tatom.%s(*this, Hexch);"%atom_method_name
            else:
                model_steps+="\n\t\t\tatom.%s(*this);"%atom_method_name

            model_steps+='''
        }
    }'''

        model_steps+= "\n}\n"

    
    DD = {}   

    DD["atom_data"] = "\n".join(["\t%s %s;"%(v,k) for k,v in atom.items()])
    
    DD["model_params"] = "\n".join(["\t%s %s;"%(v,k) for k,v in model_vars])

    #---------------------Пока так. Нужна библиотека-----------------------------
    DD["cell_sz"] = 1
    DD["max_nb_count"] = 6
    DD["nb_counts"] = "6"
    DD["nb_arr"] = '''{{Indx(-1, 0, 0),0},
                                             {Indx( 0,-1, 0),0},
                                             {Indx( 0, 0,-1),0},
                                             {Indx( 1, 0, 0),0},
                                             {Indx( 0, 1, 0),0},
                                             {Indx( 0, 0, 1),0}}'''
    #--------------------------------------------------------------------------                                             
    DD["atom_stages_heads"] = atom_stages_heads
    DD["atom_stages"] = atom_stages
    DD["model_steps_heads"] = model_steps_heads
    DD["model_steps"] = model_steps

    generate_1_module_from_str(DD, templates_path, files, path, True)
    BaseOp._format = old_format
 