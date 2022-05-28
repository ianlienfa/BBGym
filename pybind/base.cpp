#include <iostream>
#include "pybind11/pybind11.h"
#include "user_def/oneRjSumCjPrune.h"
#include "user_def/oneRjSumCj_engine.h"
#include "problem_parser/problemParser.h"
#include "user_def/oneRjSumCjNode.h"
using std::cout, std::endl;

void solveCallbackImpl(void* engine_ptr){}
namespace py = pybind11;


PYBIND11_MODULE(bbgym, m) {
    m.attr("__name__") = "bbgym";
    m.def("solve", []() {        
        if(parse_and_init_oneRjSumCj())
        {
            OneRjSumCj_engine solver; 
            OneRjSumCjGraph graph;
            solver.pruner.prune_funcs = {
                prune__OneRjSumCj__LU_AND_SAL__Theorem1
            };
            solver.pruner.safe_prune_funcs = {
                pruneIncumbentCmpr
            };    
            graph = solver.solve(OneRjSumCjNode());  
        }   
    })
    .def("solve_bfs", [](){
        if(parse_and_init_oneRjSumCj())
        {
            OneRjSumCj_engine solver; 
            solver.searcher.labeler.bfs();
            solver.pruner.prune_funcs = {
                prune__OneRjSumCj__LU_AND_SAL__Theorem1
            };
            solver.pruner.safe_prune_funcs = {
                pruneIncumbentCmpr
            };    
            OneRjSumCjGraph graph;
            graph = solver.solve(OneRjSumCjNode());  
        }   
    })
    .def("solve_brfs", [](){
        if(parse_and_init_oneRjSumCj())
        {
            OneRjSumCj_engine solver; 
            solver.searcher.labeler.brfs();
            solver.pruner.prune_funcs = {
                prune__OneRjSumCj__LU_AND_SAL__Theorem1
            };
            solver.pruner.safe_prune_funcs = {
                pruneIncumbentCmpr
            };    
            OneRjSumCjGraph graph;
            graph = solver.solve(OneRjSumCjNode());  
        }   
    })
    .def("solve_cbfs", [](){
        if(parse_and_init_oneRjSumCj())
        {
            OneRjSumCj_engine solver; 
            solver.searcher.labeler.cbfs();
            solver.pruner.prune_funcs = {
                prune__OneRjSumCj__LU_AND_SAL__Theorem1
            };
            solver.pruner.safe_prune_funcs = {
                pruneIncumbentCmpr
            };    
            OneRjSumCjGraph graph;
            graph = solver.solve(OneRjSumCjNode());  
        }   
    })
    ;
}