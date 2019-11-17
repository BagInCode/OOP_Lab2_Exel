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
				setError(1);

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
						setError(4);
					
						return;
					}

					stack.push_back(x / y);
				}; break;			
				case '%':
				{
					if (y == 0)
					{
						setError(4);
					
						return;
					}

					stack.push_back(x % y);
				}; break;				
				case '&':
				{
					stack.push_back(min(x, y));
				}; break;				
				case '|':
				{
					stack.push_back(max(x, y));
				}; break;	
				case '^':
				{
					long long z = binPow(abs(y), x);

					if (y < 0)
					{
						z = 1 / z;
					}

					stack.push_back(z);
				}break;
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
				setError(3);

				return;
			}

			if (myTable->at(position.first).at(position.second).testError())
			{
				setError(2);
				
				return;
			}

			stack.push_back(myTable->at(position.first).at(position.second).getValue());
		}
	}

	if (stack.size() != 1)
	{
		setError(1);
	
		return;
	}

	value = stack[0];

	return;
}

void Formula::setError(int errorType)
{
	const string Errors[5] =
	{
		"This cell is inside cycle",
		"There is incorrect formula view",
		"There is incorrect argument: error in cell, which this depend on",
		"There is incorrect argument: position of cell is out of table range",
		"There is dividing by zero",
	};

	isError = 1;
	errorText = Errors[errorType];

	return;
}

void Formula::update()
{
	if (isError && errorText == "This cell is inside cycle")
	{
		return;
	}
	if (isError && errorText == "There is incorrect formula view")
	{
		return;
	}

	isError = 0;
	errorText = "";

	calculate();

	for (size_t i = 0; i < referenceFrom.size(); i++)
	{
		string checkErrors = myTable->at(referenceFrom[i].first).at(referenceFrom[i].second).getValueString();

		if (checkErrors == "There is incorrect formula view") continue;
		if (checkErrors == "This cell is inside cycle") continue;

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
	if (errorText == "This cell is inside cycle")
	{
		isError = 0;
		errorText = "";
	}
}

long long Formula::binPow(int step, int val)
{
	if (step == 0)
	{
		return 1;
	}

	if (step & 1)
	{
		return binPow(step - 1, val)* val;
	}
	else
	{
		long long temp = binPow(step / 2, val);
		
		return temp * temp;
	}
}