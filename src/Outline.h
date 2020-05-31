#ifndef _Outline_h_
#define _Outline_h_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdarg.h>
#include <cctype>
#include "Customer.h"
#include "Employee.h"
#include "HashTable.h"
#include "List.h"
#include "BST.h"
#include "Order.h"
#include "Product.h"
#include "Heap.h"

using namespace std;

typedef HashTable<Customer> CustomerHash;
typedef HashTable<Employee> EmployeeHash;


// Ask for choice from 1 to <max>
int choice (int max);

// Show menu with <n> choices
// and ask for choice
int menu (const char* leadPhrase, int n, ...);

// Handle main customer menu
void menu_customer (CustomerHash&, BST&, BST&, Heap&);

// Handle customer sign-in sub-menu
void menu_CustomerSignin (CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue);

// Handle New customer menu
void menu_CustomerNew (CustomerHash &Customers);

// Handle customer product search sub-menu
void menu_CustomerProductSearch (const BST &BSTModel, const BST &BSTBrand);

// Handle customer Search by model
void menu_CustomerProductSearchByModel (const BST &BSTModel);

// Handle customer Search by brand
void menu_CustomerProductSearchByBrand (const BST &BSTBrand);

// Handle customer Print list of products
void menu_CustomerPrintList (const BST &BSTModel, const BST &BSTBrand);

// Handle customer Place Order sub-menu
void menu_CustomerPlaceOrder (CustomerHash& Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue, Customer &cust);

// Handle customer View Purchases menu
void menu_CustomerViewPurchases (const Customer &cust);

// Handle customer Edit personal information menu
void menu_CustomerEditPersonalInfo (CustomerHash& Customers, const Customer &cust);


// Main employee menu
void menu_employee (EmployeeHash &Employees, CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue);

// Handle Employee sign-in sub-menu
void menu_EmployeeSignin (EmployeeHash &Employees, CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue);

// Handle New employee menu
void menu_EmployeeNew (EmployeeHash &Employees);

// Handle employee Search Customer menu
void menu_EmployeeSearchCustomer (CustomerHash &Customers);

// Handle employee Ship Order menu
void menu_EmployeeShipOrder (Heap &PriorityQueue);

// Handle employee Add Product menu
void menu_EmployeeAddProduct (BST &BSTModel, BST &BSTBrand);

// Handle employee Remove Product menu
void menu_EmployeeRemoveProduct (BST &BSTModel, BST &BSTBrand);

// Handle employee Update Stock menu
void menu_EmployeeUpdateStock (BST &BSTModel, BST &BSTBrand);


// Compute unique user ID from hash index
template <class HASH>
int hash2ID (int hash_index, HASH &hash)
{
	return hash_index * 1000 + 10000 + hash.countBucket (hash_index) + 1;
}

// Compute hash index from user ID
inline int ID2hash (int id)
{
	if (id < 10000 || id > 99999)
		return -1;
	return (id - 10000) / 1000;
}


#define PROD_FILE "products.txt"
#define CUST_FILE "customers.txt"
#define EMP_FILE "employees.txt"
#define ORDERS_FILE "orders.txt"

// Load Orders from file
void prePopulateOrders (vector<Order> &orders);

// Store Orders to file
void printOrdersToFile (vector<Order> &orders);


// Load BSTs from file
void prePopulateBST (BST &modelBST, BST &brandBST);

// Store BSTs to file
void printBSTToFile (BST &modelBST);


// Insert user to hash with generating and setting ID
// Returns ID
template <class HASH, class HASHDATA>
int userInsertToHash (HASH &hash, HASHDATA &incoming)
{
	int index = hash.hash (incoming.getFirstName () + incoming.getLastName ());
	int ID = hash2ID (index, hash);
	incoming.setID (ID);
	hash.insert (incoming, index);
	return ID;
}

// Load user hash from file
template <class HASH, class HASHDATA>
void prePopulateHash (HASH &hash, const char* fname)
{
	ifstream fin;

	fin.open (fname);
	if (fin.fail ())
		// no file: just return
		return;

	while (!fin.eof ())
	{
		HASHDATA c;
		fin >> c;
		if (c.getFirstName () == "" && c.getLastName () == "")
			break;
		userInsertToHash (hash, c);
	}
	fin.close ();
}


// Store user to file
template <class HASH, class HASHDATA>
void printHashToFile (HASH &hash, const char* fname)
{
	ofstream fout;
	fout.open (fname);
	if (fout.fail ())
	{
		fout.close ();
		cout << endl;
		cout << "Cannot find file " << fname << endl << "Exiting" << endl;
		exit (1);
	}

	hash.printTable (fout);
	fout.close ();
}

#endif // _Outline_h_
