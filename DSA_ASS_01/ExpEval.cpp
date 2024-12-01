// Stack data structure defined in this header file 
#include"Stack.h"

//converts the expression from prefix to infix first and then postfix
string prefixToPostfix(string prefix); 
//converts the expression from postfix to infix first and then prefix 
string postfixToPrefix(string postfix); 
//evaluates the infix expression but first converts the expression into postfix form ad then evaluates
int evaluateExpression(string s); 
//evaluates expression in postfix notation
int evalPostFixExp(string s);
//evaluates expression in prefix notation
int evalPreFixExp(string s);
//validates the expression depend on its notation
bool validateExpression(string expression, string notation); 
// conversion from infx to postfix
string infixToPostfix(string infix); 
// checks whether the sexpression is prefix 
bool isPrefix(string exp);
// checks whether the sexpression is postfix 
bool isPostfix(string exp);
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
// function that deals with the interface of the applicaction
void ExpressionApp();
//main funtion 


int main()
{			
	ExpressionApp();   //execution starts 
	return 0;
}
void ExpressionApp()
{
	//interface to perform different functions on expression based on user's choice
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
			if (choice <= 0 || choice > 7) // if user enters invalid choice close the application
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
	} while (choice); // runs the app until the user enters 0;
	
}
int evalPreFixExp(string s)
{
	Stack<int> exp{ (int)s.length() }; // A stack to store the operands 
	for (int i = s.length() - 1; i >= 0; i--)
	{
		int result = 0;
		if (isOperator(s[i]) || isLogicalOp(s[i])) //if the charachter is operator pop the first two charachter from stack
		{											//and push them back after performing the operation 
			if (!exp.isEmpty())
			{
				int sec = exp.pop(), first = exp.pop();
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
						throw "\nInvalid division i.e by zero"; // invalid division exception thrown
					exp.push(sec / first);
				}
				else if (s[i] == '^')
				{
					exp.push(calcPower(sec, first));   // funtion to calculate power of an operand
				}
				else if (s[i] == '%')
				{
					if (!first)
						throw "\nInvalid division i.e by zero"; // division by zero exception thrown
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
				i--;
			} while (i >= 0 && isOperand(s[i]));
			i++;
			exp.push(num);
		}
	}
	if (!exp.isEmpty())
		return exp.pop(); // return the only number left in the stack
	throw runtime_error("\nInvalid Expression");
}

int evalPostFixExp(string s)
{
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
						throw "\nInvalid division i.e by zero"; // division by zero exception thrown
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
			} while (i < s.length() && isOperand(s[i]));
			i--;
			exp.push(num);
		}
	}
	if (!exp.isEmpty())
		return exp.pop(); // return the only number left in the stack
	throw runtime_error("\nInvalid Expression");
}

bool isPrefix(string exp)   // funtion to determine whether the provided expression is infix or not
{
	int operators = 0, operands = 0;
	for (int i = exp.length() - 1; i >= 0; i--)    /// read tge string from right to left
	{
		if (isOperand(exp[i]))
		{
			do
			{
				i--;
			} while (i >= 0 && isOperand(exp[i]));  // run the loop until the final number of the operand is reached
			i++;									// operand can be comprised of multi digit number
			operands++;
		}
		else if (isOperator(exp[i]) || isLogicalOp(exp[i]))
		{
			operators++;
		}
		if (operators >= operands) // if operators greater than equal to operands returns false
		{
			return false;
		}
	}
	return (operands == operators + 1) ? true : false;   
}

