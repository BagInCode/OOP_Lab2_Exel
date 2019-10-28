#pragma once

#ifndef WRAPPING_CLASS
#define WRAPPING_CLASS

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

#include "Max.h"
#include "Min.h"
#include "Square.h"

using namespace std;

class Wrapping
{
	int dataType;
	long long value;
	Max maxFunction;
	Min minFunction;
	Square* square = NULL;

public:
	bool testError();

	bool testNumber();
	long long getValue();

	bool testOperation();
	long long getOperationType();

	vector < pair < int, int > > getSquares();

	Wrapping();
	Wrapping(int _dataType, long long value);
	Wrapping(Max _maxFunction);
	Wrapping(Max _minFunction);
	Wrapping(Square* _square);

	~Wrapping();
};

#endif