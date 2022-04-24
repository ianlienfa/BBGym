#include <iostream>
#include "pybind11/pybind11.h"
#include "user_def/oneRjSumCj_engine.h"
#include "user_def/oneRjSumCjPrune.h"
#include "problem_parser/problemParser.h"
#include "user_def/oneRjSumCjNode.h"
using std::cout, std::endl;

namespace py = pybind11;

PYBIND11_MODULE(bbgym, m) {
    m.attr("__name__") = "bbgym";
    m.def("solve", []() {        
        if(parse_and_init_oneRjSumCj())
        {
            OneRjSumCj_engine solver; 
            OneRjSumCjGraph graph;
            graph = solver.solve(OneRjSumCjNode());  
        }   
    });
}