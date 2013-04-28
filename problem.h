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
extern settings * SET;




class problem{
 public:
  static const int SOLVED,CONFLICT;
 private:
  int debug;
  int version;
  int level;

  int num_decisions; 
  int num_forced;
  int num_heuristic;
  int num_unit;
  int size;
  int indx_arr[];	

  void updateValues();
  std::string out_file;
  void DPLL2();
  int DPLL(int &conf_idx,int &mod_changed);
  void initProblem();
  int solutionStatus(int &conf_idx);    

  int num_trace;
  std::vector <int> trace_val;

  std::vector <std::vector<int> > levelClauses;
  std::vector <int> numLevel;
  std::vector <int> trace_var;
  std::vector <int> branch;
  void reverseUpdate2();

  int addConflictClause(int conf1,int conf2,int branch_var);

  void deActivate2(int idx_in_active);
  void doUpdate2(int var,int val);
  void activateClauses2(int branch_var,int branch_val);

  void doUpdate(int var,int val,int &changed);
  void reverseUpdate(int var,int val,int changed);
  bool findUnitClause(int &branch_var, int &branch_val);
  //bool branchWithMetric(int &branch_var, int &branch_val);

  int num_active;
  int num_sat;

  //int set_vars;
  //std::vector <int> variables;

  std::vector <int> satClauses;
  std::vector <int> activeClauses;

  std::vector <int> con2;
  std::vector <int> con1;

  void addConflict();

  void deActivate(int idx,int &changed);
  void activateClauses(int branch_var,int branch_val,int num);

public:

  void removeClause(int idx);
  void addClauseFromIdx(int conf1,int conf2,int branch_var);


  bool findClause(int conf1,int conf2,int branch_var, std::vector <int> &new_row);
  void showStatus();
  void showStatus2();


  void printStatus();
  void preProcess();

  void printSolution();
  void saveSolution(int status);
  void printOut(std::string text);

  problem(std::string out_file_name);
  void solveProblem();
  int selectBranchVariable(int &var,int &val,int &type);
  int numClauses();
};


#endif
