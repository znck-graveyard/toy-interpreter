#include "detector.h"
#include <iostream>

block * detector::get(string tok) {
	block * b = NULL;
	if(tok == "if") b = new if_statement();
    else if(tok == "while") b = new while_statement();
    else if(tok == "print") b = new print_statement();
    else if(tok == "exit") b = new exit_statement();
    else b = new compound_statement();
	return b;
}

int detector::see(string tok){
    return (tok == "if" || tok == "while" || tok == "print" || tok == "exit");
}