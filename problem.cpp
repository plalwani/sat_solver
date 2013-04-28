#include <math.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "problem.h"
#include <sstream>
#include <map>
#include "parser.h"


const int problem::SOLVED =1;
const int problem::CONFLICT =-1;


void problem::pushClause(std::vector <int> new_row){
  int next_index = P->nextIndex();
  //std::cout << "\nnext index " << next_index <<  "\n";
  removeClause(next_index);
  showStatus2();
  P->addClause(new_row);
  P->updateWatch(next_index);
  activeClauses[num_active] = P->nextIndex();
  P->updateNext();
  num_active++;
  
  showStatus2();
  //exit(0);

 



  showStatus2();
 
}

std::vector<int> problem::findClause(int conf1,int conf2,int branch_var){
  std::vector <int> new_row;

  for(int i = 0; i < P->numTerms(conf1);i++){
    if(abs(P->getTerm(conf1,i)) != branch_var){
      new_row.push_back(P->getTerm(conf1,i));
    }
  }

  if(debug == 1){
    std::cout << "\n";
    for(int i = 0; i < new_row.size();i++){
      std::cout << new_row[i] <<" ";
    }
    std::cout << "\n";
  }

  for(int i = 0; i < P->numTerms(conf2);i++){
    if(abs(P->getTerm(conf2,i)) != branch_var){
      int set = 1;
      for(int j = 0; j < new_row.size();j++){
	if(P->getTerm(conf2,i) == new_row[j]){
	  set = 0;
	  break;
	}
      }
      if(set == 1){
	new_row.push_back(P->getTerm(conf2,i));
      }
    }
  }

  if(debug == 1){
    std::cout << "\n";
    for(int i = 0; i < new_row.size();i++){
      std::cout << new_row[i] <<" ";
    }
    std::cout << "\n";
  }


  return new_row;
}

void problem::printVector(std::vector <int> new_row){
  if(debug == 1){
    std::cout << "\n";
    for(int i = 0; i < new_row.size();i++){
      std::cout << new_row[i] <<" ";
    }
    std::cout << "\n";
  }
}

void problem::addConflict(){
  if(SET->conflict() == 0){
    return;
  }

  //std::cout << "con1 " << con1[level] << " con2 " << con2[level] <<"\n";
  if( con1[level] == 0|| con2[level] == 0){
    return;
  }
  if(con1[level] >= P->org_clauses)
    return;
  if(con2[level] >= P->org_clauses)
   return;
  if(P->nextIndex() % 100 == 0)
    std::cout << "adding clause " << P->num_clauses << "next_idx " << P->nextIndex()<< " \n";

  std::vector <int> new_row = findClause(con1[level],con2[level],trace_val[level]*trace_var[level]);
  printVector(new_row);
  pushClause(new_row);
  
  //exit(0);
}

void problem::addClauseFromIdx(int conf1,int conf2,int branch_var){
  
}

void problem::removeClause(int idx){
  if(P->nextIndex() >= P->num_clauses){
    //std::cout << "no remove";
    return;
  }

  if(idx < P->org_clauses){
    std::cout << "Error removing original clause\n";
    exit(0);
  }
  


  for(int i = 1; i<= level;i++){
    for(int j =0; j < numLevel[i];j++){
      if(levelClauses[i][j] == idx){
	levelClauses[i][j] = levelClauses[i][numLevel[i]-1];
	numLevel[i]--;
      }
      if(levelClauses[i][j] == P->num_clauses-1){
	levelClauses[i][j] =  idx;        
      }

    }
  }



  for(int i = 0; i < num_active;i++){
    if(activeClauses[i] == idx){
      num_active--;
      activeClauses[i] = activeClauses[num_active];
      break;
    }
  }
  
  for(int i = 0; i < num_active;i++){
    if(activeClauses[i] == P->num_clauses -1){
      activeClauses[i] = idx;
      break;
    }
  }

  P->store[idx] = P->store[P->num_clauses-1];
  P->data[idx] = P->data[P->num_clauses-1];
  P->watch1[idx] =   P->watch1[P->num_clauses-1];
  P->watch2[idx] =   P->watch2[P->num_clauses-1];
  P->num_clauses--;

}

