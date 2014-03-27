#include "token.h"
token::token(){
	data = "";
}

token::token(string d){
	data = d;
	reco();
}

token_type token::type(){
	return data_type;
}

string token::get(){
	return data;
}

void token::set(string d) {
	data = d;
	reco();
}

void token::reco() {
	if(isalpha(data[0])){
        data_type = IDENTIFIER;
    }
    else if(isdigit(data[0])){
        data_type = NUMBER_LITERAL;    
    }
    else if ('"' == data[0]){
        data_type = STRING_LITERAL;
    }
    else if (';' == data[0]){
        data_type = TERMINATOR;
    }
    else{
        data_type = OPERATOR;
    }
}