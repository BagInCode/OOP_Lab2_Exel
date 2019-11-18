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
#include "Parser.h"

using namespace std;

class Formula
{
	vector < Wrapping > backPolishNotation;

	pair < int, int > myPosition;

	bool isError = 0;
	string errorText = "";

	long long value = 0;

	vector < pair < int, int > > referenceFrom;
	vector < pair < int, int > > referenceTo;

	vector < vector < Formula > >* myTable = nullptr;

public:
	void create(vector < vector < Formula > >* _myTable, pair < int, int > _myPosition);
	void setFormula(string newFormula);
	void calculate();
	void setError(string _errorText);
	void update();

	long long getValue();

	string getValueString();

	vector < pair < int, int > >* getReferenceFrom();

	void prepareToDelete();
	void deleteReferenceFrom(pair < int, int > deletedPosition);
	void addReferenceFrom(pair < int, int > addedPosition);
	bool testError();

	void nullCycleError();
};