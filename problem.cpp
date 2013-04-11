#include <math.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "problem.h"
#include <sstream>
#include <map>

const int problem::SOLVED =1;
const int problem::CONFLICT =-1;

problem::problem(){
  SETTING_WATCH_VAR = 0;
}


void problem::solveProblem(){
  std::cout << "Starting DPL\n";
  initProblem();
  
  if(DPLL() == CONFLICT){
     std::cout << "UNSAT!!!!!!!\n";
  }
  std::cout << "COMPLETE\n";
}

void problem::initProblem(){
  //1. set watch variables
  for(int i = 0; i < P->numClauses();i++){
    P->watch1[i] = P->getTerm(i,0);
    P->watch2[i] = P->getTerm(i,1);
  }
}

int problem::solutionStatus(){
  int solved = 1;
  for(int i = 0; i < numClauses();i++){
    if(P->getClauseStatus(i) == 0){
      solved = 0;
    }
    if(P->getClauseStatus(i) == -1){
      std::cout << "conflict clause "<< i << "\n";
      return CONFLICT;
    }
  }
  if(solved == 1){
    std::cout <<"solved !!!!!!!\n";
    printSolution();
    return SOLVED;
  }
  return 0;
}

void problem::printSolution(){
  for(int i = 1; i <=  P->getVar();i++){
    std::cout <<"Var:  " << i << " val  " << P->getVariableStatus(i) << "\n"; 
  }
}

int problem::DPLL(){
  //status
  int status = solutionStatus(); 
  if(status == CONFLICT|| status == SOLVED){
    return status;
  }
 
  //branch
  int branch_var;
  int branch_val;
  selectBranchVariable(branch_var,branch_val);
  std::vector <int> changed_clauses;
  doUpdate(branch_var,branch_val,changed_clauses);
  if(DPLL() == SOLVED){
    return SOLVED;
  }
  reverseUpdate(branch_var,branch_val,changed_clauses);

  changed_clauses.resize(0);
  branch_val = -branch_val;
  std::cout << "Branch other! var: " << branch_var << " val: " << branch_val <<"\n";
  
  doUpdate(branch_var,branch_val,changed_clauses);
  if(SOLVED == DPLL()){
    return SOLVED;
  }
  reverseUpdate(branch_var,branch_val,changed_clauses);

  return CONFLICT;
}


void problem::reverseUpdate(int branch_var,int branch_val,std::vector<int> changed){
  P->setVariableStatus(branch_var,0);
  for(int i = 0; i < changed.size();i++){
    std::cout << "unset clause " << changed[i] <<"\n"; 
    P->setClauseStatus(changed[i],0);
  }
}

void problem::doUpdate(int branch_var,int branch_val,std::vector <int> &changed_idx){
  //1. update watchvariables and clause status
  P->setVariableStatus(branch_var,branch_val);
  if(SETTING_WATCH_VAR == 0){
    for(int i = 0; i < numClauses();i++){
      if(P->getClauseStatus(i) == 0){
	if(P->varInClause(i,branch_var) == branch_val){
	  changed_idx.push_back(i);
	  P->setClauseStatus(i,1);
	  std::cout << "Set clause " << i << "\n";
	}
	
	if(P->varInClause(i,branch_var) == -branch_val){
	  //std::cout <<" checking if we messed up a clause (idx)" << i << "\n";
	  //check if it was the last one
	  for(int j = 0; j < P->numTerms(i);j++){
	    int idx = abs(P->getTerm(i,j));
	    int val;
	    if(P->getTerm(i,j) > 0){
	      val = 1;
	    }else{
	      val = -1;
	    }
	    //std::cout << " checking " << idx << " " << val <<"\n";
	    //std::cout << " match    " << idx << " " << P->getVariableStatus(idx) <<"\n";
	    if(!(P->getVariableStatus(idx) == -val)){
	      // std::cout << " NO mess up " << P->getVariableStatus(idx) << "\n" ;
	      break;
	    }
	    if(j == P->numTerms(i)-1){
	      //std::cout << "CONFLICT!!!" <<"\n";
	      std::cout << "BAN clause " << i << "\n";
	      changed_idx.push_back(i);
	      P->setClauseStatus(i,-1);
	    }
	  }
	  //changed_idx.push_back(i);
	  
	}
	
      }
    }
  }
}

int problem::selectBranchVariable(int &branch_var,int &branch_val){
  //1. check for unit clauses
  //2. value metric

  //(0 means none found)
  if(findUnitClause(branch_var,branch_val)){
    std::cout << "Unit clause branch! on var "<< branch_var << " value " << branch_val << "\n";
    return true;
  }

  //branch metric 
  if(P->branchWithMetric(branch_var,branch_val)){
    std::cout << "Branch with metric! on var "<< branch_var << " value " << branch_val << "\n";
    return true;
  }
  
  std::cout << "ERROR no variable found problem.cpp\n";
  exit(0);
}

int problem::numClauses(){
  return P->numClauses();
}




bool problem::findUnitClause(int &branch_var, int &branch_val){
  for(int i = 0; i < numClauses();i++){
    if(P->watch2[i] == 0){
      branch_var = abs(P->watch1[i]);
      if(P->watch1[i] > 0){
	branch_val = 1;
      }else{
	branch_val = -1;
      }
      return true;
    }
  }
  return false;
}

