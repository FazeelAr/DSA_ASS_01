#include<iostream>
#include<ctime>
#include"SLList.h"
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
void moveToVIP(Node<Customer>*& head, Node <Customer>*& vipHead);
void removeLowOrders(Node <Customer>*& head);
int calculateTotalOrders(Node <Customer>* head);
int main()
{
	SLList<Customer> list{};
	srand(time(0));
	for (int i = 1; i <= 15; i++)
	{
		list.addToTail(Customer{ i,(rand() % 15 + 1) });
	}
	cout << "\nMain List";
	list.display();
	SLList<Customer> vipList{};
	moveToVIP(list.getHead(), vipList.getHead());
	removeLowOrders(list.getHead());
	cout << "\nVIP List: ";
	vipList.display();
	cout << "\nMain List after removal of low orders and Vip Customers";
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
		Node<Customer>* temp = head;
		head = head->next;
		removeLowOrders(head);
		delete temp;
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