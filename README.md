```markdown
# Assignment 1: Data Structures and Algorithms

## Task 1: Multi-Tier Processing System

### Approach
A class named `WareHouseMS` was implemented with the following structure:

#### Private Data Members
- `Shipment :: Stack<int>`  
  (Handles shipments in the order they arrive)
- `Requests :: Queue<int>`  
  (Manages dispatch requests)
- `Dispatch :: PriorityQueue<int>`  
  (Prioritizes dispatch requests)

#### Public Member Functions
1. **`void unloadShipment(int shipmentID)`**  
   Adds a shipment to the stack.
2. **`void addDispatchRequest(int shipmentID, int priority)`**  
   Adds a dispatch request with a priority.
3. **`int processDispatch()`**  
   Processes dispatch requests based on priority.
4. **`void displaySystemState()`**  
   Displays the current state of the system.

#### Logic
- Shipments are stored in a stack.
- On a dispatch request, the shipment ID is searched in the stack. If found, it's moved to the queue and priority queue according to its priority.
- Dispatch processing removes the shipment from the priority queue and updates the request queue.

### Challenges
- Implementing appropriate data structures and their functionality.
- Developing logic for member functions while adhering to coding conventions.

### Output Example
- **Shipments IDs:**  
  `2  3  5  6  8  9  11  12  14  15`
- **Requests with Priorities:**  
  - IDs: `1, 13`  
  - Priorities: `4, 5`

This output represents the system after **5 dispatch requests** and **3 processed requests** from a total of **15 shipments**.

### Dependencies
- `Stack.h`
- `Queue.h`  
(These header files define the custom data structures.)

---

## Task 2: Recursive Rule-Based Linked List Operations

### Approach
A `Customer` ADT was defined with two attributes:
- `ID`
- `OrderCount`

A linked list was initialized with 15 customer nodes. Three global recursive functions were implemented:

#### Functions
1. **`void moveToVIP(Node*& head, Node*& vipHead)`**  
   Moves customers with orders > 10 to a VIP list. 
2. **`void removeLowOrders(Node*& head)`**  
   Removes customers with orders < 3.
3. **`int calculateTotalOrders(Node* head)`**  
   Calculates the total order count in the list.

### Challenges
- Designing recursive implementations for list operations.
- Transitioning from iterative logic to recursive logic.

### Outputs
#### Initial State
**Main List:**  
| ID   | OrderCount |  
|------|------------|  
| 1    | 11         |  
| 2    | 13         |  
| ...  | ...        |  
| 15   | 15         |

**VIP List:**  
| ID   | OrderCount |  
|------|------------|  
| 15   | 15         |  
| 10   | 15         |  
| ...  | ...        |  

**Modified Main List:**  
After removing VIP and low-order customers:  
| ID   | OrderCount |  
|------|------------|  
| 3    | 7          |  
| 4    | 4          |  

### Dependencies
- `SLList.h`

---

## Task 3: Expression Conversion, Validation, and Evaluation

### Approach
The program evaluates user-provided expressions (infix, prefix, or postfix) and converts between formats. It uses a stack for operations.  

#### Functions
1. **Conversion**  
   - `string infixToPostfix(string infix)`
   - `string infixToPrefix(string infix)`
   - `string prefixToPostfix(string prefix)`
   - `string postfixToPrefix(string postfix)`
2. **Evaluation**  
   - `int evalPostFixExp(string s)`
   - `int evalPreFixExp(string s)`
   - `int evaluateExpression(string s)`
3. **Validation**  
   - `bool validateExpression(string expression, string notation)`
4. **Utility**  
   - `string determineExpressionType(string expression)`
   - `bool isOperand(char op)`
   - `bool isOperator(char op)`

### User Interface
```plaintext
Enter 1 to convert from infix to postfix:
Enter 2 to convert from infix to prefix:
Enter 3 to convert from prefix to postfix:
Enter 4 to convert from postfix to prefix:
Enter 5 to check the validity of the expression:
Enter 6 to check the type of expression:
Enter 7 to evaluate an expression:
Enter choice:
```

### Challenges
- Handling multiple-digit numbers with delimiters (`","`).
- Validating expressions across various formats.

### Outputs
- **Input:** `1,2,+,3,99,/,2,*,-,87,6,22,&,^,+`  
  **Output:** `90`
- **Input:** `&,|,%,9,2,^,3,2`  
  **Output:** `Invalid expression`

### Dependencies
- `Stack.h`

---

## Task 4: Advanced Search with Dynamic Analysis

### Approach
A template-based binary search was implemented for both arrays and linked lists. The class structure:

#### Private Member Function
- `Node<T>* getListMid(Node<T>* lb, Node<T>* ub)`

#### Public Member Functions
1. **`bool searchArray(T arr[], int size, T key)`**  
   Performs binary search on arrays.
2. **`bool searchLinkedList(Node<T>* head, T key)`**  
   Performs binary search on linked lists.
3. **`void analyzeExecutionTime(string structureType, int inputSize, T key)`**  
   Analyzes search execution time.

### Challenges
- Implementing binary search for linked lists due to the absence of indices.  
  Complexity changes to **O(N)**.

### Outputs
#### Time Analysis
**Array:**  
| Input Size | Key | Time (ns) | Found? |  
|------------|-----|-----------|--------|  
| 100        | 34  | 700       | Yes    |  

**Linked List:**  
| Input Size | Key | Time (ns) | Found? |  
|------------|-----|-----------|--------|  
| 10000      | 1   | 475100    | Yes    |

### Dependencies
- `SLList.h`

---
```
