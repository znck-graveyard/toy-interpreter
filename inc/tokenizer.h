#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <sstream>
#include <queue>
#include <iostream>
#include <fstream>
#include <cctype>
#include "token.h"

using namespace std;

class tokenizer{
	static int line_no;
	string line;
    queue<string> tok;
    bool check(string, char);
public:
	tokenizer();
    void parse(string);
    void read_line();
    void read_line(ifstream &);
    string get_token();
    string get();
    void pop();
    bool has_token();
    int get_line_number();
    string get_line();
};

string trim(string);
#endif