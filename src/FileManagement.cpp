#include "Outline.h"


// Load Orders from file
void prePopulateOrders (vector<Order> &orders)
{
	orders.resize (0);

	ifstream fin;

	fin.open (ORDERS_FILE);
	if (fin.fail ())
	{
		fin.close ();
		return;	// OK to have no orders
	}

	while (!fin.eof ())
	{
		Order ord;
		int orderID = 0;
		string model = "", brand = "", orderSpeed = "", address = "";
		int orderStatus = 0, priority = 0, quantity = 0;

		fin >> orderID;
		if (orderID == 0)
			break;	// EOF

		ord.setID (orderID);
		fin.ignore (1, '\n');

		getline (fin, model);
		ord.setModel (model);

		getline (fin, brand);
		ord.setBrand (brand);

		fin >> quantity;
		ord.setQuantity (quantity);
		fin.ignore (1, '\n');

		getline (fin, address);
		ord.setAddress (address);

		getline (fin, orderSpeed);
		ord.setType (orderSpeed);

		fin >> orderStatus;
		ord.setShip (orderStatus);
		fin.ignore (1, '\n');

		fin >> priority;
		ord.setPriorityRaw (priority);
		fin.ignore (1, '\n');

		fin.ignore (1, '\n');

		orders.push_back (ord);
	}

	fin.close ();
}

// Store Orders to file
void printOrdersToFile (vector<Order> &orders)
{
	ofstream fout;
	fout.open (ORDERS_FILE);
	if (fout.fail ()) {
		fout.close ();
		cout << endl;
		cout << "Cannot find file...\nExiting.";
		exit (1);
	}

	for (size_t oi = 1; oi < orders.size (); oi++)
	{
		fout << orders[oi].getID () << endl;
		fout << orders[oi].getModel () << endl;
		fout << orders[oi].getBrand () << endl;
		fout << orders[oi].getQuantity () << endl;
		fout << orders[oi].getAddress () << endl;
		fout << orders[oi].getType () << endl;
		fout << (orders[oi].getShip () ? 1 : 0) << endl;
		fout << orders[oi].getPriority () << endl;
		fout << endl;
	}

	fout.close ();
}


// Load BSTs from files
void prePopulateBST (BST &modelBST, BST &brandBST)
{
	ifstream fin;
	string strData;
	int intData;
	double dblData;
	Product product;

	fin.open (PROD_FILE);
	if (fin.fail ()) { //Checks to make input file can be found
		fin.close (); //Close previous(the incorrect) file
		cout << endl;
		cout << "Cannot find file...\nExiting.";
		exit (1);
	}

	while (!fin.eof ())
	{
		getline (fin, strData);
		if (strData.length () == 0)
			break;	// last empty line

		product.setModel (strData);
		getline (fin, strData);
		product.setBrand (strData);
		fin >> dblData;
		product.setPrice (dblData);
		fin >> dblData;
		product.setSize (dblData);
		fin >> dblData;
		product.setWeight (dblData);
		fin >> intData;
		product.setStorage (intData);
		fin >> intData;
		product.setInStock (intData);

		getline (fin, strData); // Read in empty line that separates products
		fin.clear ();
		fin.ignore (1, '\n');

		modelBST.insertModel (product);
		brandBST.insertBrand (product);
	}
	fin.close ();
}

// Store BSTs to file
void printBSTToFile (BST &modelBST)
{
	ofstream fout;
	fout.open (PROD_FILE);
	if (fout.fail ()) {
		fout.close ();
		cout << endl;
		cout << "Cannot find file...\nExiting.";
		exit (1);
	}
	modelBST.inOrderPrintToFile (fout);
	fout.close ();
}
