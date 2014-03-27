#include "parse.h"

expression * parse::get_exp(tokenizer &t){
	string tok;
	expression * exp = new empty_expression("", NULL, NULL);
#ifdef DEBUG
    cout << "----parse:d: emtying stack" <<endl;
#endif
	while(!exp_stack.empty())exp_stack.pop();
#ifdef DEBUG
    cout << "----parse:d: building parse tree" <<endl;
    cout << "----parse:d: terminator: " << _break << endl;
    cout << "----parse:d: tokens:" ;
#endif
	while(t.has_token()) {
		tok = (t.get());
#ifdef DEBUG
        cout << " " << tok << " ";
#endif
		if(tok == ")") {
            t.pop();
			if(exp_stack.empty()) throw new error("Invalid expression. Expected an operend after operator.");
			expression *op2 = exp_stack.top();
			exp_stack.pop();
			if(exp_stack.empty()) throw "Invalid expression. Expected an operator.";
			expression *oper = exp_stack.top();
			exp_stack.pop();
			if(exp_stack.empty()) throw "Invalid expression. Expected an operend before operator.";
			expression *op1 = exp_stack.top();
			exp_stack.pop();
			if(exp_stack.empty()) throw "Invalid expression. Expected (";
			exp_stack.pop();
			oper->set_left(op1);
			oper->set_right(op2);
			exp_stack.push(oper);
		} else {
            if(tok == _break || tok == ";") break;
            else{
                expression *e = create_exp(tok);
                exp_stack.push(e);
                t.pop();
            }
		}
	}
    if(exp_stack.size() > 1) throw new error("invalid expression");
    if(!exp_stack.empty()){
        exp = exp_stack.top();
        exp_stack.pop();
    }
#ifdef DEBUG
    cout << "\n----parse:d: parse tree built successfully" <<endl;
#endif
	return exp;
}

expression * parse::create_exp(string s) {
	token t(s);
	expression *var = NULL;
	switch((int)t.type()){
		case 0://IDENTIFIER:
			var = new variable_expression(s, NULL, NULL);
			break;
		case 1://NUMBER_LITERAL:
			var = new literal_expression(s, NULL, NULL);
			break;
		case 3://OPERATOR:
			if(s == "+"){
				var = new plus_expression(s, NULL, NULL);
			} else if(s == "-"){
				var = new minus_expression(s, NULL, NULL);
			} else if(s == "*"){
				var = new multiply_expression(s, NULL, NULL);
			} else if(s == "/"){
				var = new divide_expression(s, NULL, NULL);
			} else if(s == ":="){
				var = new assign_expression(s, NULL, NULL);
			} else if(s == "<"){
				var = new less_than_expression(s, NULL, NULL);
			} else if(s == ">"){
				var = new more_than_expression(s, NULL, NULL);
			} else if(s == "<="){
				var = new less_than_equal_to_expression(s, NULL, NULL);
			} else if(s == ">="){
				var = new more_than_equal_to_expression(s, NULL, NULL);
			} else if(s == "="){
				var = new equal_to_expression(s, NULL, NULL);
			} else if(s == "!="){
				var = new not_equal_to_expression(s, NULL, NULL);
			} else if(s == "(") {
                
            } else
			{
                throw new error("undefined operator: "+s);
			}
			break;
        case 2:
            var = new string_expression(s, NULL, NULL);
            break;
    }
	return var;
}

void parse::set(string s) {
    _break = s;
}