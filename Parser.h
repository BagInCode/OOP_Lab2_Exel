#pragma once

#ifndef PARCER_CLASS
#define PARSER_CLASS

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

using namespace std;

class Parser
{
	static Parser* parser;

	Parser();

	void splitString(string newFormula);
	void createBackPolishNotation(vector < Wrapping >& backPolishNotation);

public:
	void parseString(string newFormula, vector < Wrapping >& backPolishNotation, bool & anyError, Table& fromTable);
	vector < pair < int, int > > checkCycles();

	static Parser* getParser();

};

#endif
