#include"SLList.h"
#include<chrono>
using namespace std::chrono;
template <typename T>
class BinarySearch
{

	// function that returns the middle node's address from the list
	Node<T>* getListMid(Node<T>* lb, Node<T>* ub); 
	
public:
	// binary search function implemented on array
	bool searchArray(T arr[], int size, T key); 
	
	// binary search funtion implemented on linked list
	bool searchLinkedList(Node<T>* head, T key); 
	
	//a function that analyze's the binary search on implemented on linked list and arrays in nanoseconds 
	void analyzeExecutionTime(string structureType, int inputSize, T key); 
																	//	
};
int main2()
{
	BinarySearch<int> bin{};
	bin.analyzeExecutionTime("list", 1000, 500);
	return 0;
}
template <typename T>
Node<T>* BinarySearch<T>::getListMid(Node<T>* lb, Node<T>* ub)
{
	if (lb == nullptr)
	{
		nullptr;
	}
	if (lb == ub)
	{
		return lb;
	}
	Node<T>* iter1 = lb, * iter2 = lb; // two pointer approach one incremented only one time other 2 times 

	while (iter2->next != ub)
	{
		iter1 = iter1->next;
		iter2 = iter2->next;
		if (iter2->next != ub) // if list does not ends move the pointer to its next 
		{
			iter2 = iter2->next;
		}
	}
	return iter1; // iter1 will end up in the middle return it 
} 

template <typename T>
bool BinarySearch<T>::searchArray(T arr[], int size, T key) //simple binary search algorithm used for arrays
{
	int lb = 0, ub = size;
	while (lb <= ub)
	{
		int mid = ((ub + lb)) / 2;
		if (arr[mid] == key)
		{
			return true;			 // if the key is found return true 
		}
		else if (arr[mid] < key) // if greater than mid move the lower bound to mid + 1
		{
			lb = mid + 1;
		}
		else // else move the upper bound to mid - 1
		{
			ub = mid - 1;
		}
	}
	return false; // return false as the key not found
}

// binary search algo may not be that efficient in the case of linked lists
template <typename T>
bool BinarySearch<T>::searchLinkedList(Node<T>* head, T key) 
{
	Node<T>* uB = nullptr;
	while (head != uB)
	{
		Node<T>* mid = getListMid(head, uB); // funtion to find the list middle node using two pointer approach
		if (mid->data == key) // if data found return true
		{
			return true;
		}
		else if (mid->data < key) // if greater than middle move the head to middle->next
		{
			head = mid->next;
		}
		else // else move the upperBound to mid
		{
			uB = mid;
		}
	}
	return false; // if the loop breaks return false as the key does not exist in the list 
}

template <typename T>
void BinarySearch<T>::analyzeExecutionTime(string structureType, int inputSize, T key)
{ 
	// if the structureType is array create an array of input size and initialize it 
	if (structureType == "array") // perform binary search on that array and provide the 
	{								// time consumed by the algorithm in nanoseconds using chrono library functions
		int* arr = new T[inputSize];
		for (int i = 0; i < inputSize; i++)
		{
			arr[i] = i + 1;
		}
		BinarySearch<int> bin{};
		time_point<high_resolution_clock> start, end;
		start = high_resolution_clock::now(); // time before noted
		bin.searchArray(arr, inputSize, key);   // function called
		end = high_resolution_clock::now();    // time after calling the function noted
		// calculate the difference and print it 
		cout << endl << fixed << "Time in nanoseconds: " << duration_cast<nanoseconds>(end - start).count() << endl;
	}
	// if the structureType is array create a linked list of input size and initialize it
	else if (structureType == "list") // perform binary search on that list and provide the 
	{								// time consumed by the algorithm in nanoseconds using chrono library functions
		SLList<T> list{};
		for (int i = 0; i < inputSize; i++)
		{
			list.addToTail(i + 1);
		}
		BinarySearch<int> bin{};
		time_point<high_resolution_clock> start, end;
		start = high_resolution_clock::now(); // time before noted
		bin.searchLinkedList(list.getHead(), key); // function called 
		end = high_resolution_clock::now(); // time after calling the function noted
		// calculate the difference and print it 
		cout << endl << fixed << "Time in nanoseconds: " << duration_cast<nanoseconds>(end - start).count() << endl;
	}
}
