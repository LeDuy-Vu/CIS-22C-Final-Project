#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <cstddef> //for NULL

#ifndef assert
#include <assert.h>
#endif

using namespace std;

template <class T>
class List
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node *previous;

		Node (const T &newData)
		{
			data = newData;
			next = previous = NULL;
		}
	};

	Node *start;
	Node *stop;
	Node *iterator;
	int length;

	int binarySearch (int low, int high, T c) const;
	//Recursively searchs the list by dividing the search space in half
	//Returns the index of the element, if it is found in the list
	//Returns -1 if the element is not in the list
	//Postcondition: The iterator location has not been changed

public:

	/**Constructors and Destructors*/

	List ();
	//Default constructor: Initializes an empty list
	//Postcondition: An empty list created

	List (const List &list);
	//Copy constructor: Makes a deep copy of list
	//Postcondition: A new list created as a copy of the original list

	List& operator = (const List &list);
	//Assignment: Makes a deep copy of list

	~List ();
	//Destructor: Frees memory allocated to the list
	//Postcondition: Delete the list and free allocated memory

	/**Accessors*/

	T getStart () const;
	//Returns the data at the start of the list
	//Precondition: The list is not empty

	T getStop () const;
	//Returns the data at the end of the list
	//Precondition: The list is not empty

	bool isEmpty () const;
	//Determines whether a list is empty

	int getLength () const;
	//Returns the size of the list

	T getIterator () const;
	//Returns the data that the iterator currently points to
	//Precondition: Iterator isn't NULL

	bool offEnd () const;
	//Determines whether the iterator is NULL or not

	bool operator==(const List &list) const;
	//Tests two lists to determine whether their contents are equal
	//Postcondition: Returns true if lists are equal and false otherwise

	int getIndex () const;
	//Indicates the index of the Node where the iterator is currently pointing
	//Nodes are numbered starting at 1 through the size of the list
	//Precondition: !offEnd()

	int linearSearch (T c) const;
	//Iteratively searchs the list, element by element, from the start of the list to the end of the list
	//Returns the index of the element, if it is found in the list
	//Does not call the indexing functions in the implementation
	//Returns -1 if the element is not in the List
	//Precondition: length != 0
	//Postcondition: The iterator location has not been changed

	int binarySearch (T c) const;
	//Returns the index where data is located in the list
	//Calls the private helper function binarySearch to perform the search
	//Precondition: length != 0
	//Precondition: List is sorted (must test on a sorted list)
	//Postcondition: The iterator location has not been changed

	/**Manipulation Procedures*/

	void removeStart ();
	//Removes the value stored in first node in the list
	//Precondition: The list is not empty
	//Postcondition: First node of the list removed

	void removeStop ();
	//Removes the value stored in the last node in the list
	//Precondition: The list is not empty
	//Postcondition: Last node of the list removed

	void insertStart (T data);
	//Inserts a new data at the beginning of the list
	//If the list is empty, the new data becomes both start and stop
	//Postcondition: A new node has been added at the beginning of the list

	void insertStop (T data);
	//Inserts a new data at the end of the list
	//If the list is empty, the new data becomes both start and stop
	//Postcondition: A new node has been added at the end of the list

	void startIterator ();
	//Moves the iterator to the start of the list
	//Precondition: The list is not empty
	//Postcondition: Iterator moved to the start of the list

	void removeIterator ();
	//Removes the element currently pointed to by the iterator
	//Precondition: Iterator is not NULL
	//Postcondition: Iterator then points to NULL

	void insertIterator (T data);
	//Inserts a new data after the node currently pointed to by the iterator
	//Precondition: Iterator isn't NULL
	//Postcondition: A new data inserted after the node currently pointed to by the iterator

	void moveIterNext ();
	//Moves the iterator up by one node towards stop
	//Precondition: Iterator isn't NULL
	//Postcondition: Iterator shifted by one node towards stop

	void moveIterPrevious ();
	//Moves the iterator down by one node towards start
	//Precondition: Iterator isn't NULL
	//Postcondition: Iterator shifted by one node towards start

	void moveToIndex (int index);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Nodes are numbered starting at 1 through the size of the list
	//Precondition: length != 0
	//Precondition: index <= length

	/**Additional List Operations*/

	void displayList (ostream &out) const;
	//Prints to the console or a file the value of each data in the list sequentially
	//and separated by a blank space
	//Prints nothing if the list is empty
	//Prints a empty newline character if it's empty

	void displayNumberedList (ostream &out) const;
	//Prints to the console or a file the value of each data in the list sequentially
	//by numbered format followed by a new line
	//Prints nothing if the list is empty
};


