#pragma once

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

class Wrapping
{
	int dataType = 0;
	char operation = 0;
	long long number = 0;
	pair < int, int > square;

public:
	bool testNumber();
	bool testOperation();
	bool testSquare();

	long long getNumber();
	char getOperation();
	pair < int, int > getSquare();

	void create(long long _number);
	void create(char _operation);
	void create(pair < int, int > _square);

};

