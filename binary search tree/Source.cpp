#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node {
	int data;
	Node* left, * right;
};

class BST {
private:
	Node* root;
	Node* insert(int, Node*);
	int getSize();
	int getSize(Node*);
	void displayInOrder(Node*);
	void Delete(Node* r, int v);
	void countLeft(int limb, int& length, Node* r);
	void countRight(int limb, int& length, Node* r);
	void displayPreOrder(Node* r);
	void countTrue(Node* r, int& sum);
	void Deleter(Node* r);
	void adder(Node* runner, int min, int max, int& total);
public:
	BST();
	void insert(int);
	void displayInOrder();
	void load(int howMany, int minVal, int maxVal);
	void insertNonRecursive(int v);
	Node* find(int v);
	int count(int v);
	void Delete(int v);
	Node* parent(Node* p, Node* c);
	int getHeight();
	void displayPreOrder();
	int countLeaves();
	bool isLeaf(Node* p);
	int maxValue();
	int minValue();
	int TreeSize();
	void treeClear();
	int sumInRange(int min,int max);
}; 

BST::BST() {
	root = nullptr;
}

Node* BST::insert(int v, Node* r) {
	if (r == nullptr) {
		r = new Node;
		r->left = r->right = nullptr;
		r->data = v;
		return r;
	}
	else if (v < r->data) {
		r->left = insert(v, r->left);
		return r;
	}
	else {
		r->right = insert(v, r->right);
		return r;
	}
}
void BST::insert(int v) {
	root = insert(v, root);
}

void BST::insertNonRecursive(int v) {
	Node* r = root;
	if (root != nullptr) {
		do {
			if (v < r->data) {
				if (r->left == nullptr) {
					r->left = new Node;
					r->left->left = r->left->right = nullptr;
					r->left->data = v;
					break;
				}
				else {
					r = r->left;
				}
			}
			else {
				if (r->right == nullptr) {
					r->right = new Node;
					r->right->left = r->right->right = nullptr;
					r->right->data = v;
					break;
				}
				else {
					r = r->right;
				}
			}

		} while (r != nullptr);
	}
	else {
		root = new Node;
		root->data = v;
	}
}

int BST::getSize(Node* r) {
	if (r == nullptr)
		return 0;
	else
		return 1 + getSize(r->left) + getSize(r->right);
}
int BST::TreeSize() {
	return getSize();
}
int BST::getSize() {
	return getSize(root);
}

void BST::displayInOrder(Node* r) {
	if (r != nullptr)
	{
		displayInOrder(r->left);
		cout << r->data << endl;
		displayInOrder(r->right);
	}
}
void BST::displayInOrder() {
	displayInOrder(root);
}
void BST::displayPreOrder(Node* r) {
	if (r != nullptr) {
		cout << r->data << endl;
		displayPreOrder(r->left);
		displayPreOrder(r->right);
	}
}
void BST::displayPreOrder() {
	Node* r = root;
	displayPreOrder(r);
} 

void BST::load(int howMany, int minVal, int maxVal) {
	insert((minVal + maxVal) / 2);
	int range = (maxVal - minVal) + 1;
	srand(time(NULL));
	for (int i = 1; i < howMany; i++) {
		insert(rand() % range + minVal);
	}
	Delete((minVal + maxVal) / 2);
	insert(rand() % range + minVal);
}

Node* BST::find(int v) {
	Node* r = root;
	while (r != nullptr) {
		if (r->data == v) {
			return r;
		}
 		else if (v < r->data) {
			r = r->left;
		}
		else {
			r = r->right;
		}
	}
	return nullptr;
}

int BST::count(int v) {
	int sum = 0;
	Node* r = root;
	while (r != nullptr) {
		if (r->data == v) sum++;
		if (r->data > v) r = r->left;
		else r = r->right;
	}
	return sum;
}

Node* BST::parent(Node* p, Node* c) {
	 while (c != nullptr && p != nullptr) {
		 if (p->left != c && p->right != c) {
			 if (p->data > c->data) {
				 p = p->left;
			 }
			 else {
				 p = p->right;
			 }
		 }
		 else {
			 break;
		 }
	}
	return p;
}

