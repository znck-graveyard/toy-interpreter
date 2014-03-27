#include <iostream>
#include <stack>
#include "../inc/state.h"
#include "../inc/tokenizer.h"
#include "../inc/statement.h"
#include "../inc/detector.h"
using namespace std;
int main(){
    state s;
	tokenizer t;
    stack<block *> blocks;
    block *exe;
	while(cin.good()){
        cout << (blocks.size() == 0 ? "> " : ": ");
		t.read_line();
		try{
            while(t.has_token()){
                if(!blocks.empty()) {
                    exe = blocks.top();
                    if(!exe->done()) {
                        block *b;
                        b = exe->build(t);
                        if(NULL != b) {
                            blocks.push(b);
                            exe = b;
                        }
                    }
                    while(NULL != exe && exe->done()) {
                        if(blocks.size() == 1) exe->execute(s);
                        exe = NULL;
                        if(!blocks.empty()) {
                            blocks.pop();
                            if(!blocks.empty())exe = blocks.top();
                        } else exe = NULL;
                    }
                } else {
                    detector d;
                    exe = d.get(t.get());
                    blocks.push(exe);
                    
                }
            }
        } catch(char const * s) {
			cout << endl << "error: "<< s << endl << "\tline:"<<t.get_line_number()<<": "<<t.get_line()<<endl;
		} catch(blank_line *e){
            
        } catch(error *e) {
            s.clear();
            while(!blocks.empty()) blocks.pop();
            while(t.has_token()) t.get_token();
			cout << endl << "error: "<< e->get() << endl << "\tline:"<<t.get_line_number()<<": "<<t.get_line()<<endl;
		}
	}
	return 0;
}
