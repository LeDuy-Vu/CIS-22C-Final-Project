// Implementation file for Product class

#include "Product.h"

//Accessors

string Product::getModel() const
{
	return model;
}

string Product::getBrand() const
{
	return brand;
}

int Product::getInStock() const
{
	return inStock;
}

//Manipulators

void Product::setModel(string _model)
{
	model = _model ;
}

void Product::setBrand(string _brand)
{
	brand = _brand ;
}

void Product::setPrice(double _price)
{
	price = _price ;
}

void Product::setWeight(double _weight)
{
	weight = _weight ;
}

void Product::setSize(double _size)
{
	size = _size ;
}

void Product::setStorage(int _storage)
{
	storage = _storage ;
}

void Product::setInStock (int _inStock)
{
	inStock = _inStock ;
}

//Additional Functions

void Product::inputDouble(bool &valid, istream &cin)
{
	if (cin.fail())
	{
		cin.clear() ;
		cin.ignore(INT_MAX, '\n') ;
		cout << "Enter a double only!" << endl ;
		valid = false ;
	}
}

void Product::inputInt(bool &valid, istream &cin)
{
	if (cin.fail())
	{
		cin.clear() ;
		cin.ignore(INT_MAX, '\n') ;
		cout << "Enter an integer only!" << endl ;
		valid = false ;
	}
}

void Product::inputNeg(bool &valid, double d)
{
	if (d <= 0)
	{
		cout << "Input must be a positive number!" << endl ;
		valid = false ;
	}
}

void Product::inputNeg(bool &valid, int i)
{
	if (i <= 0)
	{
		cout << "Input must be a positive number!" << endl ;
		valid = false ;
	}
}

Product Product::newProduct()
{
	string model, brand ;
	int storage, inStock ;
	double price, weight, size ;
	bool valid = false ;
	Product x ;

	cout << "Adding a product" << endl ;
	cout << "Model: " ;
	cin >> ws ;
	getline(cin, model) ;
	x.setModel(model) ;

	cout << "Brand: " ;
	cin >> brand ;
	x.setBrand(brand) ;

	while (!valid)
	{
		valid = true ;
		cout << "Price ($): " ;
		cin >> price ;
		inputDouble(valid, cin) ;
		inputNeg(valid, price) ;
	}
	x.setPrice(price) ;

	valid = false ;
	while (!valid)
	{
		valid = true ;
		cout << "Screen Size (inch): " ;
		cin >> size ;
		inputDouble(valid, cin) ;
		inputNeg(valid, size) ;
	}
	x.setSize(size) ;

	valid = false ;
	while (!valid)
	{
		valid = true ;
		cout << "Weight (lbs): " ;
		cin >> weight ;
		inputDouble(valid, cin) ;
		inputNeg(valid, weight) ;
	}
	x.setWeight(weight) ;

	valid = false ;
	while (!valid)
	{
		valid = true ;
		cout << "Storage (GB): " ;
		cin >> storage ;
		inputInt(valid, cin) ;
		inputNeg(valid, storage) ;
	}
	x.setStorage(storage) ;

	valid = false ;
	while (!valid)
	{
		valid = true ;
		cin.ignore(INT_MAX, '\n') ;
		cout << "Total in stock: " ;
		cin >> inStock ;
		inputInt(valid, cin) ;
		inputNeg(valid, inStock) ;
	}
	x.setInStock(inStock) ;
	cin.ignore(INT_MAX, '\n') ;

	return x;
}

ostream& operator<<(ostream &os, const Product &x)
{
	os << "Model: " << x.model << endl ;
	os << "Brand: " << x.brand << endl ;
	os << "Price: $" << x.price << endl ;
	os << "Screen Size: " << x.size << " inches" << endl ;
	os << "Weight: " << x.weight << " lbs" << endl ;
	os << "Storage: " << x.storage << " GB" << endl ;
	os << "Number in stock: " << x.inStock << endl << endl ;
	return os;
}

bool Product::operator==(const Product &x) const
{
	return model == x.model;
}

bool Product::operator!=(const Product &x) const
{
	return model != x.model;
}

void Product::displayProduct (ostream &out) const
{
    out << model << endl ;
    out << brand << endl ;
    out << price << endl ;
    out << size << endl ;
    out << weight << endl ;
    out << storage << endl ;
    out << inStock << endl << endl ;
}
