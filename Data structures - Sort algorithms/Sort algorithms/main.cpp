#include <iostream>
#include <fstream>
#include "BST.h"
#include "AVL.h"
#include "HEAP.h"
#include "item.h"

using namespace std;

int main(){

    tree_choice:
    cout << "welcome, choose which non linear structure you'd like to test" << '\n'
         << "1. Binary Search tree (BST)" << '\n' << "2. Heaps" << '\n' << "3. AVL tree" << '\n';

    int choice1;
    cin >> choice1;

    if(choice1==1){
        BSTname tree1;
	    BSTprice tree2;

        ifstream inputefile1("items.txt");
        readItems(inputefile1,tree1,tree2);

        operation_choice:
        cout << "Choose an operation:" << '\n'
        << "1. Add item" << '\n'
        << "2. Remove item" << '\n'
        << "3. Display items normally" << '\n'
        << "4. Display items sorted by name ascending" << '\n'
        << "5. Display items sorted by name descending" << '\n'
        << "6. Display items sorted by price ascending" << '\n'
        << "7. Display items sorted by price descending" << '\n'
        << "8. Exit" << '\n';


        int choice2;
        cin>>choice2;

        if(choice2==1){
            string name;
			string category;
			int price;
			cout << "Enter item name: ";
			cin >> name;
			cout << "Enter item category: ";
			cin >> category;
			cout << "Enter item price: ";
			cin >> price;
			item it (name, category, price);
			tree1.Insert(it);
			tree2.Insert(it);
			cout << "Item added successfully!" << endl;
            goto operation_choice;
        }
        else if(choice2==2){
            string name;
			cout << "Enter name of item to remove: ";
			cin >> name;
			tree1.Delete(name);
			tree2.Delete(name);
			cout << "Item removed successfully!" << endl;
            goto operation_choice;
        }
        else if(choice2==3){
            tree1.DisplayNormally();
            goto operation_choice;
        }
        else if(choice2==4){
            tree1.DisplayNameAsc();
            goto operation_choice;
        }
        else if(choice2==5){
            tree1.DisplayNameDsc();
            goto operation_choice;
        }
        else if(choice2==6){
            tree2.DisplayPriceAsc();
            goto operation_choice;
        }
        else if(choice2==7){
            tree2.DisplayPriceDsc();
            goto operation_choice;
        }
        else if(choice2==8){
            cout << "Exiting program." << endl;
            goto tree_choice;
        }
        
    }
    else if(choice1==2){
        MaxHeap maxtree;
        MinHeap mintree;

        ifstream inputfile2("items.txt");
        readItems(inputfile2,maxtree,mintree);

        operation_choice2:
        cout << "Choose an operation:" << '\n'
        << "1. Add item" << '\n'
        << "2. Remove item" << '\n'
        << "3. Display items normally" << '\n'
        << "4. Display items sorted by name ascending" << '\n'
        << "5. Display items sorted by name descending" << '\n'
        << "6. Display items sorted by price ascending" << '\n'
        << "7. Display items sorted by price descending" << '\n'
        << "8. Exit" << '\n';


        int choice2;
        cin>>choice2;
        if(choice2==1){
            string name,cat;
            int price;
            cout << "Please enter name of item: " << '\n';
            cin >> name;
            cout << "Please enter category of item: " << '\n';
            cin >> cat;
            cout << "Please enter price of item: " << '\n';
            cin >> price;
            item NEW(name,cat,price);
            maxtree.add_item(NEW);
            mintree.add_item(NEW);
            cout << "item added successfully:" << '\n';
            maxtree.print();
            goto operation_choice2;
        }
        else if(choice2==2){
            string name;
            cout << "Please enter name of item: " << '\n';
            cin >> name;
            maxtree.remove_item(name);
            mintree.remove_item(name);
            cout << "item removed successfully:" << '\n';
            maxtree.print();
            goto operation_choice2;
        }
        else if(choice2==3){
            maxtree.print();
            goto operation_choice2;
        }
        else if(choice2==4){
            maxtree.heapsort_ascending_name();
            goto operation_choice2;
        }
        else if(choice2==5){
            mintree.heapsort_descending_name();
            goto operation_choice2;
        }
        else if(choice2==6){
            maxtree.heapsort_ascending_price();
            goto operation_choice2;
        }
        else if(choice2==7){
            mintree.heapsort_descending_price();
            goto operation_choice2;
        }
        else if(choice2==8){
            cout << "Exiting program." << endl;
            goto tree_choice;
        }
    }
     else if(choice1==3){
        AVL tree;
        ifstream inputfile("items.txt");
        readItems(inputfile, tree);
        inputfile.close();

        string name, category;
        int price;


        operation_choice3:
    cout << "Choose an operation:" << '\n'
         << "1. Add item" << '\n'
         << "2. Remove item" << '\n'
         << "3. Display items normally" << '\n'
         << "4. Display items sorted by name ascending" << '\n'
         << "5. Display items sorted by name descending" << '\n'
         << "6. Display items sorted by price ascending" << '\n'
         << "7. Display items sorted by price descending" << '\n'
         << "8. Exit" << '\n';


         int choice2;
         cin>>choice2;
         if(choice2==1){
             cout << "Enter item name: ";
             cin >> name;
             cout << "Enter category: ";
             cin >> category;
             cout << "Enter price: ";
             cin >> price;
             tree.insert(item(name, category, price));
             cout << "Item added successfully." << '\n';
             goto operation_choice3;
         }
         else if(choice2==2){
             cout << "Enter item name to remove: ";
             cin >> name;
             tree.deleteItem(name);
             cout << "Item removed successfully." << '\n';
             goto operation_choice3;
         }
         else if(choice2==3){
             tree.DisplayNormally();
             goto operation_choice3;
         }
         else if(choice2==4){
             cout << "Items sorted by name ascending:" << endl;
             tree.displayItemsAscending();
             goto operation_choice3;
         }
         else if(choice2==5){
             cout << "Items sorted by name descending:" << endl;
             tree.displayItemsDescending();
             goto operation_choice3;
         }
         else if(choice2==6){
             cout << "Items sorted by price ascending:" << endl;
             tree.displayItemsByPriceAscending();
             goto operation_choice3;
         }
         else if(choice2==7){
             cout << "Items sorted by price descending:" << endl;
             tree.displayItemsByPriceDescending();
             goto operation_choice3;
         }
         else if(choice2==8){
             cout << "Exiting program." << endl;
             goto tree_choice;
         }
     }
    return 0;
}