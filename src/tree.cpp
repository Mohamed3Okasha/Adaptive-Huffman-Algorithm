#include "Tree.h"
#include <queue>

Node::Node() {
	weight = 0;
	value = '\0';
	parent = NULL;
	right = NULL;
	left = NULL;
}

Tree::Tree(){
    //create a node and set the root and NYT equal to that node
	NYT = root = new Node;
}

//find the node by the value of the character
//return the node if found else return null
Node* Tree::findNode(char value) {
	queue<Node*> nodes;
	nodes.push(root);
	while (!nodes.empty()) {
		if (nodes.front()->value == value)
			return nodes.front();
		if (nodes.front()->left && nodes.front()->right) {
			nodes.push(nodes.front()->left);
			nodes.push(nodes.front()->right);
		}
		nodes.pop();
	}
	return NULL;
}

//insert a new node into the tree
void Tree::insertNode(char value) {
	Node* leftNode = new Node;
	Node* rightNode = new Node;
	Node* node = NYT;

	leftNode->parent = node;
	rightNode->parent = node;
	rightNode->value = value;
	++rightNode->weight;

	node->left = leftNode;
	node->right = rightNode;

	NYT = leftNode;
}

//update the weight of the nodes after inserting a new node
void Tree::updateWeight() {
	Node* node = NYT;
	while (node->parent) {
		node->parent->weight = node->parent->left->weight + node->parent->right->weight;
		node = node->parent;
	}
}

//check the weight and swap
void Tree::checkAndSwap() {
	Node* node = NYT->parent;
	while (node) {
		if (node->left->weight > node->right->weight) {
			Node* tempLeft = node->left;
			node->left = node->right;
			node->right = tempLeft;
		}
		node = node->parent;
	}
}

//return the NYT code
string Tree::getNYTCode() {
	string code = "";
	Node* node = NYT;
	while (node->parent) {
		code = (node == node->parent->right ? '1' : '0') + code;
		node = node->parent;
	}
	return code;
}

//return the character code
string Tree::getCharCode(Node* node) {
	string code = "";
	while (node->parent) {
		code = (node == node->parent->right ? '1' : '0') + code;
		node = node->parent;
	}
	return code;
}

bool Tree::isLeaf(Node* node){
    return  node && !node->left && !node->right;
}

Node* Tree::getNodeByBinary(string binary){
    Node* node = root;
    for(int i = 0; i < (int) binary.length(); ++i){
        if(!node)
            return NULL;
        if(binary[i] == '0')
            node = node->left;
        else
            node = node->right;
    }
    return node;
}
