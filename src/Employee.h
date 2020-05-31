// Specification file for Employee class

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string>
#include <climits>

using namespace std ;

class Employee
{
	private:
		string firstName ;
		string lastName ;
		int ID ;

	public:

		//Constructors and Destructor
			Employee() : firstName(""), lastName(""), ID(0) {}
			Employee(string fn, string ln, int id) ;
			~Employee() ;

		//Accessors
			string getFirstName() const ;
			string getLastName() const ;
			int getID() const ;

		//Manipulators
			void setID(int id) ;

		//Additional Functions
			bool operator==(const Employee &e) const ;
			bool operator>(const Employee &e) const ;
			friend ostream& operator<<(ostream &out, const Employee &e) ;
			friend istream& operator>>(istream &in, Employee &e) ;
			static Employee newEmployee() ;
};

#endif
