#ifndef STATE_H
#define STATE_H

#include <map>
#include <string>
#include <cstdlib>

using namespace std;

class state
{
	map<string, int> data;
public:
	state(){}
	int get(string);
	void set(string, int);
	bool is_var(string);
    void clear();
};
#endif