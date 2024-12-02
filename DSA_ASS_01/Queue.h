#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
template<typename T>
class Queue
{
	T* data;
	int size;
	int front;
	int rear;
	int noOfElements;
	void reSize(int newSize);
public:
	Queue(int s = 0);
	int getSize()const;
	bool isEmpty()const;
	bool isFull()const;
	T showFront()const;
	T showRear()const;
	void enqueue(T element);
	T dequeue();
	T shiftedDequeue();
	void printQueue();
	int getNoOfElements()const;
	~Queue();
};
template<typename T>
void Queue<T>::reSize(int newSize)
{
	if (newSize <= 0)
	{
		return;
	}
	T* temp = new T[newSize];
	int i = 0;
	while (i < newSize && i < size)
	{
		temp[i] = data[i];
		i++;
	}
	if (data)
		delete[]data;
	data = temp;
	size = newSize;
}
template<typename T>
int Queue<T>::getNoOfElements()const
{
	return noOfElements;
}
template<typename T>
int Queue<T>::getSize()const
{
	return size;
}
template<typename T>
Queue<T>::Queue(int s)
{
	if (s <= 0)
	{
		data = nullptr;
		size = 0;
		rear = front = -1;
		noOfElements = 0;
		return;
	}
	size = s;
	data = new T[size];
	rear = front = -1;
	noOfElements = 0;
}
template<typename T>
bool Queue<T>::isEmpty()const
{
	return (front == -1) ? true : false;
}
template<typename T>
bool Queue<T>::isFull()const
{
	return (noOfElements == size) ? true : false;
}
template<typename T>
T Queue<T>::showFront()const
{
	if (!isEmpty())
	{
		T element = data[front % size];
		return element;
	}
	else
	{
		throw runtime_error("\nQueue is empty:");
	}
}
template<typename T>
T Queue<T>::showRear()const
{
	if (!isEmpty())
	{
		rear = rear % size;
		T element = data[rear];
		return element;
	}
	else
	{
		throw "\nQueue is empty:";
	}
}
template<typename T>
void Queue<T>::enqueue(T element)
{
	if (isFull())
	{
		reSize(size + 1);
	}
	rear = (rear + 1) % size;;
	data[rear] = element;
	if (front == -1)
	{
		front = 0;
	}
	noOfElements++;
}
template<typename T>
T Queue<T>::dequeue()
{
	if (!isEmpty())
	{
		front = front % size;
		T element = data[front];
		if (front == rear)
		{
			front = rear = -1;
		}
		else
		{
			front++;
		}
		noOfElements--;
		return element;
	}
	else
	{
		throw "\nQueue is Empty:";
	}
}
template<typename T>
T Queue<T>::shiftedDequeue()
{
	if (!isEmpty())
	{
		T element = data[front];
		for (int i = 0; i < rear; i++)
		{
			data[i] = data[i + 1];
		}
		rear--;
		if (front == rear)
		{
			front = rear = -1;
		}
		return element;
	}
	else
	{
		throw "\nQueue is Empty:";
	}

}
template<typename T>
void Queue<T>::printQueue()
{
	cout << '\n';
	for (int i = front; i <= rear; i++)
	{
		cout << setw(3) << left << data[i] << ' ';
	}
}
template<typename T>
Queue<T>::~Queue()
{
	if (!data)
	{
		return;
	}
	delete[]data;
	size = 0;
	rear = -1;
	front = -1;
}

class PriorityQueue 
{
private:
	vector<pair<int, int>> queue;

	int findHighestPriorityIndex() const 
	{
		if (queue.empty())
			return -1;

		int highestPriorityIndex = 0;
		for (int i = 1; i < queue.size(); i++) 
		{
			if (queue[i].second < queue[highestPriorityIndex].second ||
				(queue[i].second == queue[highestPriorityIndex].second && i < highestPriorityIndex)) {
				highestPriorityIndex = i;
			}
		}
		return highestPriorityIndex;
	}

public:
	void insert(int element, int priority) 
	{
		queue.push_back({ element, priority });
	}

	int getHighestPriorityElement() const 
	{
		if (isEmpty()) 
		{
			throw runtime_error("Priority Queue is empty.");
		}
		int index = findHighestPriorityIndex();
		return queue[index].first;
	}

	void removeHighestPriorityElement() 
	{
		if (isEmpty()) {
			throw runtime_error("Priority Queue is empty.");
		}
		int index = findHighestPriorityIndex();
		queue.erase(queue.begin() + index);
	}

	bool isEmpty() const 
	{
		return queue.empty();
	}

	void display()
	{
		cout << setw(9) << "\nID's" << ": ";
		for (int i = 0; i < queue.size(); i++)
		{
			cout << setw(3) << left << queue[i].first << ' ';
		}
		cout << "\nPriority: ";
		for (int i = 0; i < queue.size(); i++)
		{
			cout << setw(3) << left << queue[i].second << ' ';
		}
	}
	
	int size()
	{
		return queue.size();
	}
};
#endif // !QUEUE_H
