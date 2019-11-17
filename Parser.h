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

#include "Wrapping.h"

using namespace std;

class Parser
{
	bool testNumber(string testIt);
	bool testOperation(char testIt);
	bool testSquare(string testIt);
	bool testFunction(string testIt);

	long long convertNumber(string number);
	pair < int, int > convertSquare(string suqare);

	void splitString(string formula, vector < Wrapping >& splitedString, bool& anyError, set < pair < int, int > >& referenceTo);
	void createBackPolishNotation(vector < Wrapping >& splitedString, vector < Wrapping >& backPolishNotation, bool& anyError);
public:
	vector < Wrapping > parse(string formula, bool& anyError, vector < pair < int, int > >& referenceTo);

};