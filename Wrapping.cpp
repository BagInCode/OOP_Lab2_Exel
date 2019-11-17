#include "Wrapping.h" 

bool Wrapping::testNumber()
{
	return (dataType == 1);
}

bool Wrapping::testOperation()
{
	return (dataType == 0);
}

bool Wrapping::testSquare()
{
	return (dataType == 2);
}

long long Wrapping::getNumber()
{
	return number;
}

char Wrapping::getOperation()
{
	return operation;
}

pair < int, int > Wrapping::getSquare()
{
	return square;
}

void Wrapping::create(char _operation)
{
	dataType = 0;
	operation = _operation;
}

void Wrapping::create(long long _number)
{
	dataType = 1;
	number = _number;
}

void Wrapping::create(pair < int, int > _square)
{
	dataType = 2;
	square = _square;
}
