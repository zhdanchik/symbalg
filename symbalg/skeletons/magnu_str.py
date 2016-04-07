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


    atom_steps_heads = ""
    atom_steps = ""
    model_steps_heads = ""
    model_steps = ""


    def getncheckH(myobj):
        body = [None]
        ifH = [False]
        def ifHexch(x):
            if isinstance(x,CallOp):
                if str(x._a._name) == "Hexch":
                    ifH[0]= True
                    body[0] = x._b
                    return x._a
            return x    
        return myobj(_conv=ifHexch), body[0], ifH[0]

    for m_m_name, m_methods in model_methods:
        model_steps_heads+="\tvoid %s();\n"%m_m_name
        model_steps+= "void Model::%s(){"%m_m_name
        for a_m_name, a_methods in m_methods:
            atom_steps_heads += "\tinline void %s(const Model &model, const vctr<3> &Hexch);\n"%(a_m_name)

            tmp = getncheckH(a_methods())
            print tmp

            atom_steps += "inline void Atom::%s(const Model &model, const vctr<3> &Hexch){\n"%(a_m_name)
            atom_steps += str(tmp[0])
            atom_steps += "}\n"

            model_steps+='''
    for(indx<3> pos; pos.less(data.N); ++pos){
        Cell &cell = data[pos];
        for(int l=0; l<cell_sz; ++l){ 
            Atom &atom = cell.atoms[l];
            if(!cell.usage[l]) continue;
            vctr<3> Hexch; 
''' 
            if tmp[2]:
                model_steps+='''
            for(int i=0; i<nb_counts[l]; ++i){ 
                const NbCR &nb = nb_arr[l][i];
                const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos);
                if(cell2.usage[nb.lattice]) Hexch += cell2.atoms[nb.lattice].%s*arrJ[l][nb.lattice];
            }
'''%(tmp[1])
            model_steps+='''
            atom.%s(stage, *this, Hexch);
        }
}
'''%a_m_name

        model_steps+= "}\n"

    
    DD = {}   

    DD["atom_data"] = "\n".join(["\t%s %s;"%(v,k) for k,v in atom.items()])

    DD["cell_sz"] = len(atom)

    DD["model_params"] = "\n".join(["\t%s %s;"%(v,k) for k,v in model_vars])

    DD["max_nb_count"] = 9
    DD["nb_counts"] = "9"
    DD["nb_arr"] = ""

    DD["atom_steps_head"] = atom_steps_heads
    DD["atom_steps"] = atom_steps
    DD["model_steps_heads"] = model_steps_heads
    DD["model_steps"] = model_steps



    generate_1_module_from_str(DD, templates_path, files, path, False)
    BaseOp._format = old_format
 