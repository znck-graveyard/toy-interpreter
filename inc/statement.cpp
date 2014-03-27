#include "statement.h"

int statement::execute(state &s) {
#ifdef DEBUG
    cout << "----statement:e: statement" <<endl;
#endif
    return ex->eval(s);
}

block * statement::build(tokenizer &t) {
    parse p;
    switch(part){
        case 0:
            p.set(";");
#ifdef DEBUG
            cout << "----statement:b: 0: statement: expression" <<endl;
#endif
            ex = p.get_exp(t);
            ++part;
            break;
        default:
            throw new error("Unexpected");
    }
    return NULL;
}

bool statement::done() {
    return (1 == part);
}

int compound_statement::execute(state &s) {
#ifdef DEBUG
    cout << "----statement:e: compound statement" <<endl;
#endif
    for(int i = 0; i < child.size(); ++i) child[i]->execute(s);
    return 0;
}

block * compound_statement::build(tokenizer &t) {
    parse p;
    detector d;
    block *b = NULL;
    switch(part){
        case 0:
            if(child.empty()) {
#ifdef DEBUG
                cout << "----statement:b: 0: compound statement: first child" <<endl;
#endif
                if(d.see(t.get())) b = d.get(t.get());
                else b = new statement();
                child.push_back(b);
                break;
            } else if(add_child) {
#ifdef DEBUG
                cout << "----statement:b: 0: compound statement: add child" <<endl;
#endif
                add_child = false;
                if(d.see(t.get())) b = d.get(t.get());
                else b = new statement();
                child.push_back(b);
                break;
            }
            if(t.has_token()){
#ifdef DEBUG
                cout << "----statement:b: 0: compound statement: have some tokens checking for ;" <<endl;
#endif
                if(";" == t.get()) {
#ifdef DEBUG
                    cout << "----statement:b: 0: compound statement: expecting child" <<endl;
#endif
                    t.pop();
                    add_child = true;
                } else {
#ifdef DEBUG
                    cout << "----statement:b: 0: compound statement: ending with token: "+t.get() <<endl;
#endif
                    ++part;
                }
            } else {
#ifdef DEBUG
                cout << "----statement:b: 0: compound statement: ending without token" <<endl;
#endif
                ++part;
            }
            break;
        default:
            throw new error("Unexpected in compound statement");
    }
    return b;
}

bool compound_statement::done() {
    return (1 == part);
}

if_statement::if_statement(){
    part = 0;
	ex = NULL;
}

block * if_statement::build(tokenizer &t) {
    parse p;
    expression *e;
    detector d;
    block * n = NULL;
    switch(part) {
        case 0:
#ifdef DEBUG
            cout << "----statement:e: 0: if statement: if keyword" <<endl;
#endif
            if("if" != t.get()) throw new error("Expected if statement");
            else t.pop(); // removing 'if' from tokenizer object
            p.set("then"); // terminator for parse object
#ifdef DEBUG
            cout << "----statement:b: 0: if statement: ( ? )" <<endl;
#endif
            e = p.get_exp(t);
            ex = e;
            if("then" != t.get()) throw new error("Expected then statement");
            else t.pop();
            if(t.has_token()) throw new error("Expected new line after then statement");
            ++part;
            break;
        case 1:
#ifdef DEBUG
            cout << "----statement:b: 1: if statement: { ? }" <<endl;
#endif
            if_part = n = new compound_statement();
            ++part;
            break;
        case 2:
#ifdef DEBUG
            cout << "----statement:b: 2: if statement: searching <else or fi>" <<endl;
#endif
            if("else" == t.get()) part = 3;
            else if("fi" == t.get()) part = 5;
            else throw new error("Unexpected keyword: "+t.get());
            break;
        case 3:
#ifdef DEBUG
            cout << "----statement:b: 3: if statement: searching for else keyword" <<endl;
#endif
            if("else" != t.get()) throw new error("Expected else statement");
            else t.pop();
            if(t.has_token()) throw new error("Expected new line after else statement");
#ifdef DEBUG
            cout << "----statement:b: 5: if statement: got else keyword" <<endl;
#endif
            ++part;
            break;
        case 4:
            p.set(";");
#ifdef DEBUG
            cout << "----statement:b: 4: if statement: else { ? }" <<endl;
#endif
            else_part = n = new compound_statement();
            ++part;
            break;
        case 5:
#ifdef DEBUG
            cout << "----statement:b: 5: if statement: expecting fi keyword" <<endl;
#endif
            if("fi" != t.get()) throw new error("Expected fi statement");
            else t.pop();
#ifdef DEBUG
            cout << "----statement:b: 5: if statement: removed fi keyword" <<endl;
#endif
            ++part;
            break;
        default:
            throw new error("Unexpected in if statement");
    }
    return n;
}

