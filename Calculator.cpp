#include "Calculator.h"
#include <string>
#include<iostream>
#include<math.h>
using namespace std;

string Calculator::infixPostfix(string expression)
{
	Stack<char> toPostfix;
	
	string postFix = "";
	string previous = "";
	int i = 0;
	while( i < expression.length())
	{
		int weightOfChar = operandWeight(expression[i]);
		
		if (weightOfChar == 0)
		{
			while (expression[i] >= '0' && expression[i] <= '9')
			{
				postFix += expression[i];
				i++;
			}

			postFix += " ";
		}
		else if (weightOfChar == -1)
			i++;
		

		else if (weightOfChar > 0)
		{
			if (toPostfix.empty())
			{
				toPostfix.push(expression[i]);
			}
			else if (expression[i] == ')')
			{
				while (weightOfChar > operandWeight(toPostfix.top()))
				{
					postFix += toPostfix.pop();
					postFix += " ";
				}
				toPostfix.pop();

			}
			else if (weightOfChar == 3 && weightOfChar == operandWeight(toPostfix.top()))
				toPostfix.push(expression[i]);

			else if (expression[i] == '-' && operandWeight(previous[0]) > 0 && previous[0] != ')')
			{
				postFix += expression[i];
			}
				

			else if (weightOfChar > operandWeight(toPostfix.top()))
			{
				toPostfix.push(expression[i]);
			}
			else if (weightOfChar <= operandWeight(toPostfix.top()))
			{
				if (toPostfix.top() == '(')
				{
					toPostfix.push(expression[i]);
				}
				else
				{

					while (!toPostfix.empty() && weightOfChar <= operandWeight(toPostfix.top()) && toPostfix.top() != '(')
					{
						postFix += toPostfix.pop();
						postFix += " ";
					}
					toPostfix.push(expression[i]);
				}
			}

			i++;
		}
		if(expression[i-1] != ' ')
			previous = expression[i-1];
	}
	
	while (!toPostfix.empty())
	{
		postFix += toPostfix.pop();
		postFix += " ";
	}

	return postFix;
}

int Calculator::evaluation(string postfix)
{
	Stack<int> evaluate;
	int i = 0;

	while (i < postfix.length())
	{
		int weightOfChar = operandWeight(postfix[i]);
		int number, first, second;
		string temp = "";
		if (weightOfChar == 0)
		{
			while (postfix[i] >= '0' && postfix[i] <= '9')
			{
				temp += postfix[i];
				i++;
			}

			number = stoi(temp);
			evaluate.push(number);
		}
		else if (weightOfChar == -1)
			i++;
		else if (weightOfChar > 0)
		{
			if (postfix[i] == '-' && (postfix[i + 1] >= '0' && postfix[i + 1] <= '9'))
			{
				temp += postfix[i];
				i++;
				while (postfix[i] >= '0' && postfix[i] <= '9')
				{
					temp += postfix[i];
					i++;
				}
				number = stoi(temp);
				evaluate.push(number);
			}
			else
			{
				second = evaluate.pop();
				first = evaluate.pop();

				if (weightOfChar == 3)
				{
					number = pow(first, second);
					evaluate.push(number);
				}
				else if (weightOfChar == 2)
				{
					if (postfix[i] == '%')
					{
						number = first % second;
						evaluate.push(number);
					}
					else if (postfix[i] == '/')
					{
						number = first / second;
						evaluate.push(number);
					}
					else
					{

						number = first * second;
						evaluate.push(number);
					}
				}
				else if (weightOfChar == 1)
				{
					if (postfix[i] == '-')
					{
						number = first - second;
						evaluate.push(number);
					}
					else
					{
						number = first + second;
						evaluate.push(number);
					}
				}
				i++;
			}
		}

	}
	int result = evaluate.pop();

	return result;
}

int Calculator::operandWeight(char operand)
{
	switch(operand)
	{
	case'+':
	case'-': return 1;
	case'*':
	case'/':
	case'%': return 2;
	case'^': return 3;
	case'(':
	case')': return 4;
	case' ': return -1;
	default: return 0;
	}
}

int Calculator::balance(string input)
{
	Stack<char>toBalance;
	string previous = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '(')
			toBalance.push(input[i]);

		else if (input[i] == ')')
		{
			if (toBalance.empty())
				return 1;

			else if (toBalance.top() == '(' && input[i] == ')')
				toBalance.pop();

			else if (toBalance.top() == '(' && input[i] != ')')
				return 1;

		}
		else if (operandWeight(input[i]) == 0 && input[i] != ' ')
		{
			if (input[i] > '9' || input[i] < '0')
				return 2;
		}
		else if (operandWeight(input[i]) > 0 && operandWeight(previous[0]) > 0 && input[i] != '-' && previous[0] != ')')
			return 3;

		if (input[i] != ' ')
			previous = input[i];
		
	}
	if (toBalance.empty())
		return 0;
	else return 1;
}