void BST::Delete(Node* r, int v) {
	Node* par = parent(root, r);
	if (r != nullptr) {
		if (isLeaf(r)) { //fruit off bottom
			if (r == root){
				root = nullptr;
			}
			else if (par->data > r->data) {
				par->left = nullptr;
				delete r;
			}
			else {
				par->right = nullptr;
				delete r;
			}
		}

		else if (r->left == nullptr || r->right == nullptr) { //middle of chain
			if (r->left == nullptr) {
				if (r == root){
					if (root->left == nullptr) root = root->right;
					else root = root->left;
				}
				else if (par->data > r->data) {
					par->left = r->right;
				}
				else {
					par->right = r->right;
				}
			}
			else {
				if (par->data > r->data) {
					par->left = r->left;
				}
				else {
					par->right = r->left;
				}
			}
			delete r;
		}

		else {												//middle branch
			Node* hold = r;
			r = r->right;
			if (r->left != nullptr) {
				while (r->left != nullptr) {
					r = r->left;
				}
			}
			else {											//shift right side of tree into spot
				int temp = r->data;
				hold->right = r->right;
				hold->data = r->data;
				delete r;
				return;
			}
			hold->data = r->data;
			parent(hold, r)->left = r->right;
			delete r;
		}
	}
}
void BST::Delete(int v) {
	Delete(find(v), v);
}

void BST::countLeft(int limb, int& length, Node* r) {
	if (r->left != nullptr) {
		r = r->left;
		limb++;
		countLeft(limb, length, r);
	}
	if (r->right != nullptr) {
		r = r->right;
		limb++;
		countLeft(limb, length, r);
	}
	else {
		if (limb > length) {
			length = limb;
		}
	}
}
void BST::countRight(int limb, int& length, Node* r) {
	if (r->right != nullptr) {
		r = r->right;
		limb++;
		countRight(limb, length, r);
	}
	if (r->left != nullptr) {
		r = r->left;
		limb++;
		countRight(limb, length, r);
	}
	else {
		if (limb > length) {
			length = limb;
		}
	}
}
int BST::getHeight() {
	int length = 0;
	int limb = 0;
	Node* runner = root;
	countLeft(limb, length, runner);
	countRight(limb, length, runner);
	return length;
}

bool BST::isLeaf(Node* p) {
	if (p->left == nullptr && p->right == nullptr) return true;
	else return false;
}
void BST::countTrue(Node* r, int& sum) {
	if (r != nullptr) {
		countTrue(r->left, sum);
		if (isLeaf(r))sum++;
		countTrue(r->right, sum);
	}
}
int BST::countLeaves() {
	int sum = 0;
	countTrue(root,sum);
	return sum;
}

int BST::maxValue() {
	Node* r = root;
	if (r != nullptr) {
		while (r->right != nullptr) {
			r = r->right;
		}
		return r->data;
	}
	else {
		cout << "No max for empty tree";
		exit(EXIT_FAILURE);
	}
}
int BST::minValue() {
	Node* r = root;
	if (r != nullptr) {
		while (r->left != nullptr) {
			r = r->left;
		}
		return r->data;
	}
	else {
		cout << "No min for empty tree";
		exit(EXIT_FAILURE);
	}
}

void BST::Deleter(Node* r) {
	if (r != nullptr) {
		Deleter(r->left);
		Deleter(r->right);
		delete r;
	}
}
void BST::treeClear() {
	Node* runner = root;
	Deleter(runner);
	root = nullptr;
}

void BST::adder(Node* runner, int min, int max, int& total){
	if (runner != nullptr) {
		if (runner->data >= min && runner->data <= max) total += runner->data;
		if (runner->data >= min) adder(runner->left, min, max, total);
		if (runner->data <= max) adder(runner->right, min, max, total);
	}
}
int BST::sumInRange(int min,int max) {
	int total = 0;
	if (root == nullptr) return total;
	if (min > max) {
		int temp = min;
		min = max;
		max = temp;
	}
	if (min > maxValue() && max > maxValue() || max < minValue() && min < minValue()) {
		return total;
		/*
		cout << "The values you entered did not contain the tree\n"
			<< "Please enter better integers: ";
		cin >> min >> max;
		return sumInRange(min,max);
		*/
	}
	Node* runner = root;
	adder(runner, min, max, total);
	return total;
}

int main() {
	BST bst1 = BST();
	BST bst2 = BST();
	bst1.load(15, 20, 40);
	bst2.load(20, 0, 100);
	cout << "Tree one: \n\n";
	bst1.displayInOrder();
	cout << "Size of tree is " << bst1.TreeSize() << endl;
	cout << "Tree two: \n\n";
	bst2.displayPreOrder();
	cout << "Size of tree is " << bst2.TreeSize() << endl;

	int min, max;
	cout << "Find sum of range of tree one: ";
	cin >> min >> max;

	cout << "Sum between those numbers is " << bst1.sumInRange(min, max) << endl << endl;
	
	char yn;
	cout << "Clear tree two? (y/n) ";
	cin >> yn;
	if (tolower(yn) == 'y') {
		bst2.treeClear();
	}
	cout << "Tree two:\n";
	bst2.displayInOrder();
	cout << "------\n\n";
}