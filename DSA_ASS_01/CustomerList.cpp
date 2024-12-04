#include<iostream>
#include<ctime>
#include"SLList.h"
using namespace std;
struct Customer // customer ADT to hold customer information
{
	int ID;
	int orderCount;
	// friend function (ostream operator overloaded) to print the customer's data
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
	SLList<Customer> list{}; //SLList object of customer type created 
	srand(time(0));
	for (int i = 1; i <= 15; i++) // initialized the list with 15 customers and
	{
		list.addToTail(Customer{ i,(rand() % 15 + 1) });
	}
	cout << "\nMain List";
	cout << "\nID's   OrderCount";
	list.display(); //display  the list after adding the nodes
	SLList<Customer> vipList{};
	moveToVIP(list.getHead(), vipList.getHead());    //customers with the orders greater than 10 removed from the list and moved to VIP list
	removeLowOrders(list.getHead());     //customers with the orders less than 3 removed from the list
	cout << "\nVIP List: ";   
	cout << "\nID's   OrderCount";
	vipList.display();    
	cout << "\nMain List after removal of low orders and Vip Customers";
	cout << "\nID's   OrderCount";
	list.display();      //display the list after less order removal and vip customer's removal
	return 0;
}
void moveToVIP(Node<Customer>*& head, Node<Customer>*& vipHead)
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->data.orderCount > 10) // if the orders are greter than 10 remove the node from the list
	{
		vipHead = new Node < Customer >{ head->data,vipHead };
		Node<Customer>* temp = head; // add the new node in the vip list  
		head = head->next; // move the head to the next node
		moveToVIP(head, vipHead);  // call the function again 
		delete temp; // delete the node head
	}
	else
	{
		moveToVIP(head->next, vipHead); // move the head to the next nide and call the function again
	}
}
void removeLowOrders(Node<Customer>*& head)
{
	if (head == nullptr) // if the list ends return;
	{
		return;
	}
	else if (head->data.orderCount < 3)
	{
		Node<Customer>* temp = head;    // if the orders are  less than 2 delete the node 
		head = head->next;
		removeLowOrders(head);
		delete temp;
	}
	else
	{
		removeLowOrders(head->next); //else move the head to the next
	}
}

//count the total numbers of orders placed by the customers
int calculateTotalOrders(Node<Customer>* head)
{
	if (head == nullptr)
		return 0;
	return head->data.orderCount + calculateTotalOrders(head->next);
}