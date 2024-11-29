#include"SLList.h"
#include<chrono>
using namespace std::chrono;
void main1()
{
	const int N = 100;
	int arr[N];
	int i = 0;
	for (int j = N - 1; j >= 0; j--)
	{
		arr[i] = j;
		i++;
	}
	long double sum = 0;
	for (int i = 0; i < 10; i++)
	{
		time_point<high_resolution_clock> start, end;
		start = high_resolution_clock::now();
		end = high_resolution_clock::now();
		cout << endl << fixed << duration_cast<nanoseconds>(end - start).count() << endl;
		sum = sum + duration_cast<nanoseconds>(end - start).count();
	}

	//cout << "Average: " << sum / 10 << endl;
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << ' ';
	}

}
template <typename T>
class BinarySearch
{
	
public:
	Node<T>* getListMid(Node<T>* lb, Node<T>* ub)
	{
		if (lb == nullptr)
		{
			nullptr;
		}
		if (lb == ub)
		{
			return lb;
		}
		Node<T>* iter1 = lb, *iter2 = lb;
		while (iter2->next != ub)
		{
			iter1 = iter1->next;
			iter2 = iter2->next;
			if (iter2->next != ub)
			{
				iter2 = iter2->next;
			}
		}
		return iter1;
	}
	bool searchArray(T arr[], int size, T key)
	{
		int lb = 0, ub = size;
		while (lb <= ub)
		{
			int mid = ((ub + lb)) / 2;
			if (arr[mid] == key)
			{
				return true;
			}
			else if (arr[mid] < key)
			{
				lb = mid + 1;
			}
			else
			{
				ub = mid - 1;
			}
		}
		return false;
	}
	Node<T>* findUppB(Node<T>* head)
	{
		if (!head)
		{
			return nullptr;
		}
		while (head->next != nullptr)
		{
			head = head->next;
		}
		return head;
	}
	bool searchLinkedList(Node<T>* head, T key)
	{
		Node<T>* uB = nullptr;
		while (head != uB)
		{
			Node<T>* mid = getListMid(head, uB);
			if (mid->data == key)
			{
				return true;
			}
			else if (mid->data < key)
			{
				head = mid->next;
			}
			else
			{
				uB = mid;
			}
		}
		return false;
	}
	void analyzeExecutionTime(string structureType, int inputSize, T key) 
	{
		if (structureType == "array")
		{
			int* arr = new T[inputSize];
			for (int i = 0; i < inputSize; i++)
			{
				arr[i] = i + 1;
			}
			BinarySearch<int> bin{};
			time_point<high_resolution_clock> start, end;
			start = high_resolution_clock::now();
			bin.searchArray(arr, inputSize, key);
			end = high_resolution_clock::now();
			cout << endl << fixed << "Time in nanoseconds: " << duration_cast<nanoseconds>(end - start).count() << endl;
		}
		else if (structureType == "list")
		{
			SLList<T> list{};
			for (int i = 0; i < inputSize; i++)
			{
				list.addToTail(i + 1);
			}
			BinarySearch<int> bin{};
			time_point<high_resolution_clock> start, end;
			start = high_resolution_clock::now();
			bin.searchLinkedList(list.getHead(), key);
			end = high_resolution_clock::now();
			cout << endl << fixed << "Time in nanoseconds: " << duration_cast<nanoseconds>(end - start).count() << endl;
		}
	}
};
int main4()
{
	BinarySearch<int> bin{};
	bin.analyzeExecutionTime("list", 1000, 500);
	return 0;
}
