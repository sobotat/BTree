#include "Node.h"

Node::Node(int minDegree, bool isLeaf) {
	this->minDegree = minDegree;
	this->isLeaf = isLeaf;

	keys = vector<int>();	
	childNodes = vector<Node*>();
}

Node::~Node() {

	for (Node* node : childNodes) {
		delete node;
	}
}

void Node::insertNonFull(int key) {
	int index = keys.size() - 1;
	if (isLeaf) {		
		while (index >= 0 && keys.at(index) > key) {
			if(keys.size() > index + 1)
				keys.at(index + 1) = keys.at(index);
			else 
				keys.push_back(keys.at(index));

			index--;
		}

		if (keys.size() > index + 1)
			keys.at(index + 1) = key;
		else
			keys.push_back(key);

		return;
	}

	while (index >= 0 && keys.at(index) > key) {
		index--;
	}

	if (childNodes.at(index + 1)->keys.size() == (2 * minDegree - 1)) {
		
		splitChild(index + 1, childNodes.at(index + 1));

		if (keys.at(index + 1) < key) {
			index++;
		}
	}

	childNodes.at(index + 1)->insertNonFull(key);
}

void Node::splitChild(int index, Node* node) {

	Node* splitNode = new Node(node->minDegree, node->isLeaf);
	
	for (int j = 0; j < minDegree - 1; j++) {
		splitNode->keys.push_back(node->keys.at(j + minDegree));
	}

	if (!node->isLeaf) {
		for (int j = 0; j < minDegree; j++) {
			splitNode->childNodes.push_back(node->childNodes.at(j + minDegree));
		}
	}
	
	childNodes.push_back(splitNode);

	for (int j = keys.size() - 2; j >= index; j--) {
		keys.at(j + 1) = keys.at(j);
	}
	
	keys.push_back(node->keys.at(minDegree - 1));
	node->keys.erase(node->keys.begin() + minDegree - 1, node->keys.end());

	if(node->childNodes.size() > minDegree)
		node->childNodes.erase(node->childNodes.begin() + minDegree, node->childNodes.end());
}

int Node::findKey(int key) {
	
	int index = 0;
	while (index < keys.size() && key > keys.at(index)) {
		++index;
	}
	return index;
}

Node* Node::search(int key) {

	int index = findKey(key);
	
	if (keys.size() > index && keys.at(index) == key)
		return this;

	if (isLeaf)
		return nullptr;

	return childNodes.at(index)->search(key);
}

void Node::remove(int key) {

	int index = findKey(key);

	if (keys.size() > index && keys.at(index) == key) {
		if (isLeaf)
			removeFromLeaf(index);
		else
			removeFromNonLeaf(index);

		return;
	}

	if (isLeaf) {
		cout << "Key not found in Tree\n";
		return;
	}
	
	if (childNodes.size() <= index)
		return;

	childNodes.at(index)->remove(key);
	if(childNodes.at(index)->keys.size() > 0){
		merge(index);
		balance(index);
	}
	else if (childNodes.at(index)->keys.size() == 0 && childNodes.at(index)->childNodes.size() > 0) {
		Node* emptyNode = childNodes.at(index);
		childNodes.at(index) = childNodes.at(index)->childNodes.front();
		delete emptyNode;
	}
	else {
		/*
		Node* emptyNode = childNodes.at(index);
		childNodes.erase(childNodes.begin() + index);

		if (childNodes.size() == 0)
			isLeaf = true;

		delete emptyNode;*/

		if (keys.size() > 0){
			childNodes.at(index + 1)->moveToLeaf(keys.at(index));
			keys.erase(keys.begin() + index);
		}

		Node* emptyNode = childNodes.at(index);
		childNodes.erase(childNodes.begin() + index);

		delete emptyNode;
	}
}

void Node::removeFromLeaf(int index) {
	for (int i = index + 1; i < keys.size(); ++i) {
		keys.at(i - 1) = keys.at(i);
	}

	keys.erase(keys.begin() + keys.size() - 1);
}

