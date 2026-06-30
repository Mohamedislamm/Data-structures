#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "item.h"
using namespace std;

class Node
{
public:

	item data;
	Node* left, * right;
    int height;
	Node(item itemData) : data(itemData), left(NULL), right(NULL), height(1) {}
};

// class Node {
// public:
//     item info;
//     Node* left;
//     Node* right;
//     int height;

//     Node(item i) : info(i), left(nullptr), right(nullptr), height(1) {}
// };


#endif // NODE_H