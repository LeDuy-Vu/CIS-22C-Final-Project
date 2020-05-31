// Specification file for Product class

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <string>
#include <climits>

using namespace std ;

class Product
{
	private:
    	string model ;
    	string brand ;
    	double price ;
    	double weight ;
    	double size ;
    	int storage ;
    	int inStock ;

	public:

    	//Constructor and Destructor
    	    Product() : model(""), brand(""), price(0), weight(0), size(0), storage(0), inStock(0) {}
    	    ~Product() {}

    	//Accessors
    		string getModel() const ;
    		string getBrand() const ;
    		int getInStock() const ;

    	//Manipulators
    		void setModel(string _model) ;
    		void setBrand(string _brand) ;
    		void setPrice(double _price) ;
    		void setWeight(double _weight) ;
    		void setSize(double _size) ;
    		void setStorage(int _storage) ;
    		void setInStock (int _inStock) ;

    	//Additional Functions
    		static void inputDouble(bool &valid, istream &cin) ;
    		static void inputInt(bool &valid, istream &cin) ;
    		static void inputNeg(bool &valid, double d) ;
    		static void inputNeg(bool &valid, int i) ;
    		static Product newProduct() ;
    	    friend ostream& operator<<(ostream &os, const Product &x) ;
    	    bool operator==(const Product &x) const ;
    	    bool operator!=(const Product &x) const ;
    	    void displayProduct(ostream &out) const ;
};

#endif
