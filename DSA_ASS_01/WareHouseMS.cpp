#include"Stack.h"
#include"Queue.h"
class WareHouseMS
{
	Stack<int> shipment;
	Queue<int> request;
	PriorityQueue dispatch;
public:
	void unloadShipment(int shipmentID);
	void addDispatchRequest(int shipmentID, int priority);
	int processDispatch();
	void displaySystemState();
};
int main1()
{
	/*Stack<int> st;
	for (int i = 0; i < 5; i++)
	{
		st.push(i);
	}
	while (!st.isEmpty())
		cout << st.pop() << ' ';
	return 0;*/
	WareHouseMS ms;
	for (int i = 1; i <= 15; i++)
	{
		ms.unloadShipment(i);
	}
	cout << "\nShipment Unloaded";
	ms.displaySystemState();
	for (int i = 1; i <= 15; i = i + 3)
	{
		ms.addDispatchRequest(i, ceil(i / 3));
		//ms.displaySystemState();
	}
	cout << "\nDispatch Requested";
	ms.displaySystemState();
	for (int i = 0; i < 3; i++)
	{
		cout <<'\n' << ms.processDispatch();
	}
	cout << "\nAfter dispatching";
	ms.displaySystemState();
	return 0;
}
void WareHouseMS::unloadShipment(int shipmentID)
{
	shipment.push(shipmentID);
}
void WareHouseMS::addDispatchRequest(int shipmentID, int priority) 
{
	Stack<int> temp{shipment.size()};
	while (!shipment.isEmpty() && shipment.peek() != shipmentID)
	{
		temp.push(shipment.pop());
	}
	if (shipment.peek() == shipmentID)
	{
		shipment.pop();
		request.enqueue(shipmentID);
		dispatch.insert(shipmentID, priority);
	}
	else
	{
		cout << "\nShipment not found Request cannot be made";
	}
	while (!temp.isEmpty())
	{
		shipment.push(temp.pop());
	}
}
int WareHouseMS::processDispatch() 
{
	int ship = dispatch.getHighestPriorityElement();
	dispatch.removeHighestPriorityElement();
	return ship;
}
void WareHouseMS::displaySystemState()
{
	if (!shipment.isEmpty())
	{
		cout << "\nShipments: ";
		shipment.display();
	}
	if (!request.isEmpty())
	{
		cout << "\nDispatch Requests: ";
		request.printQueue();
	}
	if (!dispatch.isEmpty())
	{
		cout << "\nPriority Dispatch Requests: ";
		dispatch.display();
	}
}