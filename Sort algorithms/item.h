#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using namespace std;

class item{

public:
	string itemname;
	string category;
	int price;

    item(const string& name, const string& cat, int p) : itemname(name), category(cat), price(p) {}
    item() {}

    bool operator<(const item& other) const {
        return itemname < other.itemname;
    }

    bool operator>(const item& other) const {
        return itemname > other.itemname;
    }
	//bool operator<(const item& other) {
	//	return price < other.price;
	//}


    bool operator==(const item& other) {
		return price == other.price && itemname == other.itemname && category == other.category;
	}


	void print() const{
		cout << "Item: " << itemname << endl;
		cout << "Category: " << category << endl;
		cout << "Price: $" << price << endl;
	}
};
#endif // ITEM_H