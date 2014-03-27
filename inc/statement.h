#ifndef STATEMENT_H
#define STATEMENT_H

class block;

#include <vector>
#include <stack>
#include "expression.h"
#include "tokenizer.h"
#include "parse.h"
#include "detector.h"

class block{
protected:
    int part;
public:
    block(){part = 0;}
    virtual int execute(state &) = 0;
    virtual block * build(tokenizer &) = 0;
    virtual bool done() = 0;
};

class statement : public block
{
protected:
	expression * ex;
public:
	statement(){}
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class compound_statement : public block{
    vector<block*> child;
    bool add_child;
public:
    compound_statement(){add_child = false; }
    int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class if_statement : public block
{
protected:
	expression *ex;
	block *if_part, *else_part;
public:
	if_statement();
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class while_statement : public block
{
	expression *ex;
    block *st;
public:
	while_statement();
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class print_statement : public block
{
    expression *ex;
public:
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class exit_statement : public block{
public:
    int execute(state &);
    block * build(tokenizer &);
    bool done();
};
#endif