#pragma once

#ifndef TABLE_CLASS
#define TABLE_CLASS

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

#include "Square.h"

using namespace std;

class Table
{
	int fieldHigh;
	int fieldLength;

	vector < vector < Square > > thisTable;

public:
	Table();
	Table(int _fieldLength, int _fieldHigh);
	~Table();

	vector < pair < pair < int, int >, string > > updateSquare(pair < int, int > squarePosition, string newFormula);

	Square& getLink(int _positionX, int _positionY);
};

#endif

