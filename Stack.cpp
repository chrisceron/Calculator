#include<iostream>
#include<string>

#include "Stack.h"
#include "Calculator.h"

using namespace std;

int main()
{
	Calculator calc;
	string expression, postfix;
	char input = NULL;
	Stack<int> testing;
	bool run = true;

	while (run)
	{
		cout << "Please enter an expression or 0 to quit" << endl;
		getline(cin, expression);

		if (expression != "0")
		{
			int validation = calc.balance(expression);

			if (validation == 1)
				cout << "Invalid expression. Please enter correct number of parenthesis." << endl;

			else if (validation == 2)
				cout << "Invalid expression. Please enter a valid operator or integer." << endl;

			else if (validation == 3)
				cout << "Invalid expression. Too many operands." << endl;

			else
			{
				postfix = calc.infixPostfix(expression);
				cout << expression << " = " << calc.evaluation(postfix) << endl << endl;
			}
		}
		else run = false;
	}
	cout << "Good bye!" << endl;
}