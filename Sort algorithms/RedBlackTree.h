#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
using namespace std;

enum RBColor { RED, BLACK };

struct RBNode {
    int data;
    RBColor color;
    RBNode *left, *right, *parent;

    explicit RBNode(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;

    void rotateLeft(RBNode* node) {
        RBNode* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (!node->parent)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(RBNode* node) {
        RBNode* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (!node->parent)
            root = leftChild;
        else if (node == node->parent->right)
            node->parent->right = leftChild;
        else
            node->parent->left = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsert(RBNode* node) {
        while (node->parent && node->parent->color == RED) {
            RBNode* grandparent = node->parent->parent;

            if (node->parent == grandparent->left) {
                RBNode* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            } else {
                RBNode* uncle = grandparent->left;

                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void fixDelete(RBNode* x) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            RBNode* parent = x ? x->parent : nullptr;
            if (!parent) break;

            bool isLeftChild = (x == parent->left);
            RBNode* w = isLeftChild ? parent->right : parent->left;

            if (!w) break;

            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                if (isLeftChild) rotateLeft(parent);
                else rotateRight(parent);
                w = isLeftChild ? parent->right : parent->left;
                if (!w) break;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
            } else {
                if ((isLeftChild && (!w->right || w->right->color == BLACK)) ||
                    (!isLeftChild && (!w->left || w->left->color == BLACK))) {
                    w->color = RED;
                    if (isLeftChild) {
                        if (w->left) w->left->color = BLACK;
                        rotateRight(w);
                    } else {
                        if (w->right) w->right->color = BLACK;
                        rotateLeft(w);
                    }
                    w = isLeftChild ? parent->right : parent->left;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (isLeftChild) {
                    if (w->right) w->right->color = BLACK;
                    rotateLeft(parent);
                } else {
                    if (w->left) w->left->color = BLACK;
                    rotateRight(parent);
                }
                x = root;
            }
        }
        if (x) x->color = BLACK;
    }

    RBNode* bstDelete(RBNode* z) {
        RBNode* y = z;
        RBNode* x = nullptr;

        if (!z->left)
            x = z->right;
        else if (!z->right)
            x = z->left;
        else {
            y = getMin(z->right);
            z->data = y->data;
        }

        if (y) {
            if (x)
                x->parent = y->parent;
            if (!y->parent)
                root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
            if (y != z)
                delete y;
        }
        return x;
    }

    RBNode* getMin(RBNode* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    RBNode* findNode(RBNode* node, int data) {
        if (!node || node->data == data)
            return node;

        if (data < node->data)
            return findNode(node->left, data);
        return findNode(node->right, data);
    }

    RBNode* bstInsert(RBNode* current, RBNode* newNode) {
        if (!current)
            return newNode;

        if (newNode->data < current->data) {
            current->left = bstInsert(current->left, newNode);
            current->left->parent = current;
        } else if (newNode->data > current->data) {
            current->right = bstInsert(current->right, newNode);
            current->right->parent = current;
        }

        return current;
    }

    void inorder(RBNode* node) const {
        if (node) {
            inorder(node->left);
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inorder(node->right);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        RBNode* newNode = new RBNode(data);
        root = bstInsert(root, newNode);
        fixInsert(newNode);
    }

    void deleteNode(int data) {
        RBNode* node = findNode(root, data);
        if (node) {
            RBNode* replacement = bstDelete(node);
            fixDelete(replacement);
        }
    }

    void display() const {
        inorder(root);
        cout << endl;
    }
};

inline void runRedBlackTreeDemo() {
    RedBlackTree rbt;

    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(5);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);

    cout << "Inorder after insertions: ";
    rbt.display();

    rbt.deleteNode(20);
    rbt.deleteNode(10);
    cout << "Inorder after deletion: ";
    rbt.display();
}

#endif