bool if_statement::done() {
    return (6 == part);
}

int if_statement::execute(state &s) {
#ifdef DEBUG
    cout << "----statement:e: if statement" <<endl;
#endif
    if(!done()) {
        throw new error("Illegal if statement");
        return 0;
    }
	if(0 != ex->eval(s)) {
		if_part->execute(s);
	} else {
		else_part->execute(s);
	}
	return 1;
}

while_statement::while_statement() {
	ex = NULL;
    part = 0;
}

block * while_statement::build(tokenizer &t) {
    parse p;
    expression *e;
    detector d;
    block *b = NULL;
    switch(part){
        case 0:
#ifdef DEBUG
            cout << "----statement:b: 0: while statement: while keyword" <<endl;
#endif
            if("while" != t.get()) throw new error("Expected while statement");
            else t.pop(); // removing 'while' from tokenizer object
            p.set("do"); // terminator for parse object
#ifdef DEBUG
            cout << "----statement:b: 0: while statement: while ( ? )" <<endl;
#endif
            e = p.get_exp(t);
            ex = e;
#ifdef DEBUG
            cout << "----statement:b: 0: while statement: do keyword" <<endl;
#endif
            if("do" != t.get()) throw new error("Expected do statement");
            else t.pop();
            if(t.has_token()) throw new error("Expected new line after do statement");
            ++part;
            break;
        case 1:
#ifdef DEBUG
            cout << "----statement:b: 1: while statement: while () { ? }" <<endl;
#endif
            st = b = new compound_statement();
            ++part;
            break;
        case 2:
#ifdef DEBUG
            cout << "----statement:b: 0: while statement: expecting done keyword" <<endl;
#endif
            if("done" != t.get()) throw new error("Expected done statement");
            else {
#ifdef DEBUG
                cout << "----statement:b: 0: while statement: removed done keyword" <<endl;
#endif
                t.pop(); // removing 'done' from tokenizer object
            }
            ++part;
            break;
        default:
            throw new error("Unexpected in while statement");
    }
    return b;
}

int while_statement::execute(state &s) {
#ifdef DEBUG
    cout << "----statement:e: while statement" <<endl;
#endif
    if(!done()) {
        throw new error("Illegal while statement");
        return 0;
    }
	try {
		while(0 != ex->eval(s)) st->execute(s);
	} catch(error_skip *s) {}
	return 1;
}

bool while_statement::done() {
    return 3 == part;
}

int print_statement::execute(state &s) {
#ifdef DEBUG
    cout << "----statement:e: print statement" <<endl;
#endif

    if(!done()) {
        throw new error("Illegal print statement");
        return 0;
    }
    try{
        cout << ex->eval(s) << endl;
    } catch(blank_line *e){
        cout << endl;
    }
	return 0;
}

block * print_statement::build(tokenizer &t) {
    parse p;
    block * b = NULL;
    switch(part) {
        case 0:
#ifdef DEBUG
            cout << "----statement:b: 0: print statement: print keyword" <<endl;
#endif
            if("print" != t.get()) throw new error("Expected print statement: found - "+t.get());
            else t.pop(); // removing 'print' from tokenizer object
            if(!t.has_token()) throw new error("Expected expression after print statement");
#ifdef DEBUG
            cout << "----statement:b: 0: print statement: print ?" <<endl;
#endif
            ex = p.get_exp(t);
            ++part;
            break;
        default:
            throw new error("Unexpected in print statement");
    }
    return b;
}

bool print_statement::done() {
    return 1 == part;
}

int exit_statement::execute(state &s){
#ifdef DEBUG
    cout << "----statement:e: exit statement" <<endl;
#endif
    if(!done()){
        throw new error("Illegal exit statement");
        return 0;
    }
    exit(0);
    return 0;
}

block * exit_statement::build(tokenizer &t){
    switch(part) {
        case 0:
#ifdef DEBUG
            cout << "----statement:b: 0: exit statement: exit keyword" <<endl;
#endif
            if("exit" != t.get()) throw new error("Expected exit statement: found - "+t.get());
            else t.pop(); // removing 'exit' from tokenizer object
            ++part;
            break;
        default:
            throw new error("Unexpected in exit statement");
    }
    return NULL;
}

bool exit_statement::done(){
    return 1 == part;
}