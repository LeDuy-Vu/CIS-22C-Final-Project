#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>

using namespace std;

template <typename hashdata>
class HashTable {
public:
	typedef hashdata HASHDATA;

	/**Constructors*/

	HashTable () {}
	//constructor

	~HashTable () {}
	//destructor


	/**Access Functions*/

	int hash (string key) const;
	//returns the hash value for the given key
	//the hash value is the sum of
	//of the ASCII values of each char in the key
	//% the size the of the table
	//Key for this table: title + author

	int countBucket (int index) const;
	//counts the number of Books at this index
	//returns the count
	//pre: 0<= index < SIZE

	hashdata searchCustomer (hashdata c, int _in);
	//Searches for b in the table
	//returns the object, if it is located
	//returns empty object if search is unsuccessful

	hashdata searchId (hashdata c, int _in);
	//Searches for object with id in table
	//returns the object, if it is located
	//returns empty object if search is unsuccessful

	/**Manipulation Procedures*/

	void insert (hashdata u, int _in);
	//inserts a new user into the table
	//calls the hash function on the key to determine
	//the correct bucket

	void remove (hashdata u, int _in);
	//deletes a user from the table
	//calls the hash function on the key to determine
	//the correct bucket

	/**Additional Functions*/

	//void printBucket (ostream& out, int index) const;
	//Prints all the books at index
	//pre: 0<= index < SIZE
	//Should print according to the following formula:
	//Prints each book at that index in the format:
	//<title> by <author>
	//$<X.XX>
	//ISBN#: <isbn>
	//followed by a blank line

	void printTable (ostream& out) const;
	//Prints the first book at each index
	//along with a count of the total books
	//at each index by calling count_bucket
	//as a helper function
	//Prints in the format:
	//Books in the Catalogue:
	//<new line>
	//Group <bucket>
	//<title> by <author>
	//$<X.XX>
	//ISBN: <isbn>
	//+<number of elements at this index> -1 more similar book(s)
	//<new line><new line><new line>

private:
	static const int SIZE = 50;
	List<hashdata> Table[SIZE + 1];
};

template <typename hashdata>
int HashTable<hashdata>::hash (string fullName) const {
	int index, sum = 0;
	for (unsigned int i = 0; i < fullName.length (); i++) {
		sum += (int)tolower (fullName[i]); //summing the ASCII values for each character in the string
	}
	index = sum % SIZE; //dividing the summed ASCII values by TABLE_SIZE and storing remainder as my index
	return index + 1;
}
//Uses last name + first name as key, currently uses same hash from lab 7

template <typename hashdata>
int HashTable<hashdata>::countBucket (int index) const
{
	assert (index > 0 && index <= SIZE);
	return Table[index].getLength ();
}
//pre: 0<= index < SIZE

template <typename hashdata>
hashdata HashTable<hashdata>::searchCustomer (hashdata c, int _in)
{
	hashdata empty;
	if (Table[_in].isEmpty ()) { // If bucket is empty already, just return empty object (also bypasses linearSearch assert)
		return empty;
	}
	int index = Table[_in].linearSearch (c);
	if (index == -1) {
		return empty; // Returns empty object if row is not empty AND customer is not in the row
	}
	else
	{
		Table[_in].moveToIndex (index);
		hashdata search = Table[_in].getIterator ();
		return search; // Returns found value
	}
}
//Searches for customer or employee when logging in

template <typename hashdata>
hashdata HashTable<hashdata>::searchId (hashdata c, int _in) {
	hashdata empty;
	if (Table[_in].isEmpty ()) { // If bucket is empty already, just return empty object (also bypasses binarySearch assert)
		return empty;
	}
	int index = Table[_in].binarySearch (c);
	if (index == -1) {
		return empty; // Returns empty object if row is not empty AND customer is not in the row
	}
	else
	{
		Table[_in].moveToIndex (index);
		hashdata search = Table[_in].getIterator ();
		return search; // Returns found value
	}
}

/**Manipulation Procedures*/

template <typename hashdata>
void HashTable<hashdata>::insert (hashdata user, int _in) {
	Table[_in].insertStop (user);
}
//Inserts customer/employee into respective hash tables


//deletes a user from the table
//calls the hash function on the key to determine
//the correct bucket
template <typename hashdata>
void HashTable<hashdata>::remove (hashdata u, int _in)
{
	if (Table[_in].isEmpty ())
		return;	// empty

	int index = Table[_in].binarySearch (u);
	if (index < 0)
		return; // not found

	Table[_in].moveToIndex (index);
	Table[_in].removeIterator ();
}


/**Additional Functions*/

template <typename hashdata>
void HashTable<hashdata>::printTable (ostream& out) const {
	for (int unsigned i = 1; i <= SIZE; i++)
	{
		if (!Table[i].isEmpty ())
			Table[i].displayList (out);
	}
}
//Prints all customersí information onto screen


#endif /* HASHTABLE_H_ */
