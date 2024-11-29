#include<iostream>
#include<string>
using namespace std;
template<typename T>
class Stack
{
	T* data;
	int top;
	int capacity;
public:
	Stack(int cap = 0);
	~Stack();
	bool isEmpty()const;
	bool isFull()const;
	int size()const;
	void push(T val);
	T pop();
	T peek()const;
	Stack<T>& operator = (Stack<int>& ref);
};
string prefixToPostfix(string prefix);
string postfixToPrefix(string postfix);
int evaluateExpression(string expression);
bool validateExpression(string expression, string notation);
string infixToPostfix(string infix);
string infixToPrefix(string infix);
string determineExpressionType(string expression);
string reverseExpression(string expression);
bool isOperator(char op);
bool isOperand(char op);
//(Returns "Arithmetic", "Logical", or "Mixed")
int main()
{
	try
	{
		string exp{ "a+b+c-d*r" };
		cout << "initial Expression: " << exp << '\n';
		string post = infixToPostfix(exp + "-");
		cout << validateExpression(post, "postfix");
	}
	catch (const char * s)
	{
		cout << s;
	}
	/*cout << "postix Expression: " << post << '\n';
	cout << "Post To Pre: " << prefixToPostfix(post) << '\n';
	cout << "prefix: " << infixToPostfix(exp);*/
	return 0;
}
bool validateExpression(string exp, string notation)
{
	if (notation == "postfix")
	{
		string inf=
	}
}
string prefixToPostfix(string prefix)
{
	Stack<string> s{ (int)prefix.length() };
	for (int i = prefix.length() - 1; i >= 0; i--)
	{
		if (isOperand(prefix[i]))
		{
			s.push(string{ prefix[i] });
		}
		else if (isOperator(prefix[i]))
		{
			string first = s.pop(), second = s.pop();
			s.push(second + prefix[i] + first);
		}
	}
	return infixToPostfix(reverseExpression(s.pop()));
}

string postfixToPrefix(string postfix)
{
	Stack<string> s{ (int)postfix.length() };
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isOperand(postfix[i]))
		{
			s.push(string{ postfix[i] });
		}
		else if (isOperator(postfix[i]))
		{
			string first = s.pop(), second = s.pop();
			s.push(second + postfix[i] + first);
		}
	}
	return infixToPrefix(s.pop());
}
bool isOperand(char op)
{
	return ((op >= '0' && op <= '9') || (op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z')) ? true : false;
}
template<typename T>
Stack<T>::Stack(int cap)
{
	if (cap <= 0)
	{
		data = nullptr;
		capacity = 0;
		top = -1;
		return;
	}
	capacity = cap;
	top = -1;
	data = new T[capacity];
}
template<typename T>
Stack<T>::~Stack()
{
	if (!data)
	{
		return;
	}
	delete[]data;
	capacity = 0;
	top = -1;
}
template<typename T>
bool Stack<T>::isEmpty()const
{
	if (top == -1)
	{
		return true;
	}
	return false;
}
template<typename T>
bool Stack<T>::isFull()const
{
	if (top == capacity - 1)
	{
		return true;
	}
	return false;
}
template<typename T>
int Stack<T>::size()const
{
	return capacity;
}
template<typename T>
void Stack<T>::push(T val)
{
	if (!isFull())
	{
		top++;
		data[top] = val;
		return;
	}
	throw "\nStack is full:";
}
template<typename T>
T Stack<T>::pop()
{
	T val;
	if (!isEmpty())
	{
		val = data[top];
		top--;
		return val;
	}
	throw "\nStack is empty:";
}
template<typename T>
T Stack<T>::peek()const
{
	if (!isEmpty())
	{
		return data[top];
	}
	throw "\nStack is empty:";
}
template<typename T> 
Stack<T>& Stack<T>::operator = (Stack<int>& ref)
{
	if (ref.isEmpty())
	{
		return *this;
	}
	if (&ref == this)
	{
		return *this;
	}
	capacity = ref.capacity;
	data = new T[capacity];
	top = ref.top();
	for (int i = 0; i < ref.top; i++)
	{
		data[i] = ref.data[i];
	}
	return *this;
}
template<typename T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
bool isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%') ? true : false;
}
int getPrecedence(char op)
{
	switch (op)
	{
	case '-':
		return 1;
	case '+':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '%':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}
string infixToPostfix(string expression)
{
	string postfix;
	Stack<char> stk{ (int)expression.length() };
	for (int i = 0; i < expression.length(); i++)
	{
		if ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] >= 'a' && expression[i] <= 'z'))
		{
			postfix += expression[i];
		}
		else if (expression[i] == '(')
		{
			stk.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			while (stk.peek() != '(')
			{
				postfix += stk.pop();
			}
			stk.pop();
		}
		else if (isOperator(expression[i]))
		{
			if ((!stk.isEmpty() && stk.peek() != '('))
			{
				while (!stk.isEmpty() && getPrecedence(stk.peek()) >= getPrecedence(expression[i]))
				{
					if (stk.peek() != '(')
						postfix += stk.pop();
					else
						stk.pop();
				}
			}
			stk.push(expression[i]);
		}
	}
	while (!stk.isEmpty())
	{
		if (stk.peek() != '(')
		{
			postfix += stk.pop();
		}
		else
		{
			stk.pop();
		}
	}
	return postfix;
}

string reverseExpression(string expression)
{
	int j = expression.length() - 1;
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == '(')
		{
			expression[i] = ')';
		}
		else if (expression[i] == ')')
		{
			expression[i] = '(';
		}
	}
	for (int i = 0; i <= j; i++)
	{
		mySwap(expression[i], expression[j]);
		j--;
	}
	return expression;
}
string infixToPrefix(string expression)
{
	expression = reverseExpression(expression);
	string postfix;
	Stack<char> stk{ (int)expression.length() };
	for (int i = 0; i < expression.length(); i++)
	{
		if ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] >= 'a' && expression[i] <= 'z'))
		{
			postfix += expression[i];
		}
		else if (expression[i] == ')')
		{
			while (!stk.isEmpty() && stk.peek() != '(')
			{
				postfix += stk.pop();
			}
			stk.pop();
		}
		else if (expression[i] == '(')
		{
			stk.push(expression[i]);
		}
		else if (isOperator(expression[i]))
		{
			if ((!stk.isEmpty() && stk.peek() != '('))
			{
				while (!stk.isEmpty() && getPrecedence(stk.peek()) > getPrecedence(expression[i]))
				{
					if (stk.peek() != '(')
						postfix += stk.pop();
					else
						stk.pop();
				}
			}
			stk.push(expression[i]);
		}
	}
	while (!stk.isEmpty())
	{
		if (stk.peek() != '(')
		{
			postfix += stk.pop();
		}
		else
		{
			stk.pop();
		}
	}
	return reverseExpression(postfix);
}
