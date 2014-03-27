#ifndef PARSE_H
#define PARSE_H

#include <stack>
#include <iostream>

#include "tokenizer.h"
#include "expression.h"
#include "token.h"

using namespace std;

class parse{
	stack<expression *> exp_stack;
	expression* create_exp(string);
    string _break;
public:
	parse(){
        _break = ";";
    }
	expression* get_exp(tokenizer &);
    void set(string);
};

#endif