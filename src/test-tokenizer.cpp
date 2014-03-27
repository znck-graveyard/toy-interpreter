#include <iostream>
#include "../inc/tokenizer.h"
using namespace std;
int main(){
    tokenizer t;
    t.read_line();
    while(t.has_token()) {
        cout << t.get_token() << endl;
    }
	return 0;
}
