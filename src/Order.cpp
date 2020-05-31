// Implementation file for Order class

#include "Order.h"

//Accessors

int Order::getPriority() const
{
	return priority;
}

int Order::getQuantity() const
{
	return quantity;
}

int Order::getID() const
{
	return ID;
}

string Order::getType() const
{
	return type;
}

string Order::getModel() const
{
	return model;
}

string Order::getBrand() const
{
	return brand;
}

string Order::getAddress() const
{
	return address;
}

bool Order::getShip() const
{
	return ship;
}

//Manipulators

void Order::setPriorityRaw(int pr)
{
	priority = pr ;
}

void Order::setPriority(int p)
{
	int second ;
	second = (int) time(NULL) ;
	priority = 0 - (second + p * 86400) ;
}

void Order::setQuantity(int q)
{
	quantity = q ;
}

void Order::setID(int id)
{
	ID = id ;
}

void Order::setType(string t)
{
	type = t ;
}

void Order::setModel(string m)
{
	model = m ;
}

void Order::setBrand(string b)
{
	brand = b ;
}

void Order::setAddress (string a)
{
	address = a ;
}

void Order::setShip(bool s)
{
	ship = s ;
}

//Additional Functions

bool Order::operator==(const Order &order)
{
	return priority == order.priority;
}

bool Order::operator<(const Order &order)
{
	return priority < order.priority;
}

bool Order::operator>(const Order &order)
{
	return priority > order.priority;
}

ostream& operator<<(ostream &os, const Order &order)
{
	os << "Order ID: " << order.ID << endl ;
	os << "Product: " << order.model << " by " << order.brand << endl ;
	os << "Quantity: " << order.quantity << endl ;
	os << "Shipping Address: " << endl << order.address << endl ;
	os << "Order type: " << order.type << endl ;
	os << "Order Status: " ;
	if (order.ship == false)
		os << "Product has not been shipped yet" << endl << endl ;
	else
		os << "Product has been shipped" << endl << endl ;
	return os;
}
