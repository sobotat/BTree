#include "BTree.h"

BTree::BTree(int minDegree) {
	this->minDegree = minDegree;
}

BTree::~BTree() {
	if(root != nullptr)
		delete root;
}

void BTree::insert(int key) {

	if (root == nullptr) {
		root = new Node(minDegree, true);
		root->keys.push_back(key);

		return;
	}

	if (root->keys.size() == (2 * minDegree - 1)) {
		Node* node = new Node(minDegree, false);

		node->childNodes.push_back(root);

		node->splitChild(0, root);

		int index = 0;
		if (node->keys.at(0) < key) {
			index++;
		}

		node->childNodes.at(index)->insertNonFull(key);

		root = node;
	} else {
		root->insertNonFull(key);
	}
}

void BTree::remove(int key) {

	if (root == nullptr) {
		cout << "Tree is Empty\n";
		return;
	}

	root->remove(key);

	if (root->keys.size() == 0) {
		Node* orgRoot = root;

		if (root->isLeaf)
			root = nullptr;
		else
			root = root->childNodes.front();
	}
}

Node* BTree::search(int key) {
	if (root == nullptr)
		return nullptr;
	else
		return root->search(key);
}

void BTree::print() {
	cout << "\033[1;34mPrint:\033[0m\n";

	if (root != nullptr)
		root->print(2);
	else
		cout << "Tree is Empty\n";

	cout << "\n";
}

void BTree::printKeys() {
	if (root != nullptr)
		root->printKeys();
}