bool isPostfix(string exp)
{
	int operators = 0, operands = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		if (isOperand(exp[i]))
		{
			do
			{                    // same work done as to check the prefix expression only difference is 
				i++;			// start reading the string from left to right
			} while (i < exp.length() && isOperand(exp[i]));
			i--;
			operands++;
		}
		else if (isOperator(exp[i]) || isLogicalOp(exp[i]))
		{
			operators++;
		}
		if (operands <= operators)
		{
			return false;
		}
	}
	return (operands == operators + 1) ? true : false;
}
int evaluateExpression(string s)
{
	string notation;
	if (isPrefix(s) == true)    // if the expression is prefix 
	{
		notation = "prefix";		
		if (validateExpression(s, notation)) // check the validity of the expression
		{
			return evalPreFixExp(s);    // if valid evaluate and return 
		}
		throw ("\nInvalid Expression");
	}
	else if (isPostfix(s) == true)    // if the expression is postfix 
	{
		notation = "postfix";
		if (validateExpression(s, notation))    // check the validity of the expression
		{
			return evalPostFixExp(s);          // if valid evaluate and return 
		}
		throw ("\nInvalid Expression");
	}
	else
	{
		notation = "infix";   // if not the both case
		s = infixToPostfix(s);   // convert the expression into post fix 
		if (validateExpression(s, "postfix"))       // check the validity of the expression
		{
			return evalPostFixExp(s);      // if valid evaluate and return 
		}
		throw ("\nInvalid Expression");  // else throw invlid exception
	}
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
bool validateExpression(string exp, string notation) // validates the expression depends upon the notation
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
				} while (i < exp.length() && isOperand(exp[i]));     // skip the string until the operand ends 
				i--;
				count++;
			}
			else if (isOperator(exp[i]) || isLogicalOp(exp[i]))
			{
				if (count < 2)   // if operands less than 2 return false
				{
					return false;
				}
				count--;
			}
		}
		return count == 1 ? true : false;
	}
	else if (notation == "prefix")    // do the same work for prefix but read the string from right to left
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
	if (!validateExpression(prefix, "prefix"))  // reject the expression if invalid
	{
		throw "\nInvalid Expression";
	}
	Stack<string> s{ (int)prefix.length() };
	for (int i = prefix.length() - 1; i >= 0; i--)
	{              // basically converting the expression first into infix and then postfix 
		if (isOperand(prefix[i]))
		{
			string op;
			do 
			{
				op += prefix[i];
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
	if (!validateExpression(postfix, "postfix"))   // validate the expression first 
	{
		throw "\nInvalid Expression";      // throw an exception if invalid
	}
	Stack<string> s{ (int)postfix.length() };    // stack to store the expression
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isOperand(postfix[i]))
		{
			string op;
			do                    // basically converting the expression first into infix and then postfix 
			{
				op += postfix[i] ;  // concatenate every charachter of the operand
				i++;
			} while (i >= 0 && isOperand(postfix[i]));
			i--;
			s.push(op);
		}
		else if (isOperator(postfix[i]) || isLogicalOp(postfix[i]))
		{
			string first = s.pop(), second = s.pop();     // if operator pop the first two ele
			s.push("(" + second + postfix[i] + first + ")");
		}
	}
	return infixToPrefix(s.pop());
}
bool isOperand(char op)    //checking whether the charachter is operand or not 
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
bool isOperator(char op)      //checking whether the charachter is operator or not 
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
		return 2;				 //funtion assigning precedence to different operators 
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
	string postfix; // string to store the postfix expression
	Stack<char> stk{ (int)expression.length() };  // stack to store the operands 
	for (int i = 0; i < expression.length(); i++) // run the loop untill the end of string 
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
		else if (expression[i] == '(')   // push the starting brackets into the stack
		{
			stk.push(expression[i]);
		}
		else if (expression[i] == ')') // pop the element from the stack until the starting brace arrive 
		{
			while (stk.peek() != '(')
			{
				postfix += stk.pop();
			}
			stk.pop(); // pop the starting brace as well 
		}
		else if (isOperator(expression[i]) || isLogicalOp(expression[i])) // if operator 
		{
			if ((!stk.isEmpty() && stk.peek() != '(')) //check whether the stack is empty or not and the top element is not a brace
			{
				while (!stk.isEmpty() && getPrecedence(stk.peek()) >= getPrecedence(expression[i]))
				{								// check the 
					if (stk.peek() != '(')
						postfix += stk.pop();
					else
						stk.pop();
				}
			}
			stk.push(expression[i]);
		}
	}
	while (!stk.isEmpty())   // pop the remaining elements from the stack and concatenate them into the postfix string
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
	return postfix; // return the final string 
}

string reverseExpression(string expression)
{
	int j = expression.length() - 1;
	for (int i = 0; i < expression.length(); i++)   // replacing the starting and ending braces before reversing the expression
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
		mySwap(expression[i], expression[j]);    // mySwap function used to reverse the expression
		j--;
	}
	return expression;
}
string infixToPrefix(string expression)
{
	expression = reverseExpression(expression);   /// reverse the provide expression
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
		else if (expression[i] == ')') // if the ending braces are reached pop the elements from the stack untill the strting braces are found
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
			stk.push(expression[i]);    // use the same algorithm that used in conversion of infix to postfix 
		}								// pop the operand out of the stack if the precedence is greater than the current operand
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
	return reverseExpression(prefix);   // reverse the expression again and return back
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

