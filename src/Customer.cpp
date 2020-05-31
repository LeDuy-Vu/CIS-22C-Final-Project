#include "Customer.h"

Customer::Customer(int _id, string _first_name, string _last_name, string _address, string _city, string _state, string _zip, string _phone)
{
	first_name = _first_name;
	last_name = _last_name;
	address = _address;
	city = _city;
	state = _state;
	zip = _zip;
	ID = _id;
	phone = _phone;
}

Customer::~Customer () {}

string Customer::getFirstName () const
{
	return first_name;
}

string Customer::getLastName () const
{
	return last_name;
}

int Customer::getID() const
{
	return ID;
}

bool Customer::operator == (const Customer &rhs) const
{
	return ((ID == rhs.ID) || (first_name == rhs.first_name && last_name == rhs.last_name));
}

bool Customer::operator > (const Customer &rhs) const
{
	return ID > rhs.ID;
}

ostream& operator << (ostream &out, const Customer &rhs)
{
	out << rhs.ID << endl;
	out << rhs.first_name << " " << rhs.last_name << endl;
	out << rhs.address << endl << rhs.city << endl << rhs.state << " " << rhs.zip << endl;
	out << rhs.phone << endl;
	return out;
}


istream& operator >> (istream &in, Customer &rhs)
{
	in >> rhs.ID;
	in.ignore (INT_MAX, '\n');

	in >> rhs.first_name;
	in >> rhs.last_name;
	in.ignore (INT_MAX, '\n');

	getline (in, rhs.address);
	getline (in, rhs.city);

	in >> rhs.state;
	in >> rhs.zip;
	in.ignore (INT_MAX, '\n');
	getline (in, rhs.phone);
	in.ignore (INT_MAX, '\n');

	return in;
}

void Customer::displayOrders (ostream &out) const
{
	orders.displayList (out);
}

void Customer::setID (int _id)
{
	ID = _id;
}

Customer Customer::newCustomer ()
{
	string firstName, lastName, address, city, state, phone, zip;
	cout << "Enter first name: ";
	getline (cin, firstName);
	cin.clear ();
	cout << "Enter last name: ";
	getline (cin, lastName);
	cin.clear ();
	cout << "Enter address: ";
	getline (cin, address);
	cin.clear ();
	cout << "Enter city: ";
	getline (cin, city);
	cin.clear ();
	cout << "Enter state: ";
	getline (cin, state);
	cin.clear ();
	cout << "Enter zip code: ";
	cin >> zip;
	cin.clear ();
	cin.ignore (100, '\n');
	cout << "Enter phone number: ";
	cin >> phone;
	cin.clear ();
	cin.ignore (100, '\n');
	Customer customer = Customer (0, firstName, lastName, address, city, state, zip, phone);
	return customer;
}

Order Customer::placeOrder (string m, string b, int q)
{
	Order order;
	order.setModel (m);
	order.setBrand (b);
	cout << "Enter type of shipping:\n     1 - Overnight\n     2 - Rush\n     4 - Standard\n\n";
	cout << "Enter choice: ";
	int choice;
	cin >> choice;
	while (choice != 1 && choice != 2 && choice != 4)
	{
		cout << "\nInvalid choice!\n\n";
		cout << "Enter choice: ";
		cin >> choice;
	}
	if (choice == 1)
		order.setType ("Overnight");
	else if (choice == 2)
		order.setType ("Rush");
	else
		order.setType ("Standard");
	order.setPriority (choice);
	order.setID (ID * 1000 + orders.getLength () + 1);
	order.setQuantity (q);
	order.setShip (false);
	order.setAddress (address + ", " + city + ", " + state + " " + zip);
	orders.insertStop (order);
	return order;
}

void Customer::editInfo ()
{
	bool edit;
	do {
		cout << "1: " << first_name << "\n2: " << last_name << endl;
		cout << "3: " << address << endl << "4: " << city << endl << "5: ";
		cout << state << endl << "6: " << zip << endl << "7: " << phone << endl << endl << endl;
		cout << "What do you want to edit? Enter 1 - 7: ";
		int choice;
		cin >> choice;
		cin.clear ();
		cin.ignore (100, '\n');
		while (choice < 1 || choice > 7 || static_cast<bool>(isalpha (choice)) == true)
		{
			cout << "\nInvalid choice!\n\n";
			cout << "Enter 1 - 7: ";
			cin >> choice;
			cin.clear ();
			cin.ignore (100, '\n');
		}
		switch (choice)
		{
		case 1:
		{
			cout << "Enter new first name: ";
			string n;
			getline (cin, n);
			cin.clear ();
			first_name = n;
			break;
		}
		case 2:
		{
			cout << "Enter new last name: ";
			string n;
			getline (cin, n);
			cin.clear ();
			last_name = n;
			break;
		}
		case 3:
		{
			cout << "Enter new address: ";
			string n;
			getline (cin, n);
			cin.clear ();
			address = n;
			break;
		}
		case 4:
		{
			cout << "Enter new city: ";
			string n;
			getline (cin, n);
			cin.clear ();
			city = n;
			break;
		}
		case 5:
		{
			cout << "Enter new state: ";
			string n;
			getline (cin, n);
			cin.clear ();
			state = n;
			break;
		}
		case 6:
		{
			cout << "Enter new zip: ";
			string n;
			getline (cin, n);
			cin.clear ();
			zip = n;
			break;
		}
		case 7:
		{
			cout << "Enter new phone number: ";
			string n;
			getline (cin, n);
			cin.clear ();
			phone = n;
			break;
		}
		}
		cout << endl << endl << "Do you want to continue editing? (Y/N) ";
		string cont;
		getline (cin, cont);
		cin.clear ();
		while (cont != "Y" && cont != "y" && cont != "N" && cont != "n")
		{
			cout << "\nInvalid choice!\n\n";
			cout << "Enter Y, y, N, or n: ";
			getline (cin, cont);
			cin.clear ();
		}
		if (cont == "Y" || cont == "y")
			edit = true;
		if (cont == "N" || cont == "n")
			edit = false;
	} while (edit == true);
}
