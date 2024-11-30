#include"Stack.h"

//converts the expression from prefix to infix first and then postfix
string prefixToPostfix(string prefix); 

//converts the expression from postfix to infix first and then prefix 
string postfixToPrefix(string postfix); 

//evaluates the infix expression but first converts the expression into postfix form ad then evaluates
int evaluateExpression(string expression); 

//validates the expression depend on its notation
bool validateExpression(string expression, string notation); 

// conversion from infx to postfix
string infixToPostfix(string infix); 

// conversion from infx to prefix
string infixToPrefix(string infix); 

// determines the expression's Type (Returns "Arithmetic", "Logical", or "Mixed")
string determineExpressionType(string expression); 

//reverse the expression majorly used in conversion from infix to prefix and prefix to infix
string reverseExpression(string expression);

// check whether the current charachter of the expresssion is arithmetic operator or not
bool isOperator(char op);

// check whether the current charachter of the expresssion is logical operator or not
bool isLogicalOp(char op);

// check whether the current charachter of the expresssion is operand or not (1 to 9 OR a to b OR A to B)
bool isOperand(char op);

// calculates the power used for exponential operator "^"
int calcPower(int base, int exp);

int main()
{
	string exp;
	getline(cin, exp);
	//exp = infixToPrefix(exp);
	cout << postfixToPrefix(exp);
	return 0;
	int choice; //variable to ask the user for his choice
	do
	{
		try // to catch any exception occured during the execution of the application
		{
			cout << "\n\n\tExpressions: ";
			cout << "\nEnter 1 to convert from infix to postfix: ";
			cout << "\nEnter 2 to convert from infix to prefix: ";
			cout << "\nEnter 3 to convert from prefix to postfix: ";
			cout << "\nEnter 4 to convert from postfix to prefix: ";
			cout << "\nEnter 5 to check the validity of the expression";
			cout << "\nEnter 6 to check type of expression: ";
			cout << "\nEnter 7 to evaluate Expression: ";
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
			else if (choice == 6)
			{
				cout << "\nExpression Type: " << determineExpressionType(exp);
			}
			else if (choice == 7)
			{
				cout << "\nEvaluated Expression: " << evaluateExpression(exp);
			}
		}
		catch (const char* except)
		{
			cout << except;   //exception caught and displayed
		}
	} while (choice);
	
	return 0;
}
int evaluateExpression(string s)
{
	s = infixToPostfix(s); //converison from infix to postfix  
	Stack<int> exp{ (int)s.length() }; // A stack to store the operands 
	for (int i = 0; i < s.length(); i++)
	{
		int result = 0;
		if (isOperator(s[i]) || isLogicalOp(s[i])) //if the charachter is operator pop the first two charachter from stack
		{											//and push them back after performing the operation 
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
					if (!first)
						throw "\nInvalid division i.e by zero";
					exp.push(sec % first);
				}
				else if (s[i] == '&') //evaluates to true if both the operands are non zero
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
				else if (s[i] == '|') //evaluates to false if any of the operand is non zero
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
		else if (s[i] >= '0' && s[i] <= '9') // if the charachter is operand extract every digit of the number 
		{									// from the expression, convert it into a number and push it into the stack
			int num = 0;
			do
			{
				num = (num * 10) + (s[i] - '0');
				i++;
			}
			while (i<s.length()&&isOperand(s[i]));
			i--;
			exp.push(num);
		}
	}
	return exp.pop(); // return the only number left in the stack
}
bool isLogicalOp(char op) //
{
	return (op == '&' || op == '|') ? true : false;
}
string determineExpressionType(string exp)
{
	int ar, log; //counters to count logical and arithmetic expression 
	ar = log = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		if (isOperator(exp[i])) 
		{
			ar++; // if operator is arithmetic increase the count by one
		}
		else if (isLogicalOp(exp[i]))
		{
			log++; // if operator is logical increase the count by one
		}
	}
	if (ar && log) //if both counts are non zero expression is mixed 
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
				do
				{
					i++;
				} while (i < exp.length() && isOperand(exp[i]));
				i--;
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
				do
				{
					i--;
				} while (i < exp.length() && isOperand(exp[i]));
				i++;
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
	throw "\nExpression Invalid:";
}
string prefixToPostfix(string prefix)
{
	if (!validateExpression(prefix, "prefix"))
	{
		throw "\nInvalid Expression";
	}
	Stack<string> s{ (int)prefix.length() };
	for (int i = prefix.length() - 1; i >= 0; i--)
	{
		if (isOperand(prefix[i]))
		{
			string op;
			do 
			{
				op += (string{ prefix[i] });
				i--;
			} while (i >= 0 && isOperand(prefix[i]));
			i++;
			s.push(op);
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
	if (!validateExpression(postfix, "postfix"))
	{
		throw "\nInvalid Expression";
	}
	Stack<string> s{ (int)postfix.length() };
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isOperand(postfix[i]))
		{
			string op;
			do
			{
				op += (string{ postfix[i] });
				i++;
			} while (i >= 0 && isOperand(postfix[i]));
			i--;
			s.push(op);
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
		if (isOperand(expression[i])||expression[i]==',')
		{
			do
			{
				postfix += expression[i];
				i++;
			} while (i < expression.length() && isOperand(expression[i]));
			i--;
			postfix += ",";
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
	string prefix;
	Stack<char> stk{ (int)expression.length() };
	for (int i = 0; i < expression.length(); i++)
	{
		if (isOperand(expression[i]) || expression[i] == ',')
		{
			do
			{
				prefix += expression[i];
				i++;
			} while (i < expression.length() && isOperand(expression[i]));
			i--;
			prefix += ",";
		}
		else if (expression[i] == ')')
		{
			while (!stk.isEmpty() && stk.peek() != '(')
			{
				prefix += stk.pop();
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
						prefix += stk.pop();
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
			prefix += stk.pop();
		}
		else
		{
			stk.pop();
		}
	}
	return reverseExpression(prefix);
}
int calcPower(int base, int exp)
{
	int res = 1;
	while (exp)
	{
		res = res * base;
		exp--;
	}
	return res;
}

