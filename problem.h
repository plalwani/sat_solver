#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <map>
#include "parser.h"


//This class is the main class in the dpl algorithm.

extern parser * P;

class problem{
 public:
  static const int SOLVED,CONFLICT;
 private:

  int SETTING_WATCH_VAR;


  int DPLL();
  void initProblem();
  int solutionStatus();    

  void doUpdate(int var,int val,std::vector<int> &change);
  void reverseUpdate(int var,int val,std::vector<int> change);
  bool findUnitClause(int &branch_var, int &branch_val);
  //bool branchWithMetric(int &branch_var, int &branch_val);


public:

  void printSolution();
  problem();
  void solveProblem();
  int selectBranchVariable(int &var,int &val);
  int numClauses();
};


#endif
