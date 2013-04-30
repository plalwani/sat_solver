==========
sat_solver
==========

A satifiability solver using DPLL framework immplemented using C++. 
Included Project Report has all other details. 



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



Directory Structure:

• Makefile: Used for compiling the code
•	Run_benchmarks.pl: A perl script capable of looping over benchmarks
•	Results.csv: Runtime file dumped by benchmarking script
•	Benchmarks.tar: All benchmarks that were used for testing
•	Myrun: executable to run individual input files
•	Parser.h: Header file with the input parser class and init function declarations
•	Parser.cpp: Input parser code
•	Problem.h: header file with all the DPLL functions
•	Problem.cpp: Algorithm code
•	Sat_solver.cpp: Code to execute DPLL

