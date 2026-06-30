#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "item.h"
#include "Node.h"
using namespace std;





class AVL {
public:
    Node* root;

    vector<item> insertionOrder;
    AVL() : root(nullptr) {}

    int nodeHeight(Node* p) {
        int hl = (p && p->left) ? p->left->height : 0;
        int hr = (p && p->right) ? p->right->height : 0;
        return max(hl, hr) + 1;
    }

    int balanceFactor(Node* p) {
        int hl = (p && p->left) ? p->left->height : 0;
        int hr = (p && p->right) ? p->right->height : 0;
        return hl - hr;
    }


    Node* llRotation(Node* p) {
        Node* pl = p->left;
        Node* plr = pl->right;

        pl->right = p;
        p->left = plr;

        p->height = nodeHeight(p);
        pl->height = nodeHeight(pl);

        if (root == p)
            root = pl;

        return pl;
    }

    Node* rrRotation(Node* p) {
        Node* pr = p->right;
        Node* prl = pr->left;

        pr->left = p;
        p->right = prl;

        p->height = nodeHeight(p);
        pr->height = nodeHeight(pr);

        if (root == p)
            root = pr;

        return pr;
    }

    Node* lrRotation(Node* p) {
        Node* pl = p->left;
        Node* plr = pl->right;

        pl->right = plr->left;
        p->left = plr->right;

        plr->left = pl;
        plr->right = p;

        pl->height = nodeHeight(pl);
        p->height = nodeHeight(p);
        plr->height = nodeHeight(plr);

        if (root == p)
            root = plr;

        return plr;
    }

    Node* rlRotation(Node* p) {
        Node* pr = p->right;
        Node* prl = pr->left;

        pr->left = prl->right;
        p->right = prl->left;

        prl->right = pr;
        prl->left = p;

        pr->height = nodeHeight(pr);
        p->height = nodeHeight(p);
        prl->height = nodeHeight(prl);

        if (root == p)
            root = prl;

        return prl;
    }

    Node* inPre(Node* p) {
        while (p && p->right != nullptr) p = p->right;
        return p;
    }

    Node* inSucc(Node* p) {
        while (p && p->left != nullptr) p = p->left;
        return p;
    }

    Node* rInsert(Node* p, item key) {
        if (p == nullptr) {
            Node* t = new Node(key);
            return t;
        }

        if (key < p->data) p->left = rInsert(p->left, key);
        else if (key > p->data) p->right = rInsert(p->right, key);

        p->height = nodeHeight(p);
        int bf = balanceFactor(p);

        if (bf == 2) {
            if (balanceFactor(p->left) == 1) return llRotation(p);
            else return lrRotation(p);
        } else if (bf == -2) {
            if (balanceFactor(p->right) == -1) return rrRotation(p);
            else return rlRotation(p);
        }

        return p;
    }


    void insert(item key) {
        root = rInsert(root, key);
        insertionOrder.push_back(key);
    }

    Node* deleteNode(Node* p, item key) {
        if (p == nullptr) return nullptr;

        if (p->left == nullptr && p->right == nullptr) {
            if (p == root) root = nullptr;
            delete p;
            return nullptr;
        }

        if (key < p->data) p->left = deleteNode(p->left, key);
        else if (key > p->data) p->right = deleteNode(p->right, key);
        else {
            Node* q;
            if (nodeHeight(p->left) > nodeHeight(p->right)) {
                q = inPre(p->left);
                p->data = q->data;
                p->left = deleteNode(p->left, q->data);
            } else {
                q = inSucc(p->right);
                p->data = q->data;
                p->right = deleteNode(p->right, q->data);
            }
        }

        p->height = nodeHeight(p);
        int bf = balanceFactor(p);

        if (bf == 2) {
            if (balanceFactor(p->left) >= 0) return llRotation(p);
            else return lrRotation(p);
        } else if (bf == -2) {
            if (balanceFactor(p->right) <= 0) return rrRotation(p);
            else return rlRotation(p);
        }

        return p;
    }

    void deleteItem(string itemname) {
        item temp(itemname, "", 0);
        root = deleteNode(root, temp);
    }
    //int countNodes(Node* p) {
    //    if (!p) return 0;
     //   return 1 + countNodes(p->left) + countNodes(p->right);
    //}

    void inorder(Node* p, vector<item>& items) {
        if (p != nullptr) {
            inorder(p->left, items);
            items.push_back(p->data);
            inorder(p->right, items);
        }
    }

    void reverseInorder(Node* p, vector<item>& items) {
        if (p != nullptr) {
            reverseInorder(p->right, items);
            items.push_back(p->data);
            reverseInorder(p->left, items);
        }
    }

    void preOrder(Node* root) {
        if (root != nullptr) {
            root->data.print();
            preOrder(root->left);
            preOrder(root->right);
        }
    }


    vector<item> getInorder() {
        vector<item> items;
        inorder(root, items);
        return items;
    }

    void displayItemsAscending() {
        vector<item> items;
        inorder(root, items);
        sort(items.begin(), items.end(), [](const item& a, const item& b) {
            return a < b;
        });
        for (const auto& itm : items) {
            itm.print();
        }
    }

    void displayItemsDescending() {
        vector<item> items;
        inorder(root, items);
        sort(items.begin(), items.end(), [](const item& a, const item& b) {
            return a > b;
        });
        for (const auto& itm : items) {
            itm.print();
        }
    }

    void displayItemsByPriceAscending() {
        vector<item> items;
        inorder(root, items);
        sort(items.begin(), items.end(), [](const item& a, const item& b) {
            return a.price < b.price;
        });
        for (const auto& itm : items) {
            itm.print();
        }
    }

    void displayItemsByPriceDescending() {
        vector<item> items;
        inorder(root, items);
        sort(items.begin(), items.end(), [](const item& a, const item& b) {
            return a.price > b.price;
        });
        for (const auto& itm : items) {
            itm.print();
        }
    }
    // Function to print items in their original order of insertion
    void DisplayNormally() {
        cout << "Items in original order of insertion:" << endl;
        for (const auto& itm : insertionOrder) {
            itm.print();
        }
    }

};
void readItems(ifstream &file, AVL &tree) {
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    string line, name, category;
    int price;

    // Skip the first line (number of items)
    getline(file, line);

    while (getline(file, line)) {
        name = line;
        if (!getline(file, category) || !getline(file, line)) {
            cout << "Error: Invalid file format.\n";
            break;
        }
        try {
            price = stoi(line);
        } catch (const std::invalid_argument& e) {
            cout << "Error: Invalid price value. Skipping item.\n";
            continue;
        }
        item ITEM(name, category, price);
        tree.insert(ITEM);
    }
}


#endif // AVL_H