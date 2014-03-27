#ifndef DETECTOR_H
#define DETECTOR_H

#include "statement.h"

class detector
{
public:
	detector(){}
	block * get(string);
    int see(string);
};

#endif