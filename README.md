==========
sat_solver
==========

A satifiability solver using DPLL framework immplemented using C++. 


Usage:


The SAT solver can be compiled by using the included make file.

To run the SAT solver the following command can be executed:

./myrun input_file output_file X Y

Where X and Y are binary toggles used to turn On/Off certain functionality. The functionality being:

X -> Watched Variables
Y -> Conflict driven learning

e.g. 

./myrun uf100.cnf uf100.out 1 0

Will run the SAT solver with watched variables and without conflict driven learning on uf100.cnf benchmark and will save the results in uf100.out.

Looping over Benchmarks:

•  A Perl script is also included which is capable of running the SAT solver over several *.cnf benchmarks with all possible On/Off combinations of Watched variables and conflict driven learning. 

•	To run the script, include all your *.cnf files in benchmark folder and run the run_benchmarks.pl script.

•	 The script will loop over all benchmarks and will save the runtime as well as Status (SAT/UNSAT) for each benchmark in Results.csv. 

•	All output files will be available in output_files.tar in the benchmark folder and the runtime files in time_files.tar.



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
