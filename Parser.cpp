#include "Parser.h"

void Parser::splitString(string formula, vector < Wrapping >& splitedString, bool& anyError, set < pair < int, int > >& referenceTo)
{
	string temp = "";

	for (size_t i = 0; i < formula.size(); i++)
	{
		if (formula[i] == ' ')
		{
			continue;
		}
			
		temp = temp + formula[i];
	}

	formula = '(' + temp + ')';

	string formulaPart = "";

	for (size_t i = 1; i < formula.size(); i++)
	{
		if (testOperation(formula[i]))
		{
			if (formula[i] == '-' && formula[i - 1] == '(')
			{
				Wrapping minusOne;
				minusOne.create(-1ll);

				Wrapping mult;
				mult.create('*');

				splitedString.push_back(minusOne);
				splitedString.push_back(mult);

				continue;
			}
			if (formula[i] == '+' && formula[i - 1] == '(')
			{
				continue;
			}

			if (formulaPart.size())
			{
				vector < Wrapping > arguments = getArguments(formula, formulaPart, anyError, i, referenceTo);

				if (anyError)
				{
					return;
				}

				for (size_t j = 0; j < arguments.size(); j++)
				{
					splitedString.push_back(arguments[j]);
				}

				formulaPart = "";
			}

			Wrapping operation;
			operation.create(formula[i]);

			splitedString.push_back(operation);
		}
		else
		{
			formulaPart = formulaPart + formula[i];
		}
	}

	splitedString.pop_back();

	return;
}

void Parser::createBackPolishNotation(vector < Wrapping >& splitedString, vector < Wrapping >& backPolishNotation, bool & anyError)
{
	vector < pair < int, Wrapping > > stack;

	for (size_t i = 0; i < splitedString.size(); i++)
	{
		if (splitedString[i].testOperation())
		{
			if (splitedString[i].getOperation() == '(')
			{
				stack.push_back({ 0, splitedString[i] });

				continue;
			}else
			if (splitedString[i].getOperation() == ')')
			{
				for (; stack.size() && stack.back().second.getOperation() != '('; stack.pop_back())
				{
					backPolishNotation.push_back(stack.back().second);
				}

				if (stack.size() && stack.back().second.getOperation() == '(')
				{
					stack.pop_back();
				}else
				{
					anyError = 1;
				}

				continue;
			}

			int priory = 0;

			if (splitedString[i].getOperation() == '+' || splitedString[i].getOperation() == '-')
			{
				priory = 1;
			}
			if (splitedString[i].getOperation() == '*' || splitedString[i].getOperation() == '/' || splitedString[i].getOperation() == '%')
			{
				priory = 2;
			}
			if (splitedString[i].getOperation() == '^')
			{
				priory = 3;
			}
			if (splitedString[i].getOperation() == '&' || splitedString[i].getOperation() == '|')
			{
				priory = 4;
			}

			if (stack.size() && stack.back().first >= priory)
			{
				backPolishNotation.push_back(stack.back().second);
				stack.pop_back();
			}

			stack.push_back({ priory, splitedString[i] });
		}
		else
		{
			backPolishNotation.push_back(splitedString[i]);
		}
	}

	for (; stack.size(); stack.pop_back())
	{
		backPolishNotation.push_back(stack.back().second);
	}

	return;
}

vector < Wrapping > Parser::parse(string formula, bool& anyError, vector < pair < int, int > > & referenceTo)
{
	vector < Wrapping > result;
	vector < Wrapping > splitedString;

	set < pair < int, int > > references;

	splitString(formula, splitedString, anyError, references);

	if (anyError)
	{
		return result;
	}

	createBackPolishNotation(splitedString, result, anyError);

	for (set < pair < int, int > > ::iterator it = references.begin(); it != references.end(); it++)
	{
		referenceTo.push_back(*it);
	}

	return result;
}

bool Parser::testNumber(string testIt)
{
	bool result = 1;

	for (size_t i = 0; i < testIt.size(); i++)
	{
		if (testIt[i] < '0' || testIt[i] > '9')
		{
			result = 0;
			break;
		}
	}

	return result;
}

bool Parser::testOperation(char testIt)
{
	return(testIt == '+' || testIt == '-' 
		|| testIt == '*' || testIt == '/' || testIt == '%'
		|| testIt == '(' || testIt == ')' 
		|| testIt == '^');
}

bool Parser::testSquare(string testIt)
{
	bool result = 1;
	bool letters = 0;
	bool numbers = 0;

	for (size_t i = 0; i < testIt.size(); i++)
	{
		if (testIt[i] >= 'A' && testIt[i] <= 'Z')
		{
			if (numbers)
			{
				result = 0;
				break;
			}else
			{
				letters = 1;
			}
		}else
		if (testIt[i] >= '0' && testIt[i] <= '9')
		{
			numbers = 1;
		}
		else
		{
			result = 0;
			break;
		}
	}

	result = (result && numbers && letters);

	return result;
}

bool Parser::testFunction(string testIt)
{
	return (testIt == "min" || testIt == "max" || testIt == "inc" || testIt == "dec");
}

