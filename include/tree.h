#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;

class Tree;

class Node{
	public:
		Node();
		//the parent node
		Node* parent;
		//the right node
		Node* right;
		//the left node
		Node* left;
		//the weight of the node
		int weight;
		//the value of the character
		char value;
};

class Tree{
	public:
		Tree();
		Node* findNode(char);
		void insertNode(char);
		void updateWeight();
		void checkAndSwap();
		string getNYTCode();
		string getCharCode(Node*);
		bool isLeaf(Node*);
		Node* getNodeByBinary(string);
	private:
		Node* root;
		Node* NYT;
};

#endif
