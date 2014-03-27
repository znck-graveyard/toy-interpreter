#include "tokenizer.h"

int tokenizer::line_no = 0;

tokenizer::tokenizer(){
}
bool tokenizer::check(string s, char c){
    if(s.length() < 1) return false;
    token reco(s);
    switch(reco.type()){
        case 0:
            return(!isalnum(c) || isspace(c) || c == '(' || c == ')' || c == ';');
            break;
        case 1:
            return(!isdigit(c) || isspace(c) || c == '(' || c == ')' || c == ';');
            break;
        case 2:
            return(s.length() >= 2 && s[s.length()-1] == '"');
            break;
        case 3:
            return(isalnum(c) || isspace(c) || c == '(' || c == ')' || c == ';');
            break;
        case 4:
            return true;
        default:
            return false;
    }
}
void tokenizer::parse(string line) {
#ifdef DEBUG
    cout << "----tokenizer:d: extracting tokens" <<endl;
#endif
    line += ' ';
    string t;
	for(int i = 0; i < line.size(); ++i) {
        if(check(trim(t), line[i])){
            tok.push(trim(t));
            t = "";
        }
        t+=line[i];
    }
}
void tokenizer::read_line(ifstream &inp) {
	char str[256];
    inp.getline(str, 256);
    string l(str); //stl definition
    line = l;
    ++line_no;
#ifdef DEBUG
    cout << "--------parsing line:" << line_no << ": " << line << endl;
    cout << "----tokenize:d: input:"<< line_no << ": "<< line <<endl;
#endif
    parse(trim(l));
}

void tokenizer::read_line() {
	char str[256];
    cin.getline(str, 256);
    string l(str); //stl definition
    line = l;
    ++line_no;
#ifdef DEBUG
    cout << "--------parsing line:" << line_no << ": " << line << endl;
    cout << "----tokenize:d: input:"<< line_no << ": "<< line <<endl;
#endif
    parse(trim(l));
}

int tokenizer::get_line_number(){
    return line_no;
}

string tokenizer::get_line() {
    return line;
}

string tokenizer::get_token(){
    string tok1;
    tok1 = trim(tok.front());
    tok.pop();
    return tok1;
}

string tokenizer::get(){
    if(has_token())
        return trim(tok.front());
    return "";
}

void tokenizer::pop(){
    tok.pop();
}

bool tokenizer::has_token(){
    return (!tok.empty());
}


string trim(string s) {
    int i = 0;
    for(; i < s.length() && isspace(s[i]); ++i);
    int j = (int)s.length() - 1;
    for(; j > 0 && isspace(s[j]); --j);
    if(j < i) return "";
    return s.substr(i, j-i+1);
}