#include "Outline.h"

// Main entry point
int main()
{
	cout << "Welcome to Team 8 Laptop Shop!" << endl << endl << endl;

	CustomerHash Customers;
	EmployeeHash Employees;
	BST BSTModel, BSTBrand;

	// Load orders from file
	vector<Order> orders_vector;
	prePopulateOrders (orders_vector);
	Heap PriorityQueue (orders_vector);

	// Load users hash from file
	prePopulateHash<CustomerHash, Customer> (Customers, CUST_FILE);
	prePopulateHash<EmployeeHash, Employee> (Employees, EMP_FILE);

	// Load products from file
	prePopulateBST (BSTModel, BSTBrand);

	//BSTModel.inOrderPrint (cout);
	//cout << "===========================" << endl;
	//BSTBrand.inOrderPrint (cout);

	switch (menu ("Are you a:", 3, "Customer", "Employee", "Quit"))
	{
	case 1:
		menu_customer (Customers, BSTModel, BSTBrand, PriorityQueue);
		break;
	case 2:
		menu_employee (Employees, Customers, BSTModel, BSTBrand, PriorityQueue);
		break;
	case 3:
	{
		cout << endl << "System closed!" << endl ;
		break;
	}
	}

	// Store customers to file
	printHashToFile<CustomerHash, Customer> (Customers, CUST_FILE);
	printHashToFile<EmployeeHash, Employee> (Employees, EMP_FILE);

	// store products to file
	printBSTToFile (BSTModel);

	// store orders to file
	printOrdersToFile (orders_vector);

	return 0;
}


// Update customer database with new customer info
// Returns new customer ID
static int customerHashUpdate (CustomerHash &Customers, const Customer &cust, Customer &new_cust)
{
	Customers.remove (cust, Customers.hash (cust.getFirstName () + cust.getLastName ()));
	return userInsertToHash (Customers, new_cust);
}


// Main customer menu
void menu_customer (CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue)
{
	for(;;)
	{
		switch (menu ("Welcome to the Customer Page!", 3, "Sign in", "Create account", "Quit"))
		{
		case 1:
			menu_CustomerSignin (Customers, BSTModel, BSTBrand, PriorityQueue);
			break;
		case 2:
			menu_CustomerNew (Customers);
			break;
		case 3:
		{
			cout << endl << "Thank you for visiting Team 8 Laptop Shop!" << endl ;
			return;
		}
		}
	}
}

// Customer sign-in sub-menu
void menu_CustomerSignin (CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue)
{
	int id;
	cout << "Enter ID: ";
	cin >> id;
	Customer search (id);
	int index = ID2hash (id);
	Customer empty;
	Customer found = index >=0 ? Customers.searchId (search, index) : empty;
	if (found == empty)
	{
		cout << endl << "Customer ID is not registered!\n\n";
		return;
	}

	cout << "Welcome " << found.getFirstName () << " " << found.getLastName () << "!" << endl << endl;

	for(;;)
	{
		switch (menu ("What would you like to do?", 6,
			"Search product", "Print list", "Place an Order", "View Purchases", "Edit Personal Information", "Sign Out"))
		{
		case 1:	// product search
			menu_CustomerProductSearch (BSTModel, BSTBrand);
			break;
		case 2:	// Print list
			menu_CustomerPrintList (BSTModel, BSTBrand);
			break;
		case 3:
			menu_CustomerPlaceOrder (Customers, BSTModel, BSTBrand, PriorityQueue, found);
			break;
		case 4:	// View Purchases
			menu_CustomerViewPurchases (found);
			break;
		case 5:	// Edit personal information
			menu_CustomerEditPersonalInfo(Customers, found);
			break;
		case 6:	// sign-out
			return;
		}
	}
	return;
}


