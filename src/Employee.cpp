// Implementation file for Employee class

#include "Employee.h"

//Constructor and Destructor
Employee::Employee(string fn, string ln, int id)
{
	firstName = fn ;
	lastName = ln ;
	ID = id ;
}

Employee::~Employee()
{

}

//Accessors

string Employee::getFirstName() const
{
	return firstName;
}

string Employee::getLastName() const
{
	return lastName;
}

int Employee::getID() const
{
	return ID;
}

//Manipulators
void Employee::setID(int id)
{
	ID = id ;
}

//Additional Functions

bool Employee::operator==(const Employee &rhs) const
{
	return ID == rhs.ID;
}

bool Employee::operator>(const Employee &rhs) const
{
	return ID > rhs.ID;
}

ostream& operator<<(ostream &out, const Employee &e)
{
	out << e.ID << endl ;
	out << e.firstName << " " << e.lastName << endl ;
	return out;
}

istream& operator>>(istream &in, Employee &e)
{
	in >> e.ID ;
	in.ignore(INT_MAX, '\n') ;

	in >> e.firstName ;
	in >> e .lastName ;
	in.ignore (INT_MAX, '\n');
	in.ignore (INT_MAX, '\n');

	return in;
}

Employee Employee::newEmployee()
{
	string fn, ln;
	cout << "Enter your first name: ";
	cin >> fn;
	cout << "Enter your last name: ";
	cin >> ln;

	Employee employee(fn, ln, 0);
	return employee;
}
