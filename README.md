## Abstract 

BBGym is a framework for solving scheduling problems with branch and bound algorithms.
The main goal is to use CBFS (cyclic best first search) to mimic differnet behavior of searching strategies to inspect how different searching strategies behaves and what effects they have on different pruning strategies.

## Current Implementation
The current problem this framework is solving is the $1 | r_j | \sum W_jC_j$ single machine scheduling problem[[1]](#1).

## Usage
This project make uses of a util/config.h file to control the user-defined behavior of the solver engine
  * The job number should be manually defined in util/config.h !
  * This is due to the usage of <bitset> for performance enhancement
  * The bad news is that bitset for STL do not support dynamically change on its size
  * For the vanilla Lu algorithm, prune__OneRjSumCj__LU_AND_SAL__Theorem1 must be on
  * the configuration of CI is provided

## References

<a id="1">[1]</a> 
Bianco, Lucio, and Salvatore Ricciardelli. "Scheduling of a single machine to minimize total weighted completion time subject to release dates." Naval Research Logistics Quarterly 29.1 (1982): 151-167.