void problem::showStatus2(){
  if(debug == 0)
    return;
  std::cout << "Level " << level << " (out of) " << P->getVar() << " variables\n";
  for(int i = 1; i <= P->getVar();i++){
    std::cout << "Trace_var: " << trace_var[i];
    std::cout <<" Trace_val " << trace_val[i];
    std::cout <<" branch " <<branch[i];
    std::cout <<" conf1 " <<con1[i];
    std::cout <<" conf2 " <<con2[i];
    std::cout << " numLevel " << numLevel[i] << " -> ";
    for(int j = 0;j < numLevel[i];j++){
      std::cout << levelClauses[i][j] << " ";
    }
    std::cout << "\n";
  }

  //std::cout << "\n";
  for(int i = 0; i < num_active;i++){
    int idx = activeClauses[i];
    std::cout << i <<" "<<  idx << " wv1: " << P->watch1[idx] << " wv2: " << P->watch2[idx] << "   " ;
    for(int j = 0; j < P->numTerms(idx);j++){
      std::cout << P->getTerm(idx,j) << " "; 
    }
    std::cout <<"\n";
  }
  std::cout <<"\n";
}


problem::problem(std::string output_file){
  debug = 0;
  out_file = output_file;
  std::ofstream out;
  out.open(out_file.data(),std::ofstream::out);
  out.close();

  num_decisions = 0; 
  num_forced = 0;
  num_heuristic = 0;
  num_unit = 0;;

  num_trace = 1;
  trace_var.resize(P->getVar()+1);
  trace_val.resize(P->getVar()+1);
  
  con1.resize(P->getVar()+1);
  con2.resize(P->getVar()+1);

activeClauses.resize(numClauses()*10);
  satClauses.resize(numClauses()*10);

  for(int i = 0; i< numClauses()*10;i++){
    activeClauses[i] = 0;
    satClauses[i] = 0;
  }

}

void problem::solveProblem(){
  version = 2;

  initProblem();
  preProcess();

  if(version == 2){
    std::cout << "Starting DPLL2\n";
    DPLL2();
    return;
  }

  
  std::cout << "Starting DPLL\n";
 
 
  int conf = -1;int mod = 0;
  int status = DPLL(conf,mod);

  if(status == CONFLICT){
     std::cout << "UNSAT!!!!!!!\n";
  }
  if(status == SOLVED){
    std::cout << "SAT!!!\n";
  }

  printStatus();
  saveSolution(status);
}


void problem::updateValues2(){
  P->updateValues();
  return;

  for(int i = 0; i <= P->getVar();i++){
    P->pos_value[i] = 0;
    P->neg_value[i] = 0;
  }

  for(int ii = 0; ii < num_active;ii++){
    int i = activeClauses[ii];
    for(int j = 0; j < P->numTerms(i);j++){
      int idx = abs(P->getTerm(i,j));
      if(P->getTerm(i,j) > 0){
	P->pos_value[idx]++;
      }else{
	P->neg_value[idx]++;
      }
    }
  }
}

void problem::DPLL2(){
  level = 1;
  int status;
  while(level >= 1){
    if(num_decisions % 1000000 == 0 && num_decisions != 0){
      num_decisions++;
      printStatus();
      
    if(num_decisions % 10000 == 0)
      updateValues();
    
    }
    if(num_decisions % 10000 == 0){
      updateValues2();
      num_decisions++;
    }

    showStatus2();
  
    int idx_of_conf_clause = 0;
    status = solutionStatus(idx_of_conf_clause); 
    
    if(status == CONFLICT){
      reverseUpdate2();
      if(branch[level] == 1){
	con1[level] = idx_of_conf_clause;
      }
      if(branch[level] == 2){
	con2[level] = idx_of_conf_clause;
      }

      continue;
    }


    //std::cout << "level "<< level << "\n";

    // if(branch[level] == 1){
    //showStatus2();
    // exit(0);
    //}
    
    if(branch[level] == 1){
      num_forced++;
      doUpdate2(trace_var[level],-trace_val[level]);  
      continue;  
    }

    if(branch[level] == 2){
      addConflict();
      branch[level] = 0;
      con1[level] = 0;
      con2[level] = 0;
      reverseUpdate2();
      continue;
    }

    /*
      
      std::cout << "level: " << level <<" branch " << branch[level] <<  "\n";

      if(branch[level] == 2){
	
	if(level == 0){
	  break;
	}
	
	branch[level] = 0;	
	std::cout << "error\n";
	reverseUpdate2();
	//branch[level] = 0;
	//reverseUpdate2();
	showStatus2();      
	continue;	
      }

     


    }   
    */

  
    
    
  
    
    if(status == SOLVED){
      std::cout << "SAT!!!!!!\n";
      printStatus();
      saveSolution(status);
      return;
    }	
    int branch_var,branch_val,branch_type;

    
    selectBranchVariable(branch_var,branch_val,branch_type);
    doUpdate2(branch_var,branch_val);

    
 

  }
  
  printStatus();
  saveSolution(status);
  std::cout << "UNSAT\n";
}

