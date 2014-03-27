#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum token_type{
    IDENTIFIER,			// 0
    NUMBER_LITERAL, 	// 1
    STRING_LITERAL, 	// 2
    OPERATOR,			// 3
    TERMINATOR			// 4
};

class token{
protected:
    string data;
    token_type data_type;
    void reco();
public:
    token();
    token(string);
    token_type type();
    string get();
    void set(string);
};

#endif