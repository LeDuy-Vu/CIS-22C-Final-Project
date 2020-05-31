// Specification file for Customer class

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "Order.h"
#include "List.h"

using namespace std ;

class Customer
{
	private:
    	string first_name ;
    	string last_name ;
    	string address ;
    	string city ;
    	string state ;
    	string zip ;
    	int ID ;
    	string phone ;
    	List<Order> orders ;

	public:

    	//Constructors and Destructor
    	Customer(int _id = 0, string _first_name = "", string _last_name = "", string _address = "", string _city = "", string _state = "", string _zip = "", string phone = "");
    	~Customer() ;

    	//Accessors
    		string getFirstName() const ;
    		string getLastName() const ;
    		int getID() const ;
    		List<Order> getOrders() const { return orders; }

    	//Manipulators
    		void setID(int id) ;
    		void editInfo();

    	//Additional Functions
    		bool operator==(const Customer &c) const ;
    		bool operator>(const Customer &c) const ;
    		friend ostream& operator<<(ostream &out, const Customer &c) ;
    		friend istream& operator>>(istream &in, Customer &c) ;
    		void displayOrders (ostream &out) const ;
    		static Customer newCustomer() ;
    		Order placeOrder(string m, string b, int q) ;
};

#endif
