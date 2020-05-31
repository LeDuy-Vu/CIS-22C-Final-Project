
#include "Heap.h"
#include "Order.h"
#include "Product.h"
#include<cstddef>
#include<assert.h>
#include<iostream>
#include <cmath>

using namespace std;


void Heap::heapify (int i)
{
	int l, r, index_of_max;
	l = get_left (i);
	r = get_right (i);

	index_of_max = i;

	if (l <= heap_size)
	{
		if ((*heap)[l].getPriority () > (*heap)[i].getPriority ())
		{
			index_of_max = l;
		}
	}

	//out << r << heap_size << endl;
	if (r <= heap_size)
	{
		if ((*heap)[r].getPriority () > (*heap)[index_of_max].getPriority ())
		{
			index_of_max = r;
		}
	}

	//cout << "thing:" << (*heap)[1].getBrand() << endl;
	//cout << "thing2:" << (*heap)[index_of_max].getBrand() << endl;

	if (i != index_of_max)
	{
		swap ((*heap)[i], (*heap)[index_of_max]);
		//cout << "new" << (*heap)[1].getBrand() << (*heap)[2].getBrand() << (*heap)[3].getBrand() << endl;

		//cout << "thing2:" << (*heap)[1].getBrand() << endl;


		heapify (index_of_max);

	}
	//cout << "new" << (*heap)[1].getBrand() << (*heap)[2].getBrand() << (*heap)[3].getBrand() << endl;

}

void Heap::heap_increase_key (int i, Order& order)
{
	if (order.getPriority () > (*heap)[i].getPriority ())
	{
		//<< "11111111112" << endl;
		//cout << order.getBrand() << " " << order.getPriority() <<  (*heap)[i].getBrand() << (*heap)[i].getPriority() << "1111111" << endl;
		(*heap)[i] = order;
	}
	//cout << "dasdad" <<(*heap)[i+1].getBrand() << (*heap)[i].getBrand();
	while (i>1 && (*heap)[get_parent (i)].getPriority () < (*heap)[i].getPriority ())
	{
		swap ((*heap)[i], (*heap)[get_parent (i)]);
		i = get_parent (i);
	}
}




Heap::Heap (vector<Order> &v)
{
	heap = &v;
	heap_size = v.size ();
	(*heap).resize (v.size () + 1);
	Order temp = (*heap)[0];
	(*heap)[0] = Order ();
	(*heap).pop_back ();
	(*heap).push_back (temp);
	build_heap ();
}



void Heap::build_heap ()
{
	for (int i = heap_size / 2; i>0; i--)
	{
		heapify (i);
	}
}

void Heap::queue (Order &o)
{
	++heap_size;
	(*heap).resize (heap_size + 1);
	Order temp;
	heap->at (heap_size) = temp;
	heap_increase_key (heap_size, o);
}



void Heap::dequeue ()
{
	cout << "Order #" << (*heap)[1].getID () << " has been shipped." << endl;
	heap->at (1) = heap->at (heap_size);
	heapify (1);

	heap_size--;
	(*heap).resize ((*heap).size () - 1);
	sort ();
}

void Heap::sort ()
{
	int n = heap_size;
	for (int i = n; i>1; i--)
	{
		swap ((*heap)[1], (*heap)[i]);

		heap_size--;
		heapify (1);
	}
	heap_size = n;
	int left = 1, right = heap_size;
	for (int i = 1; i <= heap_size / 2; i++) {
		if ((*heap)[left].getPriority () < (*heap)[right].getPriority ()) {
			swap ((*heap)[left], (*heap)[right]);
			left++;
			right--;
		}
	}
}


/**Access Functions*/

Order Heap::get_max () const
{
	assert (heap_size>0);
	return heap->at (1);
}


int Heap::get_parent (int i) const
{
	//assert(0<i && i<=heap_size);
	return i = i / 2;
}

int Heap::get_left (int i) const
{
	return 2 * i;
}

int Heap::get_right (int i) const
{
	return 2 * i + 1;
}

int Heap::get_size () const
{
	return heap_size;
}

Order Heap::get_element (int i) const
{
	assert (0<i && i <= heap_size);
	return heap->at (i);
}


void Heap::displayOrders (ostream& out) const
{
	for (int i = 1; i <= heap_size; i++)
	{
		out << (*heap)[i] << endl;
	}
	out << endl;
}
