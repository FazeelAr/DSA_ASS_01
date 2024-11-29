#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
struct Customer
{
	int ID;
	int orderCount;
	friend ostream& operator<<(ostream& os,const Customer& cs);
};
ostream& operator<<(ostream& os, const Customer& cs)
{
	os << cs.ID << '\t' << cs.orderCount << '\n';
	return os;
}
template<typename T>
struct Node
{
	T data;
	Node* next;
	Node(T d, Node<T>* n = nullptr)
	{
		data = d;
		next = n;
	}
};
template<typename T>
class SLList
{
	Node<T>* head;
	Node<T>* tail;
public:
	SLList();
	SLList(const SLList<T>& ref);
	~SLList();
	bool isEmpty();
	void addToHead(T e);
	void addToTail(T e);
	Node<T>*& getTail();
	Node<T>*& getHead();
	T deleteAtHead();
	T deleteAtTail();
	void display();
};
template<typename T>
SLList<T>::SLList()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
SLList<T>::SLList(const SLList<T>& ref) : SLList()
{
	if (!ref.head || !ref.tail)
	{
		return;
	}
	Node<T>* iter = ref.head;
	while (iter)
	{
		if (tail != nullptr)
		{
			tail->next = new Node<T>(iter->data);
			tail = tail->next;
		}
		else
		{
			tail = head = new Node<T>(iter->data);
		}
		iter = iter->next;
	}
}

template<typename T>
SLList<T>::~SLList()
{
	while (head)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	head = tail = nullptr;
}

template<typename T>
bool SLList<T>::isEmpty()
{
	return (head == nullptr && tail == nullptr) ? true : false;
}

template<typename T>
void SLList<T>::addToHead(T e)
{
	head = new Node<T>(e, head);
	if (tail == nullptr)
	{
		tail = head;
	}
}

template<typename T>
void SLList<T>::addToTail(T e)
{
	if (tail != nullptr)
	{
		tail->next = new Node<T>(e);
		tail = tail->next;
	}
	else
	{
		tail = head = new Node<T>(e);
	}
}

template<typename T>
Node<T>*& SLList<T>::getTail()
{
	return tail;
}

template<typename T>
Node<T>*& SLList<T>::getHead()
{
	return head;
}

template<typename T>
T SLList<T>::deleteAtHead()
{
	if (!isEmpty())
	{
		T element = head->data;
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
			return element;
		}
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		return element;
	}
	throw "\nList is empty";
}

template<typename T>
T SLList<T>::deleteAtTail()
{
	if (!isEmpty())
	{
		T element = tail->data;
		if (head == tail)
		{
			delete tail;
			tail = head = nullptr;
			return element;
		}
		Node<T>* temp = head, * iter = head;
		for (; temp->next != tail; temp = temp->next)
		{
		}
		delete tail;
		tail = temp;
		tail->next = nullptr;
		return element;
	}
	throw "\nList is Empty";
}

template<typename T>
void SLList<T>::display()
{
	cout << '\n' << ' ';
	Node<T>* iter = head;
	while (iter)
	{
		cout << iter->data << ' ';
		iter = iter->next;
	}
}

void moveToVIP(Node<Customer>*& head, Node <Customer>*& vipHead);
void removeLowOrders(Node <Customer>*& head);
int calculateTotalOrders(Node <Customer>* head);
int main1()
{
	SLList<Customer> list{};
	srand(time(0));
	//for (int i = 1; i <= 15; i++)
	{
		list.addToTail(Customer{1,1});
	}
	SLList<Customer> vipList{};
	//moveToVIP(list.getHead(), vipList.getHead());
	/*cout << "\nVIP List";
	vipList.display();*/
	cout << "\nMain List";
	list.display();
	removeLowOrders(list.getHead());
	/*cout << calculateTotalOrders(list.getHead())<<'\n';
	list.display();*/
	cout << "\nList after removal";
	list.display();
	return 0;
}
void moveToVIP(Node<Customer>*& head, Node<Customer>*& vipHead)
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->data.orderCount > 10)
	{
		vipHead = new Node < Customer >{ head->data,vipHead };
		Node<Customer>* temp = head;
		head = head->next;
		moveToVIP(head, vipHead);
		delete temp;
	}
	else
	{
		moveToVIP(head->next, vipHead);
	}
}
void removeLowOrders(Node<Customer>*& head)
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->data.orderCount < 3)
	{
		Node<Customer>* temp = head->next;
		if (head->next != nullptr)
		{
			head->data = head->next->data;
			head->next = head->next->next;
			removeLowOrders(head);
			delete temp;
		}
		else
		{
			head = nullptr;
		}
	}
	else
	{
		removeLowOrders(head->next);
	}
}
int calculateTotalOrders(Node<Customer>* head)
{
	if (head == nullptr)
		return 0;
	return head->data.orderCount + calculateTotalOrders(head->next);
}