// Implementation file for List class

//Private functions

/*======================================================================================================*
* The private binarySearch function recursively searchs the list by dividing the search space in half. *
* It returns the index of the desired element if it is found in the list, -1 otherwise.				*
*======================================================================================================*/
template<class T>
int List<T>::binarySearch (int low, int high, T c) const
{
	if (high < low)
		return -1;

	int mid = (low + high) / 2;
	Node *ptr = start;
	int index = 1;

	while (index != mid)
	{
		ptr = ptr->next;
		index++;
	}

	if (c == ptr->data)
		return mid;
	else if (c > ptr->data)
		return binarySearch (mid + 1, high, c);
	else
		return binarySearch (low, mid - 1, c);
}

//Public functions

/*======================================*
* Constructor                          *
* This function creates an empty list. *
*======================================*/
template <class T>
List<T>::List ()
{
	start = stop = iterator = NULL;
	length = 0;
}


//Assignment: Makes a deep copy of list
template <class T>
List<T>& List<T>::operator = (const List &list)
{
	if (!list.start)
		start = stop = iterator = NULL;
	else
	{
		start = new Node (list.start->data);
		Node *temp = list.start;
		iterator = start;

		while (temp->next)
		{
			temp = temp->next;
			iterator->next = new Node (temp->data);
			iterator->next->previous = iterator;
			iterator = iterator->next;
		}

		stop = iterator;
		iterator = NULL;
	}

	length = list.length;
	return *this;
}


/*====================================================================================*
* Copy constructor                                              					  *
* This function allocates and initializes a new list as a copy of the original list. *
*====================================================================================*/
template <class T>
List<T>::List (const List &list)
{
	*this = list;	// overloaded =
}

/*===============================================*
* Destructor                                  	 *
* This function deletes every node in the list. *
*===============================================*/
template <class T>
List<T>::~List ()
{
	Node *cur = start;
	Node *aft;

	while (cur)
	{
		aft = cur->next;
		delete cur;
		cur = aft;
	}
}

/*===========================================================*
* The getStart function returns the first data of the list. *
*===========================================================*/
template <class T>
T List<T>::getStart () const
{
	assert (!isEmpty ());
	return start->data;
}

/*=========================================================*
* The getStop function returns the last data of the list. *
*=========================================================*/
template <class T>
T List<T>::getStop () const
{
	assert (!isEmpty ());
	return stop->data;
}

/*==========================================================================*
* The isEmpty function returns true if the list is empty, false otherwise. *
*==========================================================================*/
template <class T>
bool List<T>::isEmpty () const
{
	return length == 0;
}

/*======================================================*
* The getLength function returns the size of the list. *
*======================================================*/
template <class T>
int List<T>::getLength () const
{
	return length;
}

/*=====================================================================*
* The getIterator function returns the data which iterator points to. *
*=====================================================================*/
template <class T>
T List<T>::getIterator () const
{
	assert (!offEnd ());
	return iterator->data;
}

/*============================================================================*
* The offEnd function returns true if the iterator is NULL, false otherwise. *
*============================================================================*/
template <class T>
bool List<T>::offEnd () const
{
	if (iterator)
		return false;
	return true;
}

/*==============================================================================*
* The overloaded operator == returns true if lists are equal, false otherwise. *
*==============================================================================*/
template <class T>
bool List<T>::operator==(const List &list) const
{
	if (length != list.length)
		return false;

	Node *left = start;
	Node *right = list.start;

	while (left)
	{
		if (left->data != right->data)
			return false;
		left = left->next;
		right = right->next;
	}

	return true;
}

/*===============================================================================================*
* The getIndex function returns the index of the node where the iterator is currently pointing. *
*===============================================================================================*/
template <class T>
int List<T>::getIndex () const
{
	assert (!offEnd ());

	int index = 1;
	Node *curr = start;

	while (curr != iterator)
	{
		curr = curr->next;
		index++;
	}

	return index;
}

/*=============================================================================================*
* The linearSearch function uses linear method to search for the desired element in the list. *
* It returns the index of the element if it is found in the list, -1 otherwise.			   *
*=============================================================================================*/
template <class T>
int List<T>::linearSearch (T c) const
{
	assert (!isEmpty ());
	Node *ptr = start;
	int index = 1;

	while (ptr)
	{
		if (c == ptr->data)
			return index;
		ptr = ptr->next;
		index++;
	}

	return -1;
}

