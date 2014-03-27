#include "expression.h"

expression::expression(){
	left = right = NULL;
}

expression::expression(string s,expression *l, expression *r){
	left = right = NULL;
	set(s, l, r);
}

void expression::set(string s, expression *l = NULL, expression *r = NULL){
	tok.set(s);
	if(NULL != l) left = l;
	if(NULL != r) right = r;
}

void expression::set_left(expression *l){
	left = l;
}

void expression::set_right(expression *r){
	right = r;
}

token expression::get(){
	return tok;
}

int plus_expression::eval(state &s){
#ifdef DEBUG
    cout << "----expression:d: add +" <<endl;
#endif
	if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
	return left->eval(s) + right->eval(s);
}

int minus_expression::eval(state &s){
#ifdef DEBUG
    cout << "----expression:d: subract -" <<endl;
#endif
	if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
	return left->eval(s) - right->eval(s);
}

int multiply_expression::eval(state &s){
	if(NULL == left || NULL == right) {
		throw new error("a*b: operend missing");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: multiply *" <<endl;
#endif
	return left->eval(s) * right->eval(s);
}

int divide_expression::eval(state &s){
	if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: divide /" <<endl;
#endif
	return left->eval(s) / right->eval(s);
}


int assign_expression::eval(state &s){
#ifdef DEBUG
    cout << "----expression:d: assignment :=" <<endl;
#endif
	if(NULL == left || NULL == right) {
		throw "a:=b: operend missing";
		return 0;
	}
	token t = left->get();
	if(IDENTIFIER != t.type()) {
		throw "expected a variable name :=";
		return 0;
	}
	int d = right->eval(s);
	s.set(t.get(), d);
	return d;
}

int less_than_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("a<b: operend missing");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: less than <" <<endl;
#endif
	return left->eval(s) < right->eval(s);
}

int more_than_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: more than >" <<endl;
#endif
	return left->eval(s) > right->eval(s);
}

int less_than_equal_to_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: less than equal to <=" <<endl;
#endif
	return left->eval(s) <= right->eval(s);
}

int more_than_equal_to_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: more than equal to >=" <<endl;
#endif
	return left->eval(s) >= right->eval(s);
}

int equal_to_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: equal to =" <<endl;
#endif
	return left->eval(s) == right->eval(s);
}

int not_equal_to_expression::eval(state &s) {
    if(NULL == left || NULL == right) {
		throw new error("");
		return 0;
	}
#ifdef DEBUG
    cout << "----expression:d: not equal to !=" <<endl;
#endif
	return left->eval(s) != right->eval(s);
}

int literal_expression::eval(state &s){
	return string_to_int(tok.get());
}

int variable_expression::eval(state &s){
	if(!s.is_var(tok.get())) {
		throw new error("variable: "+tok.get()+" not defined");
		return 0;
	}
	return s.get(tok.get());
}

int empty_expression::eval(state &s){
    throw new blank_line();
}

int skip_expression::eval(state &s) {
#ifdef DEBUG
    cout << "----expression:d: skip ?breaks a while loop" <<endl;
#endif
	throw new error_skip();
	return 0;
}

int string_expression::eval(state &s){
#ifdef DEBUG
    cout << "----expression:d: string \"...\"" <<endl;
#endif
    string str = tok.get();
    cout << str.substr(1, str.length()-2) ;
    throw new blank_line();
}

int string_to_int(string s){
	return atoi(s.c_str());
}