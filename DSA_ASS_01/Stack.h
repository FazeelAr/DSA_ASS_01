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
	void display();
	void reSize(int size);
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
	if (isFull())
	{
		reSize(capacity + 1);
	}
	top++;
	data[top] = val;
	return;
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
void Stack<T>::reSize(int newSize)
{
	if (newSize <= 0)
	{
		return;
	}
	T* temp = new T[newSize];
	int i = 0;
	while (i < newSize && i < capacity)
	{
		temp[i] = data[i];
		i++;
	}
	capacity = newSize;
	delete data;
	data = temp;
}
template<typename T>
void Stack<T>::display()
{
	cout << '\n';
	for (int i = 0; i <= top; i++)
	{
		cout << data[i] << ' ';
	}
}
#endif // !STACK_H