/*================================================================================================================*
* The public binarySearch function uses binary method to recursively search for the desired element in the list. *
* It returns the index of the element if it is found in the list, -1 otherwise.								  *
*================================================================================================================*/
template <class T>
int List<T>::binarySearch (T c) const
{
	assert (!isEmpty ());
	return binarySearch (1, length, c);
}

/*==============================================================*
* The removeStart function removes the first data of the list. *
*==============================================================*/
template <class T>
void List<T>::removeStart ()
{
	assert (!isEmpty ());
	if (length == 1)
	{
		delete start;
		start = stop = iterator = NULL;
	}
	else
	{
		if (iterator == start)
			iterator = NULL;
		start = start->next;
		delete start->previous;
		start->previous = NULL;
	}
	length--;
}

/*============================================================*
* The removeStop function removes the last data of the list. *
*============================================================*/
template <class T>
void List<T>::removeStop ()
{
	assert (!isEmpty ());
	if (length == 1)
	{
		delete stop;
		start = stop = iterator = NULL;
	}
	else
	{
		if (iterator == stop)
			iterator = NULL;
		stop = stop->previous;
		delete stop->next;
		stop->next = NULL;
	}
	length--;
}

/*===========================================================================*
* The insertStart function inserts a new data at the beginning of the list. *
*===========================================================================*/
template <class T>
void List<T>::insertStart (T x)
{
	Node *ptr = new Node (x);

	if (length == 0)
		stop = ptr;
	else
	{
		ptr->next = start;
		start->previous = ptr;
	}

	start = ptr;
	length++;
}

/*====================================================================*
* The insertStop function inserts a new data at the end of the list. *
*====================================================================*/
template <class T>
void List<T>::insertStop (T x)
{
	Node *ptr = new Node (x);

	if (length == 0)
		start = ptr;
	else
	{
		stop->next = ptr;
		ptr->previous = stop;
	}

	stop = ptr;
	length++;
}

/*=========================================================================*
* The startIterator function moves the iterator to the start of the list. *
*=========================================================================*/
template <class T>
void List<T>::startIterator ()
{
	iterator = start;
}

/*====================================================================================*
* The removeIterator function removes the node currently pointed to by the iterator. *
* Iterator then points to previous. Works in a pair with insertIterator to update    *
* customer information.																				 *
*====================================================================================*/
template <class T>
void List<T>::removeIterator ()
{
	assert (!offEnd ());
	if (iterator == start)
		removeStart ();
	else if (iterator == stop)
		removeStop ();
	else
	{
		Node * temp = iterator->previous;
		iterator->previous->next = iterator->next;
		iterator->next->previous = iterator->previous;
		delete iterator;
		iterator = temp;
		length--;
	}
}

/*======================================================*
* The insertIterator function inserts a new data after *
* the node currently pointed to by the iterator.	    *
*======================================================*/
template <class T>
void List<T>::insertIterator (T x)
{
	assert (!offEnd ());
	if (iterator == stop)
		insertStop (x);
	else
	{
		Node *ptr = new Node (x);
		ptr->next = iterator->next;
		iterator->next->previous = ptr;
		iterator->next = ptr;
		ptr->previous = iterator;
		length++;
	}
}

/*===========================================================================*
* The moveIterNext function moves the iterator up by one node towards stop. *
*===========================================================================*/
template <class T>
void List<T>::moveIterNext ()
{
	assert (!offEnd ());
	iterator = iterator->next;
}

/*==================================================================================*
* The moveIterPrevious function moves the iterator down by one node towards start. *
*==================================================================================*/
template <class T>
void List<T>::moveIterPrevious ()
{
	assert (!offEnd ());
	iterator = iterator->previous;
}

/*==================================================================*
* The moveToIndex function moves the iterator to the indexed node. *
*==================================================================*/
template <class T>
void List<T>::moveToIndex (int index)
{
	assert (length != 0 && index <= length && index > 0);

	iterator = start;
	for (int i = 1; i < index; i++)
		iterator = iterator->next;
}

/*===================================================================*
* The displayList function prints the list to the screen or a file. *
*===================================================================*/
template <class T>
void List<T>::displayList (ostream &out) const
{
	Node *ptr = start;
	while (ptr)
	{
		out << ptr->data << endl;
		ptr = ptr->next;
	}
}

/*=============================================================================================*
* The displayNumberedList function prints the list to the screen or a file by numbered format. *
*==============================================================================================*/
template <class T>
void List<T>::displayNumberedList (ostream &out) const
{
	Node *ptr = start;
	for (int i = 1; i <= length; i++)
	{
		out << i << ": " << ptr->data << endl;
		ptr = ptr->next;
	}
	out << endl;
	return;
}

#endif
