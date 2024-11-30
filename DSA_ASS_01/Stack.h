#ifndef STACK_H
#define STACK_H
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
		exp--;
	}
	return res;
}
#endif // !STACK_H
