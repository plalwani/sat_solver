/*******************
*****SAT solver*****
********************/

// Created By: Prashant Lalwani and Rickard Ewetz
// Spring 2013
// Description: Basic SAT solver using DPLL algorithm.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "parser.h"
#include "problem.h"

parser * P;
settings * SET;

using namespace std;

int main(int argc, char *argv[])
{
  // If no filename provided, print usage and exit
  if(argc <= 4){
    cout << "Usage:\n" << argv[0] << " <filename> <output> <0/1 (watch variables)> <0/1 (conflict driven learning)> \n";
      exit(0);
  }
  
  std::string path = argv[1];
  std::string output = argv[2];
  std::string use_watch_variables = argv[3];
  std::string conflict_driven_lerning = argv[4];
  SET = new settings(use_watch_variables, conflict_driven_lerning);
  

  //std::cout << "PATH: " << path  << "\n";
  P = new parser(path);
  //P->printValue();
  problem * prob = new problem(output);
  prob->solveProblem();  

  return 0;
}
