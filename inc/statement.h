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
#ifdef DEBUG
    virtual string name() = 0;
#endif
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
#ifdef DEBUG
    string name() {return "normal";}
#endif
	statement(){}
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class compound_statement : public block{
    vector<block*> child;
    bool add_child;
public:
#ifdef DEBUG
    string name() {return "compound";}
#endif
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
#ifdef DEBUG
    string name() {return "if";}
#endif
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
#ifdef DEBUG
    string name() {return "while";};
#endif
	while_statement();
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class print_statement : public block
{
    expression *ex;
public:
#ifdef DEBUG
    string name() {return "print";}
#endif
	int execute(state &);
    block * build(tokenizer &);
    bool done();
};

class exit_statement : public block{
public:
#ifdef DEBUG
    string name() {return "exit";}
#endif
    int execute(state &);
    block * build(tokenizer &);
    bool done();
};
#endif