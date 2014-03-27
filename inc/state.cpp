#include "state.h"

int state::get(string key) {
	return data.find(key)->second;
}

void state::set(string key, int value) {
	pair<map<string,int>::iterator,bool> ret;
	ret = data.insert(pair<string, int> (key, value));
	if(ret.second == false){
		data.erase(ret.first);
		data.insert(pair<string, int> (key, value));
	}
}

bool state::is_var(string key) {
	map<string, int>::iterator it;
	it = data.find(key);
	if(it == data.end()) return false;
	return true;
}

void state::clear(){
    // TODO delete all variables
}