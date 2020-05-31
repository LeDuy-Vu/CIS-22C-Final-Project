#include "BST.h"

//Constructors and Destructor
BST::BST () {
	root = NULL;
}

BST::BST (const BST& bst) {
	root = NULL;
	copyHelper (bst.root);
}

BST::~BST () {
	destructorHelper (root);
}

//Private Helper Functions
void BST::insertModelHelper (Node* root, Product value) {
	if (value.getModel () == (root->data).getModel ()) {
		root->data = value;
	}
	else if (value.getModel () < (root->data).getModel ()) {
		if (root->left == NULL) {
			root->left = new Node (value);
		}
		else {
			insertModelHelper (root->left, value);
		}
	}
	else {
		if (root->right == NULL) {
			root->right = new Node (value);
		}
		else {
			insertModelHelper (root->right, value);
		}
	}
}

void BST::insertBrandHelper (Node* root, Product value) {
	if (value.getBrand () < (root->data).getBrand ()) {
		if (root->left == NULL) {
			root->left = new Node (value);
		}
		else {
			insertBrandHelper (root->left, value);
		}
	}
	else if (value.getBrand () > (root->data).getBrand ()) {
		if (root->right == NULL) {
			root->right = new Node (value);
		}
		else {
			insertBrandHelper (root->right, value);
		}
	}
	else {
		if (root->left == NULL)
			root->left = new Node (value);
		else
		{
			Node* temp = root;
			do {
				if (temp->left != NULL)
					temp = temp->left;
				else
					break;
			} while ((temp->data).getBrand () == value.getBrand ());

			Node* temp2 = temp->left;
			temp->left = new Node (value);
			temp->left->left = temp2;
		}
	}
}

Product BST::searchModelHelper (Node* root, Product value) const {
	Product empty;
	string model = value.getModel() ;
	string compare = root->data.getModel() ;

	for (int i = 0; i < model.length(); i++)
		model[i] = tolower(model[i]) ;
	for (int i = 0; i < compare.length(); i++)
		compare[i] = tolower(compare[i]) ;

	if (model == compare) {
		return root->data;
	}
	else if (model < compare) {
		if (root->left == NULL) {
			return empty;
		}
		else {
			return searchModelHelper (root->left, value);
		}
	}
	else {
		if (root->right == NULL) {
			return empty;
		}
		else {
			return searchModelHelper (root->right, value);
		}
	}
	return empty;
}

bool BST::searchBrandHelper (Node* root, Product value) const {
	if (value.getBrand () == (root->data).getBrand ()) {
		Node* temp = root;
		do {
			cout << temp->data << endl << endl;
			if (temp->left != NULL)
				temp = temp->left;
			else
				break;
		} while ((temp->data).getBrand () == value.getBrand ());
		return true;
	}
	else if (value.getBrand () < (root->data).getBrand ()) {
		if (root->left == NULL) {
			return false;
		}
		else {
			return searchBrandHelper (root->left, value);
		}
	}
	else {
		if (root->right == NULL) {
			return false;
		}
		else {
			return searchBrandHelper (root->right, value);
		}
	}
	return false;
}

Product BST::minimumHelper (Node* root) const {
	if (root->left != NULL) {
		return minimumHelper (root->left);
	}
	else {
		return root->data;
	}
}

typename BST::Node* BST::removeHelper (Node* root, Product value) {
	if (root == NULL) {
		return root;
	}
	else if (value.getModel () < (root->data).getModel ()) {
		root->left = removeHelper (root->left, value);
	}
	else if (value.getModel () > (root->data).getModel ()) {
		root->right = removeHelper (root->right, value);
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		else if (root->right != NULL && root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else {
			Product temp = minimumHelper (root->right);
			root->data = temp;
			root->right = removeHelper (root->right, temp);
		}
	}
	return root;
}

void BST::inOrderPrintHelper (ostream& out, Node* root, vector<Product> &v) const {
	if (root != NULL) {
		inOrderPrintHelper (out, root->left, v);
		out << root->data << endl;
		v.push_back (root->data);
		inOrderPrintHelper (out, root->right, v);
	}
}

void BST::copyHelper (Node* copy) {
	if (copy == NULL) {
		return;
	}
	else {
		insertModel (copy->data);
		copyHelper (copy->left);
		copyHelper (copy->right);
	}
}

void BST::destructorHelper (Node* root) {
	if (root == NULL) {
		return;
	}
	destructorHelper (root->left);
	destructorHelper (root->right);
	delete root;
}

void BST::getSizeHelper (Node* root, int& size) const {
	if (root == NULL) {
		return;
	}
	getSizeHelper (root->left, size);
	getSizeHelper (root->right, size);
	size++;
}

//Public member functions

//Manipulation Procedures

void BST::insertModel (Product value) {
	if (root == NULL) {
		root = new Node (value);
	}
	else {
		insertModelHelper (root, value);
	}
}

void BST::insertBrand (Product value) {
	if (root == NULL) {
		root = new Node (value);
	}
	else {
		insertBrandHelper (root, value);
	}
}

void BST::remove (Product value) {
	assert (!isEmpty ());
	root = removeHelper (root, value);
}

//Access Functions
Product BST::searchModel (Product value) const {
	assert (!isEmpty ());
	return searchModelHelper (root, value);
}

bool BST::searchBrand (Product value) const {
	assert (!isEmpty ());
	return searchBrandHelper (root, value);
}

Product BST::minimum () const {
	assert (!isEmpty ());
	return minimumHelper (root);
}


int BST::getSize () const {
	int size = 0;
	getSizeHelper (root, size);
	return size;
}

bool BST::isEmpty () const {
	if (getSize () == 0) {
		return true;
	}
	return false;
}

//Additional Functions
vector<Product> BST::inOrderPrint (ostream& out) const {
	vector<Product> v;
	if (!isEmpty ()) {
		inOrderPrintHelper (out, root, v);
	}
	return v;
}

void BST::inOrderPrintToFileHelper (ostream& out, Node* root) const {
	if (root != NULL) {
		inOrderPrintToFileHelper (out, root->left);
		root->data.displayProduct (out);
		inOrderPrintToFileHelper (out, root->right);
	}
}

void BST::inOrderPrintToFile (ostream& out) const {
	if (!isEmpty ()) {
		return inOrderPrintToFileHelper (out, root);
	}
}
