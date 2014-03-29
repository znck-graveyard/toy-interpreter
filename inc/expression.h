#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>

#include "state.h"
#include "tokenizer.h"
#include "token.h"
#include "error.h"

using namespace std;

class expression
{
protected:
	token tok;
	expression *left;
	expression *right;
public:
	expression();
	expression(string s, expression *, expression *);
	void set(string s, expression *, expression *);
	void set_left(expression *);
	void set_right(expression *);
	token get();
	virtual int eval(state &)=0;
};

class plus_expression : public expression
{
public:
	plus_expression(){};
	plus_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class minus_expression : public expression
{
public:
	minus_expression(){}
	minus_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class multiply_expression : public expression
{
public:
	multiply_expression(){}
	multiply_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class divide_expression : public expression{
public:
    divide_expression(){}
    divide_expression(string s,expression *l, expression *r) : expression(s,l,r){}
    int eval(state &);
};

class assign_expression : public expression
{
public:
	assign_expression(){}
	assign_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class less_than_expression: public expression{
public:
    less_than_expression(){}
    less_than_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class more_than_expression: public expression{
public:
    more_than_expression(){}
    more_than_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class less_than_equal_to_expression: public expression{
public:
    less_than_equal_to_expression(){}
    less_than_equal_to_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class more_than_equal_to_expression: public expression{
public:
    more_than_equal_to_expression(){}
    more_than_equal_to_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class equal_to_expression: public expression{
public:
    equal_to_expression(){}
    equal_to_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class not_equal_to_expression: public expression{
public:
    not_equal_to_expression(){}
    not_equal_to_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class literal_expression : public expression
{
public:
	literal_expression(){}
	literal_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class variable_expression : public expression
{
public:
	variable_expression(){}
	variable_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class empty_expression :public expression
{
public:
	empty_expression(){}
	empty_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

class string_expression : public expression{
public:
    string_expression(){}
    string_expression(string s, expression *l, expression *r):expression(s,l,r){}
    int eval(state &);
};

// TODO implement as statement
class skip_expression : public expression
{
public:
	skip_expression(){}
	skip_expression(string s,expression *l, expression *r):expression(s,l,r){}
	int eval(state &);
};

int string_to_int(string);


#endif