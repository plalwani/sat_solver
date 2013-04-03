#include <math.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "parser.h"
#include <sstream>
#include <map>



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

  infile.close();
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