long long Parser::convertNumber(string number)
{
	long long result = 0;

	for (size_t i = 0; i < number.size(); i++)
	{
		result = result * 10 + number[i] - '0';
	}

	return result;
}

pair < int, int > Parser::convertSquare(string square)
{
	string letters = "";
	string numbers = "";

	for (size_t i = 0; i < square.size(); i++)
	{
		if (square[i] >= '0' && square[i] <= '9')
		{
			numbers = numbers + square[i];
		}
		else
		{
			letters = letters + square[i];
		}
	}

	pair < int, int > result;

	result.second = convertNumber(numbers) - 1;

	if (result.second < 0 || result.second > 50)
	{
		result.second = 51;
	}

	if (letters.size() > 2)
	{
		result.first = 51;
	}
	else
	if(letters.size() == 1)
	{
		result.first = letters[0] - 'A';
	}
	else
	{
		result.first = (letters[0] - 'A' + 1)* ('Z' - 'A' + 1) + letters[1] - 'A';
	}

	return result;
}

vector < Wrapping > Parser::getArguments(string& formula, string formulaPart, bool& anyError, size_t& i, set < pair < int, int > > & referenceTo)
{
	vector < Wrapping > result;

	if (testNumber(formulaPart))
	{
		result.push_back(workWithNumber(formulaPart));
	}else
	if(testSquare(formulaPart))
	{
		result.push_back(workWithSquare(formulaPart));
	}else
	if (testFunction(formulaPart))
	{
		result = workWtihFunction(formula, formulaPart, anyError, i, referenceTo);
	}else
	{
		anyError = 1;
	}

	return result;
}

Wrapping Parser::workWithNumber(string number)
{
	Wrapping result;

	result.create(convertNumber(number));

	return result;
}

Wrapping Parser::workWithSquare(string square)
{
	Wrapping result;

	result.create(convertSquare(square));

	return result;
}

vector < Wrapping > Parser::workWtihFunction(string& formula, string functionName, bool& anyError, size_t& i, set < pair < int, int > > & referenceTo)
{
	vector < Wrapping > result;
	int countArguments = 0;
	
	if (formula[i] != '(')
	{
		anyError = 1;

		return result;
	}

	string functionPart = "";
	int balance = 0;

	vector < Wrapping > functionActions = getFunctionActions(functionName);

	for (i = i + 1; i < formula.size(); i++)
	{
		if (formula[i] == '(') balance++;
		if (formula[i] == ')') balance--;

		if ((formula[i] == ',' && balance == 0) || (formula[i] == ')' && balance < 0))
		{
			if (functionPart.size() == 0)
			{
				anyError = 1;

				return result;
			}else
			{
				countArguments++;
			}

			vector < Wrapping > arguments;

			splitString(functionPart, arguments, anyError, referenceTo);

			if (anyError)
			{
				return result;
			}

			addArgumentsToVector(arguments, result, functionName, balance);

			functionPart = "";

			if (balance < 0)
			{
				break;
			}
		}
		else
		{
			functionPart = functionPart + formula[i];
		}
	}

	if (!enoughArguments(functionName, countArguments))
	{
		anyError = 1;
	}

	result.pop_back();

	return result;
}

vector < Wrapping > Parser::getFunctionActions(string functionName)
{
	vector < Wrapping > result;

	if (functionName == "min")
	{
		Wrapping action; action.create('&');
		
		result.push_back(action);
	}else
	if (functionName == "max")
	{
		Wrapping action; action.create('|');

		result.push_back(action);
	}else
	if (functionName == "inc")
	{
		Wrapping add; add.create('+');
		Wrapping one; one.create(1ll);

		result.push_back(add);
		result.push_back(one);
	}else
	if (functionName == "dec")
	{
		Wrapping minus; minus.create('-');
		Wrapping one; one.create(1ll);

		result.push_back(minus);
		result.push_back(one);
	}

	return result;
}

bool Parser::enoughArguments(string functionName, int countArguments)
{
	if (functionName == "min")
	{
		return (countArguments != 0);
	}
	else
	if (functionName == "max")
	{
		return (countArguments != 0);
	}
	else
	if (functionName == "inc")
	{
		return (countArguments == 1);
	}
	else
	if (functionName == "dec")
	{
		return (countArguments == 1);
	}
}

void Parser::addArgumentsToVector(vector < Wrapping >& arguments, vector < Wrapping >& addTo, string functionName, int balance)
{
	Wrapping open; open.create('(');
	Wrapping close; close.create(')');

	vector < Wrapping > functionActions = getFunctionActions(functionName);

	addTo.push_back(open);

	for (size_t i = 0; i < arguments.size(); i++)
	{
		addTo.push_back(arguments[i]);
	}

	if (functionName == "inc" || functionName == "dec")
	{
		for (size_t i = 0; i < functionActions.size(); i++)
		{
			addTo.push_back(functionActions[i]);
		}

		addTo.push_back(close);
	}
	else
	{
		addTo.push_back(close);

		if (balance != -1)
		{
			for (size_t i = 0; i < functionActions.size(); i++)
			{
				addTo.push_back(functionActions[i]);
			}
		}
	}

	return;
}