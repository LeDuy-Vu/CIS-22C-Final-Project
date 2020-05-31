#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include "Product.h"

using namespace std;
class BST {
private:
	struct Node {
		Product data;
		Node* left;
		Node* right;

		Node (Product newdata) {
			data = newdata;
			left = NULL;
			right = NULL;
		}
	};

	Node* root;

	/**Private helper functions*/
	void insertModelHelper (Node* root, Product data);
	//private helper function for insert
	//recursively inserts a value into the BST

	void insertBrandHelper (Node* root, Product data);

	void inOrderPrintHelper (ostream& out, Node* root, vector<Product> &v) const;
	//private helper function for inOrderPrint
	//recursively prints tree values in order from smallest to largest

	void copyHelper (Node* copy);
	//recursive helper function to the copy constructor

	void destructorHelper (Node* root);
	//private helper function for the destructor
	//recursively frees the memory in the BST

	Product searchModelHelper (Node* root, Product data) const;
	//recursive helper function to search
	//returns whether the value is found in the tree

	bool searchBrandHelper (Node* root, Product value) const;

	Product minimumHelper (Node* root) const;
	//recursive helper function to minimum
	//returns the minimum value in the tree

	Node* removeHelper (Node* root, Product data);
	//recursive helper function to remove
	//removes data from the tree

	void getSizeHelper (Node* root, int& size) const;
	//recursive helper function to the size function
	//calculates the size of the tree
	//stores the result in size

	void inOrderPrintToFileHelper (ostream& out, Node* root) const;

public:

	/**constructors and destructor*/

	BST ();
	//Instantiates a new BST

	BST (const BST &bst);
	//copy constructor

	~BST ();
	//deallocates the tree memory

	/**access functions*/
	Product minimum () const;
	//returns the minimum value in the BST
	//pre: !empty()

	bool isEmpty () const;
	//determines whether the BST is empty

	int getSize () const;
	//returns the size of the tree

	Product searchModel (Product data) const;
	//returns whether the data is found in the tree
	//pre: !isEmpty()

	bool searchBrand (Product value) const;

	/**manipulation procedures*/

	void insertModel (Product data);
	//inserts new data into the BST

	void insertBrand (Product data);

	void remove (Product data);
	//removes the specified value from the tree
	//pre: data is located in the tree
	//pre: !isEmpty()

	/**additional functions*/

	vector<Product> inOrderPrint (ostream& out) const;
	//calls the inOrderPrint function to print out the values
	//stored in the BST

	void inOrderPrintToFile (ostream& out) const;
};



#endif /* BST_H_ */