void problem::reverseUpdate2(){
  // set_vars--;
  level--;  
  P->setVariableStatus(trace_var[level],0);
  activateClauses2(trace_var[level],trace_val[level]);
 
}

void problem::doUpdate2(int branch_var,int branch_val){
  //1. update watchvariables and clause status
  num_decisions++;
  P->setVariableStatus(branch_var,branch_val);
  
  branch[level]++;
  trace_var[level] = branch_var;
  trace_val[level] = branch_val;

  for(int i = num_active-1; i >= 0;i--){
    int idx = activeClauses[i];
    
    if(P->varInClause(idx,branch_var) == branch_val){	 
      deActivate2(i);
    }
    
    if(P->varInClause(idx,branch_var) == -branch_val){
      P->updateWV(idx,branch_var,branch_val);
    }
  }

  level++;
}

void problem::deActivate2(int idx_in_active){
  levelClauses[level][numLevel[level]] = activeClauses[idx_in_active];
  numLevel[level]++;
  num_active--;
  activeClauses[idx_in_active] = activeClauses[num_active];
}

void problem::activateClauses2(int branch_var,int branch_val){
  for(int i = 0; i < numLevel[level];i++){
    activeClauses[num_active] = levelClauses[level][i];    
    num_active++;
  }
  numLevel[level] = 0;
  for(int i = 0;i < num_active;i++){
    int idx = activeClauses[i];

    if(P->watch1[idx] == 0 || P->watch2[idx] == 0 && P->varInClause(idx,branch_var) == -branch_val){
      if(P->watch1[idx] ==  0){
	P->watch1[idx] = -branch_val*branch_var;
      }else if(P->watch1[idx] != branch_val*branch_var){
	P->watch2[idx] = -branch_val*branch_var;
      }      
    }
  }
  
}


void problem::saveSolution(int solved){
  std::ofstream out;
  std::cout << out_file << "\n";
  out.open(out_file.data(),std::ofstream::app);
  
  out << "SAT problem with\n " << P->getVar() << " variables \n " << P->numClauses() << " clauses\n";

  out << "num_decisions " << num_decisions <<"\n"; 
  out << "num forced: " << num_forced << "\n";
  out << "num heuristic "<< num_heuristic << "\n";
  out << "num unit " << num_unit << "\n";


  if(solved == 1){
    out << "  ..is SAT \n";
    for(int i = 1; i <= P->getVar();i++){
      out << "x"<< i << " value " << P->getVariableStatus(i) <<"\n";
    } 
  }

  if(solved == -1){
    out << " ...is NOT UNSATISFIABLE\n";
  }

  out.close();

}


void problem::printOut(std::string text){
  std::ofstream out;
  out.open(out_file.data(),std::ofstream::app);
  out << text << "\n";
  out.close();
}



void problem::preProcess(){
  return;
  int changed = 0;
  int vars = 0;
  for(int i = 1; i<= P->getVar();i++){
    if(P->pos_value[i] ==  0){
      //do update with xi as -1;
      doUpdate2(i,-1);
      vars++;
      continue;
    }
    if(P->neg_value[i] == 0){
      //do update with xi as -1;
      vars++;
      
      doUpdate2(i,1); //i,1,changed);
    }
  }


 std::stringstream s;
  s.clear();
  s <<  "preprocess, vars: " << vars <<" clauses: " <<  changed; 
  std::string save = s.str();
  printOut(save);
  std::cout << save << "\n";
}

void problem::initProblem(){
  //1. set watch variables
  for(int i = 0; i < P->numClauses();i++){
    P->watch1[i] = P->getTerm(i,0);
    P->watch2[i] = P->getTerm(i,1);
  }

  //2.All clauses are set as active
  num_active = numClauses();
  for(int i = 0; i < numClauses();i++){
    activeClauses[i] = i;
  }

  numLevel.resize(P->getVar()+1);
  levelClauses.resize(P->getVar()+1);
  for(int i = 1; i <= P->getVar();i++){
    levelClauses[i].resize(P->max_clauses);
  }
  
  branch.resize(P->getVar()+1);
 

  trace_var.resize(P->getVar()+1);
  trace_val.resize(P->getVar()+1);
  satClauses.resize(P->max_clauses);


  num_sat = 0;
  int* indx_arr = new int [size];
  size = 2*(P->getVar());

}



int problem::solutionStatus(int &conf_idx){
  conf_idx = -1;
  if(num_active == 0){
    return SOLVED;
  }

  for(int idx = 0; idx < num_active;idx++){
    int i = activeClauses[idx];
    if(P->watch1[i] == 0){
      conf_idx = i;
      return CONFLICT;
    }
  }
  
  return 0;
}

