#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <map>

//This class in intended to read the inputfile and store it in an array.
//acces functions can then be used to obtain the input data

// CLAUSES: N is the number of clauses (..)(..)  
// TERMS: M_i is the number of terms in clause i.   
// 
// Notation: All indexes start on 0.


class parser{
  bool readline(std::ifstream &input, std::string &read_to);
  std::vector <std::vector <int> > store;
  
  std::vector <std::vector <int> > data;
 
  std::vector <int> clause_status;
  std::vector <int> variable_status;
 public:
  std::vector <int> watch1;
  std::vector <int> watch2;

  std::vector <int> pos_value;
  std::vector <int> neg_value;
 private :
  void readFile(std::ifstream &infile);
  void debug();
  int num_clauses;
  int num_var;

  int org_clauses;
 public:
  int clause_counter;
  int max_clauses;

public:
	parser(std::string inputfile);
	int numClauses();
	int numTerms(int bracket_idx); //get terms in clasue_idx
	int getTerm(int bracket_idx,int term_idx);
	int getVar(); 
	void print();
	void printData();
	void convertData();

	void printValue();

	int varInClause(int clause_idx,int var_idx);


	void getTerm(int clause_idx,int term_idx,int &branch_var,int &branch_val);
       
	
	void updateValues();
	int idxFromVarVal(int var_val);

	bool branchWithMetric(int &branch_var, int &branch_val);

	int getClauseStatus(int idx);
	int getVariableStatus(int idx);
	void setVariableStatus(int idx,int val);
	void setClauseStatus(int idx, int val);

	bool needNewWatch(int idx_clause,int var,int val);
	void updateWatch(int idx);
	void updateWV(int clause_idx,int branch_var,int branch_val);

	bool notRedundent(std::vector <int> new_clause);
	bool addClause(std::vector <int> new_clause);

	void pushClause(std::vector<int> new_clause,int idx);
};


class settings{
 public:
  
  int watch_var;
  int conflict_var;

  settings(std::string,std::string);
  int watch();
  int conflict();
};


int string2int(std::string var_str);

#endif
