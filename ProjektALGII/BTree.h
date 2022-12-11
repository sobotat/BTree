#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"

#pragma once
using namespace std;

class BTree {

private:
	Node* root;			/**< Root Node */
	int minDegree;		/**< Minimal Degree of the tree */

public:
	BTree(int minDegree);	/**< Constructor
							 *   @param minDegree Minimal Degree of the tree
							*/
	~BTree();				/**< Destructor */

	void insert(int key);	/**< Insert Key into the Tree		 
							 *	 @param key Value to insert
							*/
	void remove(int key);	/**< Remove Key from the Tree		 
							 *	 @param key Value to remove
							*/

	Node* search(int key);	/**< Finds Node of the Key in the Tree		 
							 *	 @param key Value
							 *	 @return Returns Node of Key in the tree
							*/
	
	void print();			/**< Prints Tree */
	void clearFile(string fileName);
	void printToFile(string fileName, string heading);
	void printStatus();		/**< Prints information about the Tree */
	void printKeys();		/**< Prints Keys of the Tree */
};