#include <math.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "parser.h"
#include <sstream>
#include <map>


int parser::getClauseStatus(int idx){
  return clause_status[idx];
}


int parser::getVariableStatus(int idx){
  return variable_status[idx];
}


void parser::setClauseStatus(int ind, int value){
  clause_status[ind] = value;
}


void parser::setVariableStatus(int ind, int value){
  variable_status[ind] = value;
}



void parser::convertData(){
  int var = getVar();
  
  for(int i = 0; i < numClauses();i++){
    std::vector <int> tmp;
    tmp.resize(var+1);
    data.push_back(tmp);
  }
  
  for(int i = 0; i < numClauses(); i++){
    for(int j = 0; j < numTerms(i);j++){
      //std::cout << getTerm(i,j);
      int line = abs(getTerm(i,j));
      //std::cout << line << "\n";
      if(getTerm(i,j) > 0){
	data[i][line] = 1;
      }else{
	data[i][line] = -1;
      }
    }
  }
  
}


int parser::varInClause(int clause_idx,int var_idx){
  return data[clause_idx][var_idx];
}

void parser::printData(){
  for(int j = 0; j < numClauses();j++){
    for(int i = 1; i <= getVar();i++){
      std::cout << data[j][i] << " ";      
    }
    std::cout << "\n";
  }
}

bool parser::readline(std::ifstream &input, std::string &read_to) {
  //delimiters # % represent comments
  getline(input, read_to);
  int ii = read_to.find_first_not_of(' ');
  if (ii == std::string::npos || read_to[ii] == '#'|| read_to[ii] == '%')
    return false;
  read_to = read_to.substr(ii, read_to.size());
  return true;
}

void parser::readFile(std::ifstream &infile){
  num_clauses = -1;
  num_var = -1;
  std::string line;
  bool validline;
  
  if(!infile.is_open()) {
    std::cout << "input fail in parser.cpp";
    exit(0);
  }
 
  int line_num = 1;
  while (infile.good()) {   
    validline = readline(infile, line);
    
    if(!validline)
      continue;

    if(line.substr(0,1).compare("c") == 0){
      std::cout << "COMMENT " << line << "\n";
      continue;
    }
    
    if(line_num == 1){
      if(!(line.substr(0,1).compare("p") == 0)){
	std::cout << "ERROR format line 1 " << line << "\n";
	exit(0);
      }else{
	std::string dummy;
	std::stringstream out;
	out << line;
	out >> dummy >> dummy >> num_var >> num_clauses;
      }
      //std::cout << "num variables: "<< num_var<< "\n";
      //std::cout << "num clauses: "<< num_var<< "\n";
    }else{
      std::vector <int> tmp;	
      std::stringstream out;
      out << line;
      int num;
      while(out >> num){
	//debug std::cout << num << " ";
	tmp.push_back(num);
      }
      store.push_back(tmp);
    }



    //std::cout << line << "\n";
    line_num++;
  }
  debug();
}

void parser::print(){
  std::cout <<"DISPLAY INPUTFILE\n";
  std::cout << "num variables: " << num_var <<"\nnum clauses: "<<num_clauses<<"\n";
  for(int i = 0; i< store.size();i++){
    for(int j = 0; j < store[i].size();j++){
      std::cout << store[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout <<"END DISPLAY\n";
}

parser::parser(std::string path){
  std::ifstream infile;
  infile.open(path.data(), std::ifstream::in);
  
  if(infile.is_open()){
    std::cout << "PARSING file ************************\n";  
    readFile(infile);
    std::cout << "PARSING DONE ************************\n";  
  }else{
    std::cout << "File could not be obend" << "\n";
    exit(0);
  }
  print();
  infile.close();
 
  convertData();
  variable_status.resize(getVar()+1);
  clause_status.resize(numClauses());
  watch1.resize(numClauses());
  watch2.resize(numClauses());
  pos_value.resize(getVar()+1);
  neg_value.resize(getVar()+1);
  updateValues();
}


bool parser::branchWithMetric(int &branch_var, int &branch_val){
  double best_val = 0;
  branch_var = 0;
  branch_val = 0;

  for(int i = 1; i <= getVar();i++){
    if(getVariableStatus(i) == 0){
      if(pos_value[i] > best_val){
	best_val = pos_value[i];
	branch_var = i;
	branch_val = 1;
      }
      if(neg_value[i] > best_val){
	best_val = neg_value[i];
	branch_var = i;
	branch_val = -1;
      }
      
    }
  }
  if(branch_var != 0){
    return true;
  }
  return false;
}



void parser::updateValues(){
  for(int i = 0; i < getVar()*2;i++){
    pos_value[i] = 0;
    neg_value[i] = 0;
  }

  for(int i = 0; i < numClauses();i++){
    for(int j = 0; j < numTerms(i);j++){
      int idx = abs(getTerm(i,j));
      if(getTerm(i,j) > 0){
	pos_value[idx]++;
      }else{
	neg_value[idx]++;
      }
    }
  }
}

void parser::printValue(){
  
  for(int i = 1;i <= getVar();i++){   
    std::cout << "var: " << i << " pos-val: " << pos_value[i] << " neg-val " << neg_value[i] <<"\n";
  }
}

void parser::varValFromIdx(int idx,int &branch_var,int &branch_val){
  if(idx % 2){
    branch_val = -1;
  }else{
    branch_val = 1;
  }
  branch_var = idx/2 +1;
}

int parser::numClauses(){
  return store.size();
}

int parser::numTerms(int clause_idx){
  if(clause_idx >= numClauses() || clause_idx < 0){
    std::cout << "ERROR requesting numTerms in an invalid clause in parser.cpp\n";
    exit(0);
  }
  return store[clause_idx].size();
}

int parser::getTerm(int clause_idx,int term_idx){
  if(term_idx >= numTerms(clause_idx) || term_idx < 0){
    std::cout << "ERROR requesting getTerm out of bounds parser.cpp\n";
    exit(0);
  }
  return store[clause_idx][term_idx];
}

void parser::debug(){
  if(num_clauses != numClauses()){
    std::cout << "Poblem with input file or parser. Clauses do not match\n";
    exit(0);
  }
}

int parser::getVar(){
  return num_var;
}