void problem::printSolution(){
  for(int i = 1; i <=  P->getVar();i++){
    std::cout <<"Var:  " << i << " val  " << P->getVariableStatus(i) << "\n"; 
  }
}


void problem::printStatus(){
  std::cout << "num_decisions " << num_decisions <<"\n"; 
  std::cout << "num forced: " << num_forced << "\n";
  std::cout << "num heuristic "<< num_heuristic << "\n";
  std::cout << "num unit " << num_unit << "\n";
  std::cout << "num clauses " << P->numClauses() << "\n";

  std::ofstream out;
  std::cout << out_file << "\n";
  out.open(out_file.data(),std::ofstream::app);
  out << "------------------\n";
  out << "num_decisions " << num_decisions <<"\n"; 
  out << "num forced: " << num_forced << "\n";
  out << "num heuristic "<< num_heuristic << "\n";
  out << "num unit " << num_unit << "\n";
  out << "num unit " << P->numClauses() << "\n";
  out << "------------------\n";
  out.close();

}






int problem::DPLL(int &conf_idx,int &mod_changed){
  //status

  mod_changed = 0;
  if(num_decisions % 1000000 == 0 && num_decisions != 0){printStatus();}
  
  if(num_decisions % 10000 == 0){
    updateValues();
  }

  int status = solutionStatus(conf_idx); 
  if(status == CONFLICT|| status == SOLVED){
    return status;
  }
 
  

  //branch
  int branch_var,branch_val,branch_type;
  selectBranchVariable(branch_var,branch_val,branch_type);
 
  int changed_clauses = 0;  
  showStatus();
  doUpdate(branch_var,branch_val,changed_clauses);
 
  int conf1,conf2,mod1,mod2;
  if(DPLL(conf1,mod1) == SOLVED){
    return SOLVED;
  }
  changed_clauses += mod1;
  showStatus();
  reverseUpdate(branch_var,branch_val,changed_clauses);
  showStatus();

  // if(branch_type == 1){
  //return CONFLICT; //unit cluase only one branch
  //}

  branch_val = -branch_val;
  if(debug == 1)
    std::cout << "Branch other! var: " << branch_var << " val: " << branch_val <<"\n";
  
  num_forced++;
  changed_clauses = 0;
  doUpdate(branch_var,branch_val,changed_clauses);
  if(SOLVED == DPLL(conf2,mod2)){
    return SOLVED;
  }
  changed_clauses += mod2;
  reverseUpdate(branch_var,branch_val,changed_clauses);
  

  //mod_changed = addConflictClause(conf1,conf2,branch_var);
  
  return CONFLICT;
}

int problem::addConflictClause(int conf1,int conf2,int branch_var){
  if(!(conf1 != -1 && conf2 != -1)){
    return 0;
  }

  if(debug == 1)
    std::cout << "add conflict clause idx: " << conf1 << " " << conf2 << " var " << branch_var <<  "\n" ;
  std::vector <int> new_clause;

  //if(findClause(conf1,conf2,branch_var,new_clause)){
  //P->addClause(new_clause);
  //int tmp= 0;
  //deActivate(P->clause_counter -1,tmp);
  //return 1;
  //}
  return 0;
}




void problem::reverseUpdate(int branch_var,int branch_val,int changed){
  // set_vars--;

  num_trace--;

  P->setVariableStatus(branch_var,0);
  activateClauses(branch_var,branch_val,changed);
}

void problem::doUpdate(int branch_var,int branch_val,int &clauses_changed){
  //1. update watchvariables and clause status
  num_decisions++;
  P->setVariableStatus(branch_var,branch_val);
  
  trace_var[num_trace] = branch_val*branch_var;
  num_trace++;


  for(int i = num_active-1; i >= 0;i--){
    int idx = activeClauses[i];
    
    if(P->varInClause(idx,branch_var) == branch_val){	 
      deActivate(i,clauses_changed);
    }
    
    if(P->varInClause(idx,branch_var) == -branch_val){
      P->updateWV(idx,branch_var,branch_val);
    }
  }
}

void problem::showStatus(){
  if(debug == 0)
    return;



  std::cout << "Status:\n";
  std::cout << "Trace "; 
  for(int i = 0; i < num_trace;i++){
    std::cout << trace_var[i] << " ";
  }
  std::cout << "\n";
  for(int i = 0; i < num_active;i++){
    int idx = activeClauses[i];
    std::cout << i <<" "<<  idx << " wv1: " << P->watch1[idx] << " wv2: " << P->watch2[idx] << "   " ;
    for(int j = 0; j < P->numTerms(idx);j++){
      std::cout << P->getTerm(idx,j) << " "; 
    }
    std::cout <<"\n";
  }

}

