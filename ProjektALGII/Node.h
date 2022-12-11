#include <iostream>
#include <vector>
#include <string>

#pragma once
using namespace std;

class Node {

private:
	vector<int> keys;				/**< Keys Values */
	vector<Node*> childNodes;		/**< Childs of this Node */
	int minDegree;					/**< Minimal Degree of the Tree */
	bool isLeaf;					

public:
	Node(int minDegree, bool isLeaf);	/**< Constructor
										 *   @param minDegree Minimal Degree of the tree
										 *   @param isLeaf If its Leaf
										*/
	~Node();							/**< Destructor */

	void insertNonFull(int key);				/**< Function to insert new Key in the SubTree
												 *   @param key Key to insert
												*/
	void splitChild(int index, Node* node);		/**< Function that will split node in two
												 *   @param key Key to insert
												 *   @param node Node to split
												*/

	int findKey(int key);					/**< Function that will find Index of the Key
											 *   @param key Key
											 *   @return index of the Key
											*/
	Node* search(int key);					/**< Function that will search for the Key
											 *   @param key Key
											 *   @return Node if it finds Key
											*/

	void remove(int key);					/**< Wrapper function that will remove Key in SubTree
											 *   @param key Key
											*/
	void removeFromLeaf(int index);			/**< Function that will remove Key in this Node witch is Leaf
											 *   @param key Key
											*/
	void removeFromNonLeaf(int index);		/**< Function that will remove Key in this Node witch is not Leaf
											 *   @param key Key
											*/

	int getPredecessor(int index);			/**< Function that gets Predecessor where is key present at index location
											 *   @param index Position in Node
											*/
	int getSuccessor(int index);			/**< Function that gets Successor where is key present at index location
											 *   @param index Position in Node
											*/

	void merge(int index);					/**< Function that merge two nodes
											 *   @param index Position
											*/
	void balance(int index);				/**< Function that balance two nodes
											 *   @param index Position
											*/
	void moveToLeaf(int key);				/**< Function that will place key in leaf of subtree
											 *   @param key Key
											*/

	void print(int spacing);				/**< Prints this Node
											 *   @param spacing Space in front of the output
											*/
	string printToString(int spacing);
	void printKeys();						/**< Prints Keys of this Node */

	int countKeys();		/**< Counts all Keys in tree */
	int countMaxKeys();		/**< Counts Maximum posible count of keys in this tree */
	int countPages();		/**< Counts Pages */
	int countHeight();		/**< Counts Height of the tree */

	friend class BTree;
};
