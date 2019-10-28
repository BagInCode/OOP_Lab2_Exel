#include "Square.h"

Square::Square()
{

}

Square::~Square()
{

}


string Square::toString()
{
	if (isError)
	{
		return errorText;
	}

	long long copyValue = value;

	string result = "";

	while (copyValue)
	{
		result = result + char((copyValue % 10) + '0');
		copyValue /= 10;
	}

	reverse(result.begin(), result.end());

	return result;
}

void Square::create(int _positionX, int _positionY, Table& _myTable)
{
	positionX = _positionX;
	positionY = _positionY;

	myTable = _myTable;

	return;
}

void Square::calculate()
{
	vector < long long > stack;

	isError = 0;
	errorText = "";

	for (size_t i = 0; i < backPolishNotation.size(); i++)
	{
		if (backPolishNotation[i].testNumber())
		{
			if (backPolishNotation[i].testError())
			{
				isError = 1;
				errorText = "Error in operands";

				return;
			}

			stack.push_back(backPolishNotation[i].getValue());
		}
		else
		{
			if (stack.size() < 2)
			{
				isError = 1;
				errorText = "Incorrect formula";

				return;
			}

			long long x = stack.back();
			stack.pop_back();

			long long y = stack.back();
			stack.pop_back();
			
			switch (backPolishNotation[i].getOperationType())
			{
				case 0 : 
				{
					stack.push_back(x + y);
				}; break;
				case 1 :
				{
					stack.push_back(x - y);
				}; break;
				case 2 :
				{
					stack.push_back(x * y);
				}; break;
				case 3 :
				{
					if (y == 0)
					{
						isError = 1;
						errorText = "Division by zero";

						return;
					}

					stack.push_back(x / y);
				}; break;
			}
		}
	}

	if (stack.size() > 1)
	{
		isError = 1;
		errorText = "Incorrect formula";

		return;
	}else
	{
		value = stack.back();
	}

	return;
}

bool Square::update(string newFormula, vector < pair < pair < int, int > , string > > & updatedSquares)
{
	Parser* parser = Parser::getParser();
	
	parser->parseString(newFormula, backPolishNotation, isError, myTable);

	if (isError)
	{
		errorText = "Incorrect formula";
	}
}

void Square::update(vector < pair < pair < int, int >, string > > & updatedSquares)
{
	calculate();

	updatedSquares.push_back({ { positionX, positionY }, toString() });

	for (size_t i = 0; i < referencesFrom.size(); i++)
	{
		referencesFrom[i].update(updatedSquares);
	}

	return;
}