void problem::deActivate(int idx_in_active,int &changed){
  changed++;
  satClauses[num_sat] = activeClauses[idx_in_active];
  num_sat++;
  num_active--;
  activeClauses[idx_in_active] = activeClauses[num_active];
}

void problem::activateClauses(int branch_var,int branch_val,int num){
  for(int i = 0; i < num;i++){
    num_sat--;
    activeClauses[num_active] = satClauses[num_sat];    
    num_active++;
  }

  for(int i = 0;i < num_active;i++){
    int idx = activeClauses[i];

    if(P->watch1[idx] == 0 || P->watch2[idx] == 0 && P->varInClause(idx,branch_var) == -branch_val){
      if(P->watch1[idx] ==  0){
	P->watch1[idx] = -branch_val*branch_var;
      }else if(P->watch1[idx] != branch_val*branch_var){
	P->watch2[idx] = -branch_val*branch_var;
      }      
    }
  }
  
}

int problem::selectBranchVariable(int &branch_var,int &branch_val, int &branch_type){
  //1. check for unit clauses
  //2. value metric

  //std::cout << "Num active " <<num_active <<"\n";
  
  //(0 means none found)
  if(findUnitClause(branch_var,branch_val)){
    num_unit++;
    branch_type = 1;
    if(debug == 1)
      std::cout << "Unit clause branch! on var "<< branch_var << " value " << branch_val << "\n";
    return true;
  }

  //branch metric 
  if(P->branchWithMetric(branch_var,branch_val)){
    if(debug == 1)
      std::cout << "Branch with metric! on var "<< branch_var << " value " << branch_val << "\n";
    num_heuristic++;
    branch_type = 2;
    return true;
  }
  

  std::cout << "ERROR no variable found problem.cpp\n";
  exit(0);
}

int problem::numClauses(){
  return P->numClauses();
}




bool problem::findUnitClause(int &branch_var, int &branch_val){
  if(SET->watch() == 0){
    
    for(int idx = 0; idx < num_active;idx++){
      int i = activeClauses[idx];
      int count = 0;
      
      for(int j = 0;j < P->numTerms(i);j++){
	int var_idx,val;
	P->getTerm(i,j, var_idx, val);
	if(P->getVariableStatus(var_idx) != -val){
	  branch_var = var_idx;
	  branch_val = val;
	  count++;
	}
	
	if(count == 2){
	  break;
	}
      }
      if(count == 1){
	return true;
      }    
    }
  }
  

  if(SET->watch() == 1){
    for(int idx = 0; idx < num_active;idx++){
      int i = activeClauses[idx];
      
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
  }
  
  return false;
}


void problem::updateValues()
{
P->printData();

int temp_arr[size];	// temp array to store the varaible occurence
for(int w = 0; w < size; w++){temp_arr[w] = 0;}	   // make it a zero array

// create unsorted index array
int x = 1;
for(int j = 0; j< size; j+=2)
{
	indx_arr[j] = x;
	indx_arr[j+1] = -x;
	x+=1;
}

int s=0;
// count literal occurence
for(int p = 1; p <= P->getVar(); p++)	//loop over all columns
{
	int pos_cnt = 0;
	int neg_cnt = 0;
	for(int q = 0; q < num_active; q++)	// loop over unsatisfied rows
	{
		int rw = activeClauses[q];	//current row
		if(P->data[rw][p] == 1){pos_cnt+=1;}
		if(P->data[rw][p] == -1){neg_cnt+=1;}
		//std::cout<<"\ndata:"<<P->data[rw][p];
	}
	temp_arr[s] = pos_cnt;
	temp_arr[s+1] = neg_cnt;
	s+=2;
	//std::cout<<"\nvar1 pos:"<<temp_arr[s];
	//std::cout<<"\nvar1 neg:"<<temp_arr[s+1];
}

//for(int e = 0; e < size; e++){std::cout<<"\ntemp_arr:"<<temp_arr[e];}

int temp;
for(int i = 0; i < size; i++)
{
	for(int j = 0; j < size-1; j++)
	{
		if(temp_arr[j] < temp_arr[j+1])
		{
			//sort temp_arr
			temp = temp_arr[j];
			temp_arr[j] = temp_arr[j+1];
			temp_arr[j+1] = temp;

			// sort indx_arr
			temp = indx_arr[j];
			indx_arr[j] = indx_arr[j+1];
			indx_arr[j+1] = temp;
		}
	}
}
//for(int y = 0; y < size; y++){std::cout<<"index array; "<<indx_arr[y];}
}
