#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>
#include "item.h"
#include "Node.h"
using namespace std;

class BSTname 
{
protected:

	Node* root;

	Node* InsertName(Node* pnode, item itemData)
	{
		if (pnode == NULL)
		{
			pnode = new Node(itemData);
		}
		else if (itemData.itemname < pnode->data.itemname)
		{
			pnode->left = InsertName(pnode->left, itemData);
		}
		else
		{
			pnode->right = InsertName(pnode->right, itemData);
		}
		return pnode;
	}

	void InorderName(Node* pnode) 
	{
		if (pnode == NULL)
			return;
		InorderName(pnode->left);
		pnode->data.print();
		InorderName(pnode->right);
	}

	void reverseInorderName(Node* pnode)  
	{
		if (pnode == NULL)
			return;
		reverseInorderName(pnode->right);
		pnode->data.print();
		reverseInorderName(pnode->left);
	}

	Node* findmin(Node* pnode)
	{
		Node* ptr = pnode;
		while (ptr && ptr->left != NULL)
			ptr = ptr->left;
		return ptr;
	}
			
	Node* Delete(Node* pnode, string key)
	{
		if (pnode == NULL)
			return NULL;
		if (key < pnode->data.itemname)
			pnode->left = Delete(pnode->left, key);
		else if (key > pnode->data.itemname)
			pnode->right = Delete(pnode->right, key);
		else
		{
			if (pnode->left == NULL)
			{
				Node* temp = pnode->right;
				delete pnode;
				return temp;
			}
			else if (pnode->right == NULL)
			{
				Node* temp = pnode->left;
				delete pnode;
				return temp;
			}
			Node* temp = findmin(pnode->right);
			pnode->data = temp->data;
			pnode->right = Delete(pnode->right, temp->data.itemname);
		}
		return pnode;
	}

	void Preorder(Node* pnode) 
	{
		if (pnode == NULL)
			return;
		pnode->data.print();
		Preorder(pnode->left);
		Preorder(pnode->right);
	}

public:

	BSTname() :root(NULL) {};

	virtual void Insert(item itemData) 
	{
		root = InsertName(root, itemData);
	}
		
	void Delete(string itemName)
	{
		root = Delete(root, itemName);
	}
		
	void DisplayNameAsc()
	{
		cout << "\nItems in Ascending order by name: " << endl;
		InorderName(root);
	}
		
	void DisplayNameDsc()
	{
		cout << "\nItems in Descending order by name: " << endl;
		reverseInorderName(root);
	}

	void DisplayNormally()
	{
		cout << "\nDisplay items Normally: " << endl;
		Preorder(root);
	}
};

class BSTprice :public BSTname 
{
private:

	void InorderPrice(Node* pnode) 
	{
		if (pnode == NULL)
			return;
		InorderPrice(pnode->left);
		pnode->data.print();
		InorderPrice(pnode->right);
	}

	void reverseInorderPrice(Node* pnode)  
	{
		if (pnode == NULL)
			return;
		reverseInorderPrice(pnode->right);
		pnode->data.print();
		reverseInorderPrice(pnode->left);
	}

public:

	Node* InsertPrice(Node* pnode, item itemData)
	{
		if (pnode == NULL)
		{
			pnode = new Node(itemData);
		}
		else if (itemData.price < pnode->data.price)
		{
			pnode->left = InsertPrice(pnode->left, itemData);
		}
		else
		{
			pnode->right = InsertPrice(pnode->right, itemData);
		}

		return pnode;
	}

	void Insert(item itemData) override {
		root = InsertPrice(root, itemData);
	}

	void DisplayPriceAsc()
	{
		cout << "\nItems in Ascending order by Price: " << endl;
		InorderPrice(root);
	}

	void DisplayPriceDsc()
	{
		cout << "\nItems in Descending order by Price: " << endl;
		reverseInorderPrice(root);
	}
};

void readItems(ifstream &file, BSTname &tree1, BSTprice &tree2) {
    if (!file.is_open()) {
        cout << "Error opening file"<<endl;
    } else {
        string line;
        getline(file, line);
        for (int i = 0; getline(file, line); i += 3) {
            string name = line;

            getline(file, line);
            string category = line;

            getline(file, line);
            int price = stoi(line);

            item ITEM(name, category, price);

            tree1.Insert(ITEM);
			tree2.Insert(ITEM);

        }
    }
}

#endif // BINARY_SEARCH_TREE_H