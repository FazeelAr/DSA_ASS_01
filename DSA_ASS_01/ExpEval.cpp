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
//(Returns "Arithmetic", "Logical", or "Mixed")
string reverseExpression(string expression);
long long int conToInt(string s);
bool isOperator(char op);
bool isLogicalOp(char op);
bool isOperand(char op);
int calcPower(int base, int exp);
int main()
{
	
	try
	{
		string exp;
		getline(cin, exp);
		cout << evaluateExpression(exp);
		return 0;
		int choice;
		do
		{
			cout << "\n\n\tExpressions: ";
			cout << "\nEnter 1 to convert from infix to postfix: ";
			cout << "\nEnter 2 to convert from infix to prefix: ";
			cout << "\nEnter 3 to convert from prefix to postfix: ";
			cout << "\nEnter 4 to convert from postfix to prefix: ";
			cout << "\nEnter 5 to check the validity of the expression";
			cout << "\nEnter 6 to check type of expression: ";
			cout << "\nEnter choice: ";
			cin >> choice;
			if (choice <= 0 || choice > 7) 
			{
				break;
			}
			string exp;
			cin.ignore();
			cout << "Enter expression: ";
			getline(cin, exp);
			cout << "\nInitial Expression: " << exp;
			if (choice == 1)
			{
				cout << "\nPostfix Expression: " << infixToPostfix(exp);
			}
			else if (choice == 2)
			{
				cout << "\nPrefix Expression: " << infixToPrefix(exp);
			}
			else if (choice == 3)
			{
				cout << "\nPostfix Expression: " << prefixToPostfix(exp);
			}
			else if (choice == 4)
			{
				cout << "\nPrefix Expression: " << postfixToPrefix(exp);
			}
			else if (choice == 5)
			{
				cout << "\nEnter 1 for Prefix notation: ";
				cout << "\nEnter 2 for Postfix notation: ";
				int notation;
				cin >> notation;
				if (notation == 1)
				{
					cout << "\n" << boolalpha << validateExpression(exp, "prefix");
				}
				else if (notation == 2)
				{
					cout << "\n" << boolalpha << validateExpression(exp, "postfix");
				}
			}
			else if (choice == 5)
			{
				cout << "\nExpression Type: " << determineExpressionType(exp);
			}
		} while (choice);
	}
	catch (const char * except)
	{
		cout << except;
	}
	return 0;
}
int evaluateExpression(string s)
{
	s = infixToPostfix(s);
	Stack<int> exp{ (int)s.size() };
	for (int i = 0; i < s.size(); i++)
	{
		int result = 0;
		if (isOperator(s[i]) || isLogicalOp(s[i]))
		{
			if (!exp.isEmpty())
			{
				int first = exp.pop(), sec = exp.pop();
				if (s[i] == '+')
				{
					exp.push(sec + first);
				}
				else if (s[i] == '-')
				{
					exp.push(sec - first);
				}
				else if (s[i] == '*')
				{
					exp.push(sec * first);
				}
				else if (s[i] == '/')
				{
					if (!first)
						throw "\nInvalid division i.e by zero";
					exp.push(sec / first);
				}
				else if (s[i] == '^')
				{
					exp.push(calcPower(sec, first));
				}
				else if (s[i] == '%')
				{
					exp.push(sec % first);
				}
				else if (s[i] == '&')
				{
					if (first != 0 && sec != 0)
					{
						exp.push(1);
					}
					else
					{
						exp.push(0);
					}
				}
				else if (s[i] == '|')
				{
					if (first != 0 || sec != 0)
					{
						exp.push(1);
					}
					else
					{
						exp.push(0);
					}
				}
			}
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			int num = 0;
			while(i < s.length() && s[i] != ',')
			{
				num = (num * 10) + (s[i] - '0');
				i++;
			}
			i--;
			cout << num << ' ';
			exp.push(num);
		}
	}
	return exp.pop();
}
bool isLogicalOp(char op)
{
	return (op == '&' || op == '|') ? true : false;
}
string determineExpressionType(string exp)
{
	int ar, log;
	ar = log = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		if (isOperator(exp[i]))
		{
			ar++;
		}
		else if (isLogicalOp(exp[i]))
		{
			log++;
		}
	}
	if (ar && log)
	{
		return "Mixed";
	}
	else if (ar)
	{
		return "Arithmetic";
	}
	else if (log)
	{
		return "Logical";
	}
}
bool validateExpression(string exp, string notation)
{
	if (notation == "postfix")
	{
		int count = 0;
		for (int i = 0; i < exp.length(); i++)
		{
			if (isOperand(exp[i]))
			{
				count++;
			}
			else if (isOperator(exp[i]) || isLogicalOp(exp[i]))
			{
				if (count < 2)
				{
					return false;
				}
				count--;
			}
		}
		return count == 1 ? true : false;
	}
	else if (notation == "prefix")
	{
		int count=0;
		for (int i = exp.length(); i >= 0; i--)
		{
			if (isOperand(exp[i]))
			{
				count++;
			}
			else if (isOperator(exp[i]) || isLogicalOp(exp[i]))
			{
				if (count < 2)
				{
					return false;
				}
				count--;
			}
		}
		return (count == 1) ? true : false;
	}
	throw "\nWrong Notation";
}
string prefixToPostfix(string prefix)
{
	if (!validateExpression(prefix, "prefix"));
	{
		throw "\nInvalid Expression";
	}
	Stack<string> s{ (int)prefix.length() };
	for (int i = prefix.length() - 1; i >= 0; i--)
	{
		if (isOperand(prefix[i]))
		{
			s.push(string{ prefix[i] });
		}
		else if (isOperator(prefix[i]) || isLogicalOp(prefix[i]))
		{
			string first = s.pop(), second = s.pop();
			s.push("(" + second + prefix[i] + first + ")");
		}
	}
	string infix = reverseExpression(s.pop());
	return infixToPostfix(infix);
}

string postfixToPrefix(string postfix)
{
	if (!validateExpression(postfix, "postfix"));
	{
		throw "\nInvalid Expression";
	}
	Stack<string> s{ (int)postfix.length() };
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isOperand(postfix[i]))
		{
			s.push(string{ postfix[i] });
		}
		else if (isOperator(postfix[i]) || isLogicalOp(postfix[i]))
		{
			string first = s.pop(), second = s.pop();
			s.push("(" + second + postfix[i] + first + ")");
		}
	}
	return infixToPrefix(s.pop());
}
bool isOperand(char op)
{
	return ((op >= '0' && op <= '9') || (op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z')) ? true : false;
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
	case '|':
		return 4;
	case '&':
		return 5;
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
		if (isOperand(expression[i]))
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
		else if (isOperator(expression[i]) || isLogicalOp(expression[i]))
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
		if (isOperand(expression[i]))
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
		else if (isOperator(expression[i]) || isLogicalOp(expression[i]))
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
int calcPower(int base, int exp)
{
	int res = 1;
	while (exp)
	{
		res = res * base;
	}
	return res;
}