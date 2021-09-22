#pragma once
#include<string>

template <class E> class Stack
{
private:
	E expression[20];
	int numElements;
	int insertion;


public:
	Stack();
	int size() const;
	bool empty() const;
	const E top();
	void push(E input);
	E pop();

};

template<class E> inline Stack<E>::Stack()
{
	numElements = 0;
	insertion = -1;
}

template<class E> inline int Stack<E>::size() const
{
	return numElements;
}

template<class E> inline bool Stack<E>::empty() const
{
	if (numElements == 0)
		return true;
	else return false;
}

template<class E> inline const E Stack<E>::top()
{
	if (Stack<E>::empty())
	{
		cout << "Stack is empty" << endl;
		return NULL;
	}
	else return expression[insertion];
}

template<class E> inline void Stack<E>::push(E input)
{
	if (numElements == 20)
	{
		cout << "Stack is full. Did not add: " << input << endl;
	}
	else
	{
		numElements++;
		insertion++;
		expression[insertion] = input;
	}
}

template<class E> inline E Stack<E>::pop()
{
	if (Stack<E>::empty())
	{
		cout << "Stack is empty" << endl;
		return NULL;
	}
	else
	{
		numElements--;
		return expression[insertion--];
	}
}
