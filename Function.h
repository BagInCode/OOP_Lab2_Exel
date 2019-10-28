#pragma once

#ifndef FUNCTION_CLASS
#define FUNCTION_CLASS

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <math.h>
#include <string>
#include <time.h>
#include <random>
#include <memory.h>
#include <bitset>

using namespace std;

class Function
{
protected:
	vector < pair < int, int > > squares;

public:
	vector < pair < int , int > > getSquares();
	void addSquare(pair < int, int > newSquare);

	virtual long long getValue();

	void operator = (Function rValue);
};

#endif

