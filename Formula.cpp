#include "Formula.h"

void Formula::create(vector < vector < Formula > >* _myTable, pair < int, int > _myPosition)
{
	myTable = _myTable;
	myPosition = _myPosition;
}

void Formula::setFormula(string newFormula)
{
	isError = 0;
	errorText = "";
	
	for (size_t i = 0; i < referenceTo.size(); i++)
	{
		if (referenceTo[i].first >= myTable->size() || referenceTo[i].second >= myTable->at(0).size())
		{
			continue;
		}

		myTable->at(referenceTo[i].first).at(referenceTo[i].second).deleteReferenceFrom(myPosition);
	}

	referenceTo.clear();

	Parser parser;

	backPolishNotation = parser.parse(newFormula, isError, referenceTo);

	if (isError)
	{
		errorText = "Incorrect formula view";

		backPolishNotation.clear();

		return;
	}

	for (size_t i = 0; i < referenceTo.size(); i++)
	{
		if (referenceTo[i].first >= myTable->size() || referenceTo[i].second >= myTable->at(0).size())
		{
			continue;
		}

		myTable->at(referenceTo[i].first).at(referenceTo[i].second).addReferenceFrom(myPosition);
	}

	return;
}

void Formula::calculate()
{
	if (isError)
	{
		return;
	}

	if (backPolishNotation.size() == 0)
	{
		value = 0;
		return;
	}

	vector < long long > stack;

	for (size_t i = 0; i < backPolishNotation.size(); i++)
	{
		if (backPolishNotation[i].testOperation())
		{
			if (stack.size() < 2)
			{
				setError("Incorrect formula view");

				return;
			}

			long long y = stack.back(); stack.pop_back();
			long long x = stack.back(); stack.pop_back();

			switch (backPolishNotation[i].getOperation())
			{
				case '+':
				{
					stack.push_back(x + y);
				}; break;				
				case '-':
				{
					stack.push_back(x - y);
				}; break;				
				case '*':
				{
					stack.push_back(x * y);
				}; break;				
				case '/':
				{
					if (y == 0)
					{
						setError("Dividing by 0");
					
						return;
					}

					stack.push_back(x / y);
				}; break;				
				case '^':
				{
					stack.push_back(min(x, y));
				}; break;				
				case 'v':
				{
					stack.push_back(max(x, y));
				}; break;				
			}
		}else
		if (backPolishNotation[i].testNumber())
		{
			stack.push_back(backPolishNotation[i].getNumber());
		}else
		{
			pair < int, int > position = backPolishNotation[i].getSquare();

			if (position.first >= myTable->size() || position.second >= myTable->at(0).size())
			{
				setError("Incorrecr argument: position of cell is out of Table range");

				return;
			}

			if (myTable->at(position.first).at(position.second).testError())
			{
				setError("Incorrecr argument: error in cell which this depend by");
				
				return;
			}

			stack.push_back(myTable->at(position.first).at(position.second).getValue());
		}
	}

	if (stack.size() != 1)
	{
		setError("Incorrect formula view");
	
		return;
	}

	value = stack[0];

	return;
}

void Formula::setError(string _errorText)
{
	isError = 1;
	errorText = _errorText;
}

void Formula::update()
{
	if (isError && errorText == "Cicle here")
	{
		return;
	}
	if (isError && errorText == "Incorrect formula view")
	{
		return;
	}

	isError = 0;
	errorText = "";

	calculate();

	for (size_t i = 0; i < referenceFrom.size(); i++)
	{
		string checkErrors = myTable->at(referenceFrom[i].first).at(referenceFrom[i].second).getValueString();

		if (checkErrors == "Incorrect formula view") continue;
		if (checkErrors == "Cicle here") continue;

		myTable->at(referenceFrom[i].first).at(referenceFrom[i].second).update();
	}

	return;
}

long long Formula::getValue()
{
	return value;
}

string Formula::getValueString()
{
	if (isError)
	{
		return errorText;
	}

	if (value == 0)
	{
		if (backPolishNotation.size() == 0)
		{
			return "";
		}else
		{
			return "0";
		}
	}

	long long valueCopy = abs(value);

	string result = "";

	for (; valueCopy; valueCopy /= 10)
	{
		result = result + char(valueCopy % 10 + '0');
	}

	if (value < 0)
	{
		result = result + '-';
	}

	reverse(result.begin(), result.end());

	return result;
}

vector < pair < int, int > >* Formula::getReferenceFrom()
{
	return &referenceFrom;
}

void Formula::prepareToDelete()
{
	for (size_t i = 0; i < referenceTo.size(); i++)
	{
		if (referenceTo[i].first >= myTable->size() || referenceTo[i].second >= myTable->at(0).size())
		{
			continue;
		}

		myTable->at(referenceTo[i].first).at(referenceTo[i].second).deleteReferenceFrom(myPosition);
	}

	return;
}

void Formula::deleteReferenceFrom(pair < int, int > deletedPosition)
{
	for (vector < pair < int, int > > ::iterator it = referenceFrom.begin(); it != referenceFrom.end(); it++)
	{
		if (it->first == deletedPosition.first && it->second == deletedPosition.second)
		{
			referenceFrom.erase(it);

			break;
		}
	}

	return;
}

void Formula::addReferenceFrom(pair < int, int > addedPosition)
{
	referenceFrom.push_back(addedPosition);

	return;
}

bool Formula::testError()
{
	return isError;
}

void Formula::nullCicleError()
{
	if (errorText == "Cicle here")
	{
		isError = 0;
		errorText = "";
	}
}
