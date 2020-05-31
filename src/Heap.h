#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <iostream>
#include "Order.h"
using namespace std;

class Heap {
private:
	int heap_size;
	vector<Order> *heap;

	/**Helper Functions*/

	void heapify (int i);
	//helper function to build_heap, remove, and sort
	//bubbles an element down to its proper location within the heap

	void heap_increase_key (int i, Order& order);
	//helper funciton to insert
	//bubbles an element up to its proper location

public:

	/**Constructors*/
	Heap (vector<Order> &v);
	//assigns heap to point to v, an unordered array
	//calls build_heap to convert the unordered array into a valid max heap

	/**Manipulation Procedures*/

	void build_heap ();
	//Takes an unordered vector and builds it into a heap
	//Called as a helper function of the constructor
	//Calls heapify as a helper function

	void queue (Order& order);
	//Inserts a new value onto the end of the heap and
	//Bubbles it up to the correct location in the heap
	//Calls heap_increase_key as a helper function

	void dequeue ();
	//removes the node at the provided index of the heap
	//pre: 1 <= i <= get_size()

	void sort ();
	//sorts a heap into ascending order
	//returns the sorted array of values
	//post: heap restored to max heap
	//calls build heap as a helper function
	//calls heapify as a helper function

	/**Access Functions*/

	Order get_max () const;
	//returns the maximum value in the heap
	//pre: heap_size > 0

	int get_parent (int i) const;
	//returns the location (index) of the parent of the element stored at index i
	//pre: 0 < i <= heap_size

	int get_left (int i)  const;
	//returns the location (index) of the left child of the element stored at i
	//pre: 0 < i <= heap_size

	int get_right (int i)  const;
	//returns the location (index) of the right child of the element stored at i
	//pre: 0 < i <= heap_size

	int get_size () const;
	//returns the heap_size (current number of elements)

	Order get_element (int i) const;
	//returns the element at the specified index i
	//pre: 0 < i <= heap_size

	/**Additional Operations*/


	void displayOrders (ostream& out) const;
	//prints each element in the array (heap) separated by a comma

};

#endif /* HEAP_H_ */
