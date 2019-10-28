#include "Function.h"

vector < pair < int, int > > Function::getSquares()
{
	return squares;
}


void Function::addSquare(pair < int, int > newSquare)
{
	squares.push_back(newSquare);
}

long long Function::getValue()
{

}

void Function::operator=(Function rValue)
{
	squares = rValue.getSquares();
}