sat_solver
==========

A satifiability solver using DPLL framework immplemented using C++. 

Usage:
use the included make file to compile the code
# make
Run the sat solver
# ./myrun in_file out_file X Y
where X and Y are binary toggles(1: ON, 0: OFF) for Watched Variables and Conflict Driven Learning respectively.

Looping over Benchmarks:
Use the run_benchmarks.pl file to loop over several benchmarks, read the description in file for usage instructions

Terminology:

SAT : Given a boolean formula find a variable assignment such that the formula evaluates to 1 or prove that no such assignment exists.

DPLL : Davis-Putnam-Logemann-Loveland algorithm is aback-tracking based serach algorithm that decides the satisfiability of a boolean formula in Conjunctive normal form (CNF).

CNF: Conjunctive Normal Form i.e. a Product of sums form of representing a boolean function. e.g. (a+b)(c+d)

DIMACS: Our SAT solver will accept the input file in DIMACS CNF format. Every line beginning with a c is a comment, the first non-comment line is of the form "p cnf NUMBBER_OF_VARIABLES NUMBER_OF_CLAUSES". each non-comment line afterwards defines a clause where postive numbers correspond to a variable and negative numbers correspond to the complement of that variable.

DIMACS Example : 

c This is a comment
p cnf 3 2
1 2 -3
1 2 3

The above example has 3 variable and 2 clauses as (X1 + X2 + X3')(X1 + X2 + X3)

Description:

SAT solvers prove quite useful in the EDA industry for testing,verfication, timing and power analysis etc.This SAT solver is implemented using DPLL algorithm as a class project for "Digital Systems Design Automation"(ECE 595) at Purdue. Even after 50 years of introduction DPLL is still used a basci framework for most of the modern SAT solvers, DPLL is highhly effective at reducing runtime as compared to the DP algorithm as it keeps track of the explored cases to ensure completeness and does a depth first search of the search space.

Resources:

https://github.com/niklasso/minisat

http://www.dwheeler.com/essays/minisat-user-guide.html

http://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html

http://logic.pdmi.ras.ru/~basolver/dimacs.html

https://en.wikipedia.org/wiki/DPLL_algorithm$

https://math.hws.edu/eck/cs225/s03/binary_trees/

Benchmarks:

http://www.cs.ubc.ca/~hoos/SATLIB/benchm.html

ftp://dimacs.rutgers.edu/pub/challenge/satisfiability/benchmarks/

http://stackoverflow.com/questions/12547160/how-does-the-dpll-algorithm-work

http://www.satcompetition.org
