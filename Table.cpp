#include "Table.h"


Table::Table()
{

}

Table::Table(int _fieldLength, int _fieldHigh)
{
	fieldHigh = _fieldHigh;
	fieldLength = _fieldLength;

	thisTable.resize(fieldHigh);

	for (int i = 0; i < fieldHigh; i++)
	{
		thisTable[i].resize(fieldLength);

		for (int j = 0; j < fieldLength; i++)
		{
			thisTable[i][j].create(i, j, this);
		}
	}

	return;
}

Table::~Table()
{
	for (int i = 0; i < fieldHigh; i++)
	{
		thisTable[i].clear();
	}

	thisTable.clear();

	return;
}

vector < pair < pair < int, int >, string > > Table::updateSquare(pair < int, int > squarePosition, string newFormula)
{
	vector < pair < pair < int, int >, string > > result;
	
	thisTable[squarePosition.first][squarePosition.second].update(newFormula, result);

	return result;
}


Square& Table::getLink(int _positionX, int _positionY)
{
	Square& result = thisTable[_positionX][_positionY];

	return result;
}