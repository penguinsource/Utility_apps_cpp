
#include <cassert>
using namespace std;
template <typename T> 
class ListStack 
{
public:

  // constructor
  ListStack();
  
  // destructor
  ~ListStack();

  // copy constructor
  ListStack(const ListStack &value);

  // assignment operator
  ListStack& operator= (const ListStack &value){
	while(!empty()){				// while not empty, pop element
		pop();
	}
	
	ListStack<T> a;					// create new list
	Node *point = value.head;		// get a pointer to head of new list
	
	while (point != NULL){			// push on new list each node
		a.push(point->data);
		point = point->next;
	}	
	
	Node *second = a.head;			// do the same thing so that the list
	while (second != NULL){			// reverse its order, thus returning the 
		push(second->data);			// list in the correct order
		second = second->next;
	}

	return *this;
	
  }
 
  void push(const T &value);   // add an element at the top of the stack
  void pop();            // remove top element (pre-cond: !empty)
  bool empty() const;    // true iff no element present
  int size() const;      // return current number of elements
  T& top();              // return reference to top element (pre-cond: !empty)
  const T& top() const;  // return reference to top element in const context
                         // (pre-cond: !empty)
	
private:
	// node class
	class Node {
	public:
		Node(const T& arg) : data(arg) {
			next = NULL;
		}
		T data;
		Node *next;
	};
	
  Node *head;            // pointer to head node of linked list
  int n;                 // number of elements
};

// constructor
template <typename T>
ListStack<T>::ListStack() {
	head = NULL;							// set the head to NULL (no nodes)
	this->n = 0;							// set n to 0
}

// destructor
template <typename T>
ListStack<T>::~ListStack() {
	while(!empty()){						// until list is empty, pop node
		pop();
	}
}

// copy constructor
template <typename T>
ListStack<T>::ListStack(const ListStack &value) {
	head = NULL;
	n = 0;
	Node *ha = value.head;
	
	ListStack<T> a;							// create new list
	while (ha != NULL){						// push data on it
		a.push(ha->data);
		ha = ha->next;
	}
	
	Node *second = a.head;					// push data from the new list
	while (second != NULL){					// this will reverse the list's order
		push(second->data);
		second = second->next;
	}

}
	
// push a node down on list
template<typename T>
void ListStack<T>::push(const T &value){
	Node *nodePointer = new Node(value);	// create Node
	nodePointer->data = value;				// set Data to value
	nodePointer->next = head;				// make connections
	head = nodePointer;
	n++;									// increase n
}

// pop a node from list
template<typename T>
void ListStack<T>::pop(){
	assert(!empty());						// assert that list is not empty
	Node *pointerToDelete = head;			// make connections
	head = head->next;
	delete pointerToDelete;					// delete node
	n--;									// decrease count
}
template<typename T>
int ListStack<T>::size() const {
	return n;								// return size
}

template <typename T>
bool ListStack<T>::empty() const {
	if (n == 0){							// return true if list is empty
		return true;
	}
	return false;
}

template <typename T>
T& ListStack<T>::top() {
	assert(!empty());						// assert that list is not empty
	return head->data;						// return data from top of list
}

template <typename T>
const T& ListStack<T>::top() const {
	assert(!empty());						// assert that list is not empty
	return head->data;						// return const data from top of list
}
