#pragma once

#ifndef SQUARE_CLASS
#define SQUARE_CLASS

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

#include "Wrapping.h"
#include "Parser.h"
#include "Table.h"

using namespace std;

class Square
{
	int positionX = 0;
	int positionY = 0;

	long long value = 0;

	bool isError = 0;
	string errorText = "";

	vector < Wrapping > backPolishNotation;

	vector < Square& > referencesFrom;

	Table& myTable = *new Table();

public:

	Square();
	~Square();

	string toString();
	void create(int _positionX, int _positionY, Table& _myTable);
	void calculate();
	bool update(string newFormula, vector < pair < pair < int, int >, string > >& updatedSquares);
	void update(vector < pair < pair < int, int >, string > >& updatedSquares);

	friend void Parser::parseString(string newFormula, vector < Wrapping >& backPolishNotation, bool& anyError, Table& fromTable);
};

#endif