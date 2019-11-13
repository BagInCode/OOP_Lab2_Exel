#include "Table.h"


void Table::create(int _countRow, int _countColumn)
{
	countRow = _countRow;
	countColumn = _countColumn;

	thisTable.resize(countRow);

	for (int i = 0; i < countRow; i++)
	{
		thisTable[i].resize(countColumn);
	
		for (int j = 0; j < countColumn; j++)
		{
			thisTable[i][j].create(&thisTable, { i, j });
		}
	}

	return;
}

vector < vector < string > > Table::create(vector < vector < string > > loadedTable)
{
	vector < vector < string > > result;

	countRow = loadedTable.size();
	countColumn = loadedTable[0].size();

	thisTable.resize(countRow);
	result.resize(countRow);

	for (int i = 0; i < countRow; i++)
	{
		thisTable[i].resize(countColumn);
		result[i].resize(countColumn);

		for (int j = 0; j < countColumn; j++)
		{
			thisTable[i][j].create(&thisTable, { i, j });
			
			if (loadedTable[i][j].size())
			{
				update(loadedTable[i][j], { i,j });
			}
		}
	}

	for (int i = 0; i < countRow; i++)
	{
		for (int j = 0; j < countColumn; j++)
		{
			result[i][j] = thisTable[i][j].getValueString();
		}
	}

	return result;
}

vector < vector < string > > Table::update(string newFormula, pair < int, int > position)
{
	vector < vector < string > > result;

	thisTable[position.first][position.second].setFormula(newFormula);

	for (int i = 0; i < countRow; i++)
	{
		for (int j = 0; j < countColumn; j++)
		{
			thisTable[i][j].nullCicleError();

			if (checkCycles({ i,j }))
			{
				thisTable[i][j].setError("Cicle here");
			}
		}
	}

	for (int i = 0; i < countRow; i++)
	{
		for (int j = 0; j < countColumn; j++)
		{
			thisTable[i][j].update();
		}
	}

	result.resize(countRow);

	for (int i = 0; i < countRow; i++)
	{
		result[i].resize(countColumn);

		for (int j = 0; j < countColumn; j++)
		{
			result[i][j] = thisTable[i][j].getValueString();
		}
	}

	return result;
}

bool Table::checkCycles(pair < int, int > position)
{
	map < pair < int, int >, bool > used;
	used.clear();

	return dfs(position, position, used, 1);
}

bool Table::dfs(pair < int, int > currentPosition, pair < int, int > startPosition, map < pair < int, int >, bool >& used, bool debug)
{
	used[currentPosition] = 1;
	
	vector < pair < int, int > >* edges = thisTable[currentPosition.first][currentPosition.second].getReferenceFrom();
	
	if (edges->size() == 0)
	{
		return 0;
	}

	for (vector < pair < int, int > > ::iterator it = edges->begin(); it != edges->end(); it++)
	{
		if (it->first == startPosition.first && it->second == startPosition.second)
		{
			return 1;
		}

		if (!used[*it])
		{
			if (dfs(*it, startPosition, used))
			{
				return 1;
			}
		}
	}

	return 0;
}

void Table::addRow()
{
	countRow++;
	
	vector < Formula > emptyVector;

	thisTable.push_back(emptyVector);

	for (int i = 0; i < countColumn; i++)
	{
		thisTable[countRow - 1][i].create(&thisTable, { countRow - 1, i });
	}

	return;
}

void Table::addColumn()
{
	countColumn++;

	Formula emptyFormula;

	for (int i = 0; i < countRow; i++)
	{
		thisTable[i].push_back(emptyFormula);

		thisTable[i].back().create(&thisTable, { i, countColumn - 1 });
	}

	return;
}


vector < vector < string > > Table::deleteRow()
{
	for (int i = 0; i < countColumn; i++)
	{
		thisTable[countRow - 1][i].prepareToDelete();
	}

	countRow--;
	thisTable.pop_back();

	vector < vector < string > > result;
	result.resize(countRow);

	for (int i = 0; i < countRow; i++)
	{
		result[i].resize(countColumn);
		for (int j = 0; j < countColumn; j++)
		{
			result[i][j] = thisTable[i][j].getValueString();
		}
	}

	return result;
}

vector < vector < string > > Table::deleteColumn()
{
	for (int i = 0; i < countRow; i++)
	{
		thisTable[i][countColumn - 1].prepareToDelete();
	}

	for (int i = 0; i < countRow; i++)
	{
		thisTable[i].pop_back();
	}

	countColumn--;

	for (int i = 0; i < countRow; i++)
	{
		for (int j = 0; j < countColumn; j++)
		{
			thisTable[i][j].update();
		}
	}

	vector < vector < string > > result;
	result.resize(countRow);

	for (int i = 0; i < countRow; i++)
	{
		result[i].resize(countColumn);
		for (int j = 0; j < countColumn; j++)
		{
			result[i][j] = thisTable[i][j].getValueString();
		}
	}

	return result;
}