void Node::removeFromNonLeaf(int index) {

	int key = keys.at(index);

	if (childNodes.size() > index && childNodes.at(index)->keys.size() >= minDegree) {
		int predecessor = getPredecessor(index);
		keys.at(index) = predecessor;
		childNodes.at(index)->remove(predecessor);
	}
	else if (childNodes.size() > index + 1 && childNodes.at(index + 1)->keys.size() >= minDegree) {
		int successor = getSuccessor(index);
		keys.at(index) = successor;
		childNodes.at(index + 1)->remove(successor);
	}
	else {
		merge(index);
		//childNodes.at(index)->remove(key);
		keys.erase(keys.begin() + index);
	}
}

int Node::getPredecessor(int index) {

	Node* node = childNodes.at(index);

	while (!node->isLeaf) {
		node = node->childNodes.at(node->keys.size());
	}

	return node->keys.back();
}

int Node::getSuccessor(int index) {

	Node* node = childNodes.at(index + 1);

	while (!node->isLeaf) {
		node = node->childNodes.front();
	}

	return node->keys.front();
}

void Node::merge(int index) {

	if (childNodes.size() < 2 || childNodes.size() <= index + 1)
		return;

	Node* child = childNodes.at(index);
	Node* neighbor = childNodes.at(index + 1);

	if (child->keys.size() + neighbor->keys.size() + 2 < minDegree * 2 &&
		child->isLeaf && neighbor->isLeaf) {

		child->keys.push_back(keys.at(index));

		for (int i = 0; i < neighbor->keys.size(); i++) {
			child->keys.push_back(neighbor->keys.at(i));
		}
		
		keys.erase(keys.begin() + index);
		childNodes.erase(childNodes.begin() + index + 1);

		if (keys.size() == 0) {
			for (int i = 0; i < child->keys.size(); i++) {
				keys.push_back(child->keys.at(i));
			}

			childNodes.erase(childNodes.begin() + index);
			isLeaf = true;
			delete child;
		}

		delete neighbor;
	}
}

void Node::balance(int index) {

	if (childNodes.size() < 2 || childNodes.size() <= index + 1)
		return;

	Node* child = childNodes.at(index);
	Node* neighbor = childNodes.at(index + 1);

	Node* bigger = (child->keys.size() < neighbor->keys.size() ? neighbor : child);
	Node* smaller = (child->keys.size() < neighbor->keys.size() ? child : neighbor);

	if (!child->isLeaf || !neighbor->isLeaf)
		return;

	if (bigger->keys.size() - smaller->keys.size() < 2)
		return;

	if(neighbor->keys.size() > child->keys.size()) {
		child->keys.push_back(keys.front());
		keys.front() = neighbor->keys.front();
		neighbor->keys.erase(neighbor->keys.begin());
	}
	else if (child->keys.size() > neighbor->keys.size()) {
		for (int i = neighbor->keys.size() - 1; i >= 0; i--) {
			if (neighbor->keys.size() > i + 1)
				neighbor->keys.at(i + 1) = neighbor->keys.at(i);
			else
				neighbor->keys.push_back(neighbor->keys.at(i));
		}

		neighbor->keys.front() = keys.front();
		keys.front() = child->keys.back();
		child->keys.erase(child->keys.begin() + child->keys.size() - 1);
	}
}

void Node::moveToLeaf(int key) {

	int index = findKey(key);

	if (isLeaf) {
		keys.push_back(keys.back());
		for (int i = keys.size() - 2; i >= 0; i--) {
			keys.at(i + 1) = keys.at(i);
		}
		keys.front() = key;
	}
	else
		childNodes.at(index)->moveToLeaf(key);	
}

void Node::print(int spacing) {
	int nextSpace = 2;
	string out = "";
	
	for (int s = 0; s < spacing; s++) {
		if (s == (spacing - nextSpace) && childNodes.size() != 0)
			out += "\033[0;36m#\033[0m";
		else if (s == spacing - (nextSpace * 2))
			out += (childNodes.size() == 0 ? "\033[1;30m|\033[0m" : "\033[1;34m>\033[0m");
		else
			out += " ";
	}

	for (int key : keys) {
		out += to_string(key);
		out += " ";
	}

	//if (keys.size() != 0)
		cout << out << "\n";

	for (Node* node : childNodes) {
		node->print(spacing + nextSpace);
	}
}

void Node::printKeys() {

	int index = 0;
	while (index < keys.size()) {
		if (!isLeaf) {
			childNodes.at(index)->printKeys();
		}
		cout << keys[index] << " ";

		index++;
	}

	if (isLeaf == false)
		childNodes.at(index)->printKeys();
}