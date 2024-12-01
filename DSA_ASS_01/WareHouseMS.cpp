#include"Stack.h"
#include"Queue.h"
#include<ctime>
class WareHouseMS // a class to manage the ware house
{					// A multi tier processing system
	Stack<int> shipment;			// a stack to store the shipment ID's in the order they are unloaded
	Queue<int> request;				// a queue to store the dispatch requests as they are made 
	PriorityQueue dispatch;			// a priority Queue to store the dispatch requests as according to their respective priority 
public:
	void unloadShipment(int shipmentID);
	void addDispatchRequest(int shipmentID, int priority);
	int processDispatch();
	void displaySystemState();
};
int main3()
{ 
	try
	{
		WareHouseMS ms; // WMS object created 
		for (int i = 1; i <= 15; i++) // a loop to unload the shipment and their ID's pushed into the stack
		{
			ms.unloadShipment(i);
		}
		srand(time(0));
		cout << "\n\tShipment Unloaded";
		ms.displaySystemState(); // display the system state after the shiment is unloaded 
		cout << "\n";
		for (int i = 1; i <= 15; i = i + 3)
		{
			ms.addDispatchRequest(i, (rand() % 5) + 1); // a loop to make the dispatch requests and rand function to generate priorities
		}
		cout << "\n\tDispatch Requested";
		ms.displaySystemState(); // state displayed after requests 
		cout << "\n";
		for (int i = 0; i < 3; i++)
		{
			cout << '\n' << "dispatch processed: " << ms.processDispatch(); // requests processed based on priority
		}
		cout << "\n";
		cout << "\n\tAfter dispatching";  // system state dispalyed after the required shipments are dispatched
		ms.displaySystemState();
	}
	catch (...)
	{
		cout << "\nexception occured";
	}
	return 0;
}
void WareHouseMS::unloadShipment(int shipmentID)
{
	shipment.push(shipmentID); // shipments pushed into the stack
}
void WareHouseMS::addDispatchRequest(int shipmentID, int priority) 
{
	Stack<int> temp{shipment.size()}; // temporary stack to store the ID's poped 
	while (!shipment.isEmpty() && shipment.peek() != shipmentID)
	{
		temp.push(shipment.pop()); // continue the loop untill the stack is empty or the required shipment is found
	}  // pop the elements and save them in the temporary stack 
	if (shipment.peek() == shipmentID) // if the shipment is found enque it
	{
		shipment.pop();
		request.enqueue(shipmentID);     
		dispatch.insert(shipmentID, priority); // push into priority queue based on its priority
	}
	else
	{
		cout << "\nShipment not found Request cannot be made";
	}
	while (!temp.isEmpty()) // push the temp stack elements back to the main stack
	{
		shipment.push(temp.pop());
	}
}
int WareHouseMS::processDispatch() 
{
	int ship = dispatch.getHighestPriorityElement();    // pop the highest priority shipment and return it 
	dispatch.removeHighestPriorityElement();
	request.dequeue(); // dequeue the first inserted shipment
	return ship;
}
void WareHouseMS::displaySystemState()
{
	cout << "\n\tSystem State: \n";   
	if (!shipment.isEmpty()) //if the stack is not empty display it 
	{
		cout << "\nShipments: ";
		shipment.display();
	}
	if (!request.isEmpty())   //if the queue is not empty display it 
	{
		cout << "\nDispatch Requests: ";
		request.printQueue();
	}
	if (!dispatch.isEmpty())    //if the PriorityQueue is not empty display it 
	{
		cout << "\nPriority Dispatch Requests: ";
		dispatch.display();
	}
	else // if all the data structures are empty display stock ended
	{
		cout << "\nStock ended";
	}
}