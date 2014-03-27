#include <iostream>
#include "../inc/parse.h"
#include "../inc/state.h"
using namespace std;
int main(){
	state s;
	parse p;
	tokenizer t;
	while(cin.good()){
        cout << "> ";
		t.read_line();
		try{
            expression * exp;
            exp = p.get_exp(t);
            int a = exp->eval(s);
            cout << "~ " << a << endl;
            if(t.get() == ";") t.pop();
		} catch(char const * s) {
			cout << endl << "error: "<< s << endl << "\tline:"<<t.get_line_number()<<": "<<t.get_line()<<endl;
		} catch(blank_line *e){
            
        }
        catch(error *e) {
			cout << endl << "error: "<< e->get() << endl << "\tline:"<<t.get_line_number()<<": "<<t.get_line()<<endl;
		}
	}
	return 0;
}
