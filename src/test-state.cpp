#include <iostream>
#include "../inc/state.h"
using namespace std;
int main(){
	state s;
    s.set("abc", 5);
    if(s.is_var("Abc")) cout<< s.get("abc") <<endl; else cout << "not found" << endl;
    if(s.is_var("abc")) cout<< s.get("abc") <<endl; else cout << "not found" << endl;
	return 0;
}