// Handle New customer menu
void menu_CustomerNew (CustomerHash &Customers)
{
	Customer incoming = Customer::newCustomer ();
	userInsertToHash (Customers, incoming);
	cout << endl << "Your ID for future sign-ins is " << incoming.getID () << endl << endl;
}

// Handle customer product search sub-menu
void menu_CustomerProductSearch (const BST &BSTModel, const BST &BSTBrand)
{
	for (;;)
	{
		switch (menu ("How would you like to search our products?", 3, "By model", "By brand", "Back"))
		{
		case 1:	// by model
			menu_CustomerProductSearchByModel (BSTModel);
			break;
		case 2:	// by brand
			menu_CustomerProductSearchByBrand (BSTBrand);
			break;
		case 3:
			return;
		}
	}
}


// Handle customer Search by model
void menu_CustomerProductSearchByModel (const BST &BSTModel)
{
	string model;
	cout << "Enter the model: ";
	getline (cin, model);

	// capitalize first letter
	model.at (0) = toupper (model.at (0));

	Product p, empty;
	p.setModel (model);
	Product found = BSTModel.searchModel (p);
	if (found != empty)
	{
		cout << "This product exists in our database: " << endl;
		cout << found;
	}
	else
	{
		cout << "This product does not exist in our database." << endl;
	}
}

// Handle customer Search by brand
void menu_CustomerProductSearchByBrand (const BST &BSTBrand)
{
	string brand;
	cout << "Enter the brand: ";
	getline (cin, brand);

	// capitalize first letter
	brand.at (0) = toupper (brand.at (0));

	Product p;
	p.setBrand (brand);
	cout << "Results for '" << brand << "'" << endl << endl;
	bool found = BSTBrand.searchBrand(p);
	if (!found)
	{
		cout << "No product of this brand has been found." << endl << endl;
	}
}


// Handle customer Print list of products
void menu_CustomerPrintList (const BST &BSTModel, const BST &BSTBrand)
{
	for (;;)
	{
		switch (menu ("How would you like the products to be displayed?", 3, "By model", "By brand", "Back"))
		{
		case 1:
			cout << "Here are all our products sorted by model:" << endl;
			BSTModel.inOrderPrint (cout);
			break;
		case 2:
			cout << "Here are all our products sorted by brand:" << endl;
			BSTBrand.inOrderPrint (cout);
			break;
		case 3:
			return;
		}
	}
}


// Handle customer View Purchases menu
void menu_CustomerViewPurchases (const Customer &cust)
{
	if (cust.getOrders ().getLength () > 0)
	{
		cout << "Your purchases:" << endl;
		cust.displayOrders (cout);
	}
	else
		cout << "You have made no purchases so far" << endl << endl;
}


// Handle customer Edit personal information menu
void menu_CustomerEditPersonalInfo (CustomerHash& Customers, const Customer &cust)
{
	Customer edit_cust = cust;
	edit_cust.editInfo ();

	int newID = customerHashUpdate (Customers, cust, edit_cust);
	if (newID != cust.getID ())
		cout << endl << "WARNING! Your ID is changed! Your new ID is " << newID << endl << endl;
}


// Handle customer Place Order sub-menu
void menu_CustomerPlaceOrder (CustomerHash& Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue, Customer &cust)
{
	string model;
	cout << "What product model would you like to order?" << endl << "Input model: ";
	getline (cin, model);
	model.at (0) = toupper (model.at (0));

	Product template_prod, empty;
	template_prod.setModel (model);
	Product found_prod = BSTModel.searchModel (template_prod);
	if (found_prod == empty)
	{
		cout << endl << "Product " << model << " not found!" << endl << endl;
		return;
	}

	const int in_stock = found_prod.getInStock ();
	if (in_stock == 0)
	{
		cout << endl << "Product " << model << " out of stock!" << endl << endl;
		return;
	}

	int quantity;
	cout << "How many would you like?" << endl << "Input quantity: ";
	cin >> quantity;

	if(quantity <= 0 || quantity > in_stock)
	{
		cout << endl << "Product quantity should be from 1 to " << in_stock << endl << endl;
		return;
	}

	// place order
	Order order = cust.placeOrder (found_prod.getModel (), found_prod.getBrand (), quantity);
	PriorityQueue.queue (order);

	found_prod.setInStock (in_stock - quantity);

	// update product databases:
	BSTModel.remove (found_prod);
	BSTModel.insertModel (found_prod);
	BSTBrand.remove (found_prod);
	BSTBrand.insertBrand (found_prod);

	// update customer database:
	customerHashUpdate (Customers, cust, cust);

	cout << endl << "Order has been placed!" << endl ;
	cout << "Order ID: " << order.getID() << endl << endl ;
}


