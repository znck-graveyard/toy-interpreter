#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;
class error
{
protected:
	string err;
public:
	error(){}
	error(string);
	void set(string);
	string get();
};

class error_skip : public error
{
public:
	error_skip():error("ending while loop"){}
};

class blank_line : public error{
public:
    blank_line():error("blank line"){}
};

#endif