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
#include "node.h"

parser * P;


using namespace std;

int main(int argc, char *argv[])
{
  // If no filename provided, print usage and exit
  if(argc <= 1)
    {
      cout << "Usage:\n" << argv[0] << " <filename>\n";
      exit(1);
    }
  
  std::string path = argv[1];
  std::cout << "PATH: " << path  << "\n";
  P = new parser(path);
  P->printData();
  P->printValue();
  problem * prob = new problem();
  prob->solveProblem();  

  return 0;
}
