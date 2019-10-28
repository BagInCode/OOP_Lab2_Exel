#include "Wrapping.h"

bool Wrapping::testError()
{
	return (dataType < 0);
}

bool Wrapping::testNumber()
{
	return (dataType > 0 && dataType < 4);
}

long long Wrapping::getValue()
{

}

bool Wrapping::testOperation()
{
	return (dataType == 0);
}

long long Wrapping::getOperationType()
{
	return value;
}

vector < pair < int, int > > Wrapping::getSquares()
{

}

Wrapping::Wrapping()
{

}

Wrapping::Wrapping(int _dataType, long long _value)
{
	dataType = _dataType;
	value = _value;
}

Wrapping::Wrapping(Max _maxFunction)
{
	dataType = 2;
	maxFunction = _maxFunction;
}

Wrapping::Wrapping(Min _minFunction)
{
	dataType = 3;
	minFunction = _minFunction;
}

Wrapping::Wrapping(Square* _square)
{
	dataType = 4;
	square = _square;
}

Wrapping::~Wrapping()
{
	square = NULL;
}