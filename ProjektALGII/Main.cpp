#include <iostream>
#include "BTree.h"

using namespace std;

/*! \mainpage B-Tree
 *
 * \section intro_sec Introduction
 *
 * This project is made as school poject into Alg II.
 *
 */

string fileName = "out.txt";

void btreeTestVector() {
    vector<int> keys = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300
    };

    BTree* btree = new BTree(3);

    for (int key : keys) {
        cout << "\033[1;32mAdded\033[0m " << key << "\n";
        btree->insert(key);
        btree->print();
    }

    btree->printStatus();

    for (int key : keys) {
        (btree->search(key) != nullptr) ? cout << key << " \033[1;32mFound\033[0m\n" : cout << key << " \033[1;31mNot Found\033[0m\n";
    }

    btree->print();
    for (int key : keys) {
        cout << "\033[1;31mDeleted\033[0m " << key << "\n";
        btree->remove(key);
        btree->print();
    }

    delete btree;
}

void btreeTest(int count) {
    BTree* btree = new BTree(3);
    btree->clearFile(fileName);
    for (int i = 1; i <= count; i++) {
        cout << "\033[1;32mAdded\033[0m " << i << "\n";
        btree->insert(i);
        btree->printToFile(fileName, ("Added " + to_string(i)));
    }

    btree->printStatus();
    
    int notFound = 0;
    for (int i = 1; i <= count; i++) {
        if (btree->search(i) != nullptr)
            cout << i << " \033[1;32mFound\033[0m\n";
        else {
            cout << i << " \033[1;31mNot Found\033[0m\n";
            notFound++;
        }
    }
    cout << "\033[1;31mNot Found\033[0m Count: " << notFound << "\n\n";

    for (int i = 1; i <= count; i++) {
        cout << "\033[1;31mDeleted\033[0m " << i << "\n";
        btree->remove(i);
        btree->printToFile(fileName, ("Deleted " + to_string(i)));
    }
    

    delete btree;
}

int main() {
    cout << "\033[1;34mB-Tree Projekt\033[0m\n\n";
    
    //btreeTestVector();
    btreeTest(25);  

    cout << "\nEND";
}