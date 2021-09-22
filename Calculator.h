#pragma once
#include "Stack.h"
#include <string>

using namespace std;

class Calculator
{
private:
	string infixExpression;
	string postfixExpression;

public:
	string infixPostfix(string expression);
	int evaluation(string postfix);
	int operandWeight(char operand);
	int balance(string input);
};