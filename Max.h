#pragma once

#ifndef MAX_CLASS
#define MAX_CLASS

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
#include "Function.h"

using namespace std;

class Max : Function
{
public:
	virtual long long getValue() override;
};

#endif

