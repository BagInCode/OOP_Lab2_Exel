#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <math.h>
#include <time.h>
#include <random>
#include <memory.h>
#include <bitset>

#include "Formula.h"

using namespace std;

class Table
{
	vector < vector < Formula > > thisTable;

	int countColumn;
	int countRow;

	bool checkCycles(pair < int, int > position);
	bool dfs(pair < int, int > currentPosition, pair < int, int > startPosition, map < pair < int, int >, bool >& used);

public:
	void create(int _countRow, int _countColumn);
	vector < vector < string > > create(vector < vector < string > > loadedTable);

	vector < vector < string > > update(string newFormula, pair < int, int > position);

	vector < vector < string > > addRow();
	vector < vector < string > > addColumn();

	vector < vector < string > > deleteRow();
	vector < vector < string > > deleteColumn();

	void clear();
};

