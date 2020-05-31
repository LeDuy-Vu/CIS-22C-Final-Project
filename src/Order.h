// Specification file for Order class

#ifndef ORDER_H_
#define ORDER_H_

#include <cstddef>
#include <assert.h>
#include <time.h>
#include <iostream>
#include <string>
#include <climits>

using namespace std ;

class Order
{
	private:
		int priority ;
		int quantity ;
		int ID ;
		string type ;
		string model ;
		string brand ;
		string address ;
		bool ship ;

	public:

		//Constructors and Destructor
			Order() : priority(INT_MIN), quantity(0), ID(0), type(""), model(""), brand(""), address (""), ship(false) {}
			~Order() {}

		//Accessors
			int getPriority() const ;
			int getQuantity() const ;
			int getID() const ;
			string getType() const ;
			string getModel() const ;
			string getBrand() const ;
			string getAddress() const ;
			bool getShip() const ;

		//Manipulators
			void setPriorityRaw(int pr) ;
			void setPriority(int p) ;
			void setQuantity(int q) ;
			void setID(int id) ;
			void setType(string t) ;
			void setModel(string m) ;
			void setBrand(string b) ;
			void setAddress(string a) ;
			void setShip(bool s) ;

		//Additional Functions
			bool operator==(const Order &order) ;
			bool operator<(const Order &order) ;
			bool operator>(const Order &order) ;
			friend ostream& operator<<(ostream &os, const Order &order) ;
};

#endif
