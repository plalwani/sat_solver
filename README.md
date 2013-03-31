sat_solver
==========

A satifiability solver using DPLL framework immplemented using C++. 

Terminology:
SAT : Given a boolean formula find a variable assignment such that the formula evaluates to 1 or prove that no such assignment exists.
DPLL : Davis-Putnam-Logemann-Loveland algorithm is aback-tracking based serach algorithm that decides the satisfiability of a boolean formula in Conjunctive normal form (CNF).
CNF: Conjunctive Normal Form i.e. a Product of sums form of representing a boolean function. e.g. (a+b)(c+d)


Description:
SAT solvers prove quite useful in the EDA industry for testing,verfication, timing and power analysis etc.This SAT solver is implemented using DPLL algorithm as a class project for "Digital Systems Design Automation"(ECE 595) at Purdue. Even after 50 years of introduction DPLL is still used a basci framework for most of the modern SAT solvers, DPLL is highhly effective at reducing runtime as compared to the DP algorithm as it keeps track of the explored cases to ensure completeness and does a depth first search of the search space.

Resources:

https://github.com/niklasso/minisat

http://www.dwheeler.com/essays/minisat-user-guide.html

http://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html

http://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html

http://logic.pdmi.ras.ru/~basolver/dimacs.html

https://en.wikipedia.org/wiki/DPLL_algorithm$

Benchmarks:

http://www.cs.ubc.ca/~hoos/SATLIB/benchm.html


