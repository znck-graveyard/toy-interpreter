#include "error.h"

error::error(string s) {
	err = s;
}

void error::set(string s) {
	err = s;
}

string error::get(){
	return err;
}