// Main employee menu
void menu_employee (EmployeeHash &Employees, CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue)
{
	for (;;)
	{
		switch (menu ("Welcome to the Employee Page!", 3, "Sign In", "Create Account", "Quit"))
		{
		case 1:
			menu_EmployeeSignin (Employees, Customers, BSTModel, BSTBrand, PriorityQueue);
			break;
		case 2:
			menu_EmployeeNew (Employees);
			break;
		case 3:
		{
			cout << endl << "Program closed!" << endl ;
			return;
		}
		}
	}

}

// Handle Employee sign-in sub-menu
void menu_EmployeeSignin (EmployeeHash &Employees, CustomerHash &Customers, BST &BSTModel, BST &BSTBrand, Heap &PriorityQueue)
{
	int id;
	cout << "Enter ID: ";
	cin >> id;
	Employee search ("", "", id);
	int index = ID2hash (id);
	Employee empty;
	Employee found = index >= 0 ? Employees.searchId (search, index) : empty;
	if (found == empty)
	{
		cout << endl << "Employee ID is not registered!\n\n" ;
		return;
	}

	cout << "Welcome " << found.getFirstName () << " " << found.getLastName () << "!" << endl << endl;
	for (;;)
	{
		switch (menu ("What would you like to do?", 9, "Search Customer", "Display Customers",
			"View Orders", "Ship Order", "List Database", "Add Product", "Remove Product",
			"Update Stock", "Back"))
		{
		case 1:	// Search Customer
			menu_EmployeeSearchCustomer (Customers);
			break;
		case 2:	// Display Customers
			Customers.printTable (cout);
			cout << endl;
			break;
		case 3:	// View Orders
			if(PriorityQueue.get_size() == 0)
				cout << "No orders to ship!" << endl;
			else
				PriorityQueue.displayOrders (cout);
			cout << endl;
			break;
		case 4:	// Ship Order
			menu_EmployeeShipOrder (PriorityQueue);
			break;
		case 5:	// List Database
			menu_CustomerPrintList (BSTModel, BSTBrand);
			break;
		case 6:	// Add Product
			menu_EmployeeAddProduct (BSTModel, BSTBrand);
			break;
		case 7:	// Remove Product
			menu_EmployeeRemoveProduct (BSTModel, BSTBrand);
			break;
		case 8:	// Update Stock
			menu_EmployeeUpdateStock (BSTModel, BSTBrand);
			break;
		case 9:
			return;
		}
	}
}


// Handle New employee menu
void menu_EmployeeNew (EmployeeHash &Employees)
{
	Employee incoming = incoming.newEmployee ();
	userInsertToHash (Employees, incoming);
	cout << endl << "Your ID for future sign-ins is " << incoming.getID () << endl << endl;
}


// Handle employee Search Customer menu
void menu_EmployeeSearchCustomer(CustomerHash &Customers)
{
	string fn, ln;
	cout << "Enter First Name: ";
	cin >> fn;
	cout << "Enter Last Name: ";
	cin >> ln;

	int index = Customers.hash (fn + ln);
	Customer Customer (0, fn, ln), empty;
	Customer = Customers.searchCustomer (Customer, index);

	if (Customer == empty)
		cout << "Customer " << fn << " " << ln << " not found!" << endl << endl;
	else
		cout << Customer << endl;
}

