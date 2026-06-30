#include <iostream>
#include <fstream>
#include <limits>
#include "BST.h"
#include "AVL.h"
#include "HEAP.h"
#include "item.h"
#include "Search.h"
#include "Fibonacci.h"
#include "Hashing.h"
#include "SkipList.h"
#include "IntHeap.h"
#include "RedBlackTree.h"

using namespace std;

static bool readChoice(int& value) {
    if (cin >> value) return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

static void printItemOperations() {
    cout << "Choose an operation:\n"
         << "1. Add item\n"
         << "2. Remove item\n"
         << "3. Display items normally\n"
         << "4. Display items sorted by name ascending\n"
         << "5. Display items sorted by name descending\n"
         << "6. Display items sorted by price ascending\n"
         << "7. Display items sorted by price descending\n"
         << "8. Back\n";
}

static void runBSTMenu() {
    BSTname tree1;
    BSTprice tree2;

    ifstream inputFile("items.txt");
    readItems(inputFile, tree1, tree2);
    inputFile.close();

    while (true) {
        printItemOperations();
        int choice;
        if (!readChoice(choice)) break;

        if (choice == 1) {
            string name, category;
            int price;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter item category: ";
            cin >> category;
            cout << "Enter item price: ";
            cin >> price;
            item it(name, category, price);
            tree1.Insert(it);
            tree2.Insert(it);
            cout << "Item added successfully!" << endl;
        } else if (choice == 2) {
            string name;
            cout << "Enter name of item to remove: ";
            cin >> name;
            tree1.Delete(name);
            tree2.Delete(name);
            cout << "Item removed successfully!" << endl;
        } else if (choice == 3) {
            tree1.DisplayNormally();
        } else if (choice == 4) {
            tree1.DisplayNameAsc();
        } else if (choice == 5) {
            tree1.DisplayNameDsc();
        } else if (choice == 6) {
            tree2.DisplayPriceAsc();
        } else if (choice == 7) {
            tree2.DisplayPriceDsc();
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}

static void runItemHeapMenu() {
    MaxHeap maxtree;
    MinHeap mintree;

    ifstream inputFile("items.txt");
    readItems(inputFile, maxtree, mintree);
    inputFile.close();

    while (true) {
        printItemOperations();
        int choice;
        if (!readChoice(choice)) break;

        if (choice == 1) {
            string name, cat;
            int price;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter item category: ";
            cin >> cat;
            cout << "Enter item price: ";
            cin >> price;
            item newItem(name, cat, price);
            maxtree.add_item(newItem);
            mintree.add_item(newItem);
            cout << "Item added successfully:" << endl;
            maxtree.print();
        } else if (choice == 2) {
            string name;
            cout << "Enter name of item to remove: ";
            cin >> name;
            maxtree.remove_item(name);
            mintree.remove_item(name);
            cout << "Item removed successfully:" << endl;
            maxtree.print();
        } else if (choice == 3) {
            maxtree.print();
        } else if (choice == 4) {
            maxtree.heapsort_ascending_name();
        } else if (choice == 5) {
            mintree.heapsort_descending_name();
        } else if (choice == 6) {
            maxtree.heapsort_ascending_price();
        } else if (choice == 7) {
            mintree.heapsort_descending_price();
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}

static void runAVLMenu() {
    AVL tree;
    ifstream inputFile("items.txt");
    readItems(inputFile, tree);
    inputFile.close();

    while (true) {
        printItemOperations();
        int choice;
        if (!readChoice(choice)) break;

        if (choice == 1) {
            string name, category;
            int price;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter price: ";
            cin >> price;
            tree.insert(item(name, category, price));
            cout << "Item added successfully." << endl;
        } else if (choice == 2) {
            string name;
            cout << "Enter item name to remove: ";
            cin >> name;
            tree.deleteItem(name);
            cout << "Item removed successfully." << endl;
        } else if (choice == 3) {
            tree.DisplayNormally();
        } else if (choice == 4) {
            cout << "Items sorted by name ascending:" << endl;
            tree.displayItemsAscending();
        } else if (choice == 5) {
            cout << "Items sorted by name descending:" << endl;
            tree.displayItemsDescending();
        } else if (choice == 6) {
            cout << "Items sorted by price ascending:" << endl;
            tree.displayItemsByPriceAscending();
        } else if (choice == 7) {
            cout << "Items sorted by price descending:" << endl;
            tree.displayItemsByPriceDescending();
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}

static void runNonLinearMenu() {
    while (true) {
        cout << "\nNon-linear structures:\n"
             << "1. Binary Search Tree (BST)\n"
             << "2. Item Heaps (Max/Min)\n"
             << "3. AVL Tree\n"
             << "4. Back to main menu\n";

        int choice;
        if (!readChoice(choice)) break;

        if (choice == 1) runBSTMenu();
        else if (choice == 2) runItemHeapMenu();
        else if (choice == 3) runAVLMenu();
        else if (choice == 4) break;
        else cout << "Invalid choice." << endl;
    }
}

int main() {
    while (true) {
        cout << "\n=== Search Algorithms Project ===\n"
             << "1. Non-linear structures (BST, Heaps, AVL)\n"
             << "2. Linear search algorithms\n"
             << "3. Fibonacci algorithms\n"
             << "4. Hashing techniques\n"
             << "5. Skip list demo\n"
             << "6. Integer max heap demo\n"
             << "7. Red-black tree demo\n"
             << "8. Exit\n"
             << "Choice: ";

        int choice;
        if (!readChoice(choice)) {
            cout << "Goodbye!" << endl;
            return 0;
        }

        switch (choice) {
            case 1: runNonLinearMenu(); break;
            case 2: runSearchMenu(); break;
            case 3: runFibonacciMenu(); break;
            case 4: runHashingMenu(); break;
            case 5: runSkipListDemo(); break;
            case 6: runIntHeapDemo(); break;
            case 7: runRedBlackTreeDemo(); break;
            case 8:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}