// Handle employee Ship Order menu
void menu_EmployeeShipOrder (Heap &PriorityQueue)
{
	if (PriorityQueue.get_size () == 0)
	{
		cout << "No orders to ship!" << endl << endl;
		return;
	}

	cout << "This is the first order that needs to be shipped:" << endl;
	cout << PriorityQueue.get_max ();

	switch (menu ("Would you like to ship this order now?", 2, "Yes", "No"))
	{
	case 1:	// Yes
		PriorityQueue.dequeue ();
		break;
	case 2:	// No
		break;
	}
}


// Handle employee Add Product menu
void menu_EmployeeAddProduct (BST &BSTModel, BST &BSTBrand)
{
	Product x = Product::newProduct ();
	if (x.getModel () == BSTModel.searchModel (x).getModel ())
		cout << x.getModel () << " already exists in database!" << endl << endl;
	else
	{
		BSTBrand.insertBrand (x);
		BSTModel.insertModel (x);
		cout << endl << x.getModel () << " added to database" << endl << endl;
	}
}


// Handle employee Remove Product menu
void menu_EmployeeRemoveProduct (BST &BSTModel, BST &BSTBrand)
{
	string name, decision;
	cout << "Enter the model of the product you want to remove: ";
	cin >> ws;
	getline (cin, name);

	Product x, empty;
	x.setModel (name);
	Product found = BSTModel.searchModel (x);

	if (found == empty)
		cout << "The product model " << name << " is not found in database!" << endl << endl;
	else
	{
		cout << "This is the product you searched for:" << endl;
		cout << found;
		cout << "You want to remove it from the shop? (Y/y to agree, any other key to dismiss): " << endl;
		string decision;
		getline (cin, decision);
		if (decision == "Y" || decision == "y")
		{
			BSTModel.remove (found);
			BSTBrand.remove (found);
			cout << "The product model " << name << " is removed from database" << endl << endl;
		}
	}
}


// Handle employee Update Stock menu
void menu_EmployeeUpdateStock (BST &BSTModel, BST &BSTBrand)
{
	string name, decision;
	cout << "Enter the model of the product you want to update: ";
	cin >> ws;
	getline (cin, name);

	Product x, empty;
	x.setModel (name);
	Product found = BSTModel.searchModel (x);

	if (found == empty)
		cout << "The product model " << name << " is not found in database!" << endl << endl;
	else
	{
		cout << "This is the product you searched for:" << endl;
		cout << found;
		cout << "Enter new stock: " << endl;
		int stock;
		cin >> stock;
		found.setInStock (stock);
		BSTBrand.insertBrand (found);
		BSTModel.insertModel (found);
		cout << "The product model " << name << " is updated. New stock is " << stock << endl << endl;
	}
}

// Ask for choice from 1 to <max>
int choice (int max)
{
	int choice;
	cout << "Enter choice: ";
	cin >> choice;
	cin.clear ();
	cin.ignore (INT_MAX, '\n');
	while (choice < 1 || choice > max || static_cast<bool>(isalpha (choice)) == true)
	{
		cout << endl << "Invalid entry!" << endl << endl;
		cout << "Enter choice: ";
		cin >> choice;
		cin.clear ();
		cin.ignore(INT_MAX, '\n');
	}
	cout << endl << endl << endl;

	return choice;
}

// Show menu with <n> choices
// and ask for choice
int menu (const char* leadPhrase, int n, ...)
{
	va_list argptr;
	cout << leadPhrase << endl << endl;
	va_start (argptr, n);
	for (int i = 1; i <= n; i++)
	{
		string option = va_arg (argptr, const char*);
		cout << "     " << i << ": " << option << endl;
	}
	cout << endl;
	va_end (argptr);
	return choice (n);
}
