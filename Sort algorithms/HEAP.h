#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "item.h"
using namespace std;

class MaxHeap{
    vector<item>items;
    public:

    void add_item(item to_add){
        items.push_back(to_add);
    }

    void remove_item(string to_remove){
        int i=0;
        for(;i<items.size();i++){
            if(items[i].itemname==to_remove){
                break;
            }
        }
        swap(items[i],items[items.size()-1]);
        items.pop_back();
    }

    void print(){
        for(auto val:items){
            val.print();
        }
    }

    void maxHeapify_by_name(vector<item>&items,int size, int i){
        int l =i*2+1;
        int r=i*2+2;
        int max=i;
        if(l<size && items[l].itemname>items[max].itemname){
            max=l;
        }
        if(r<size && items[r].itemname>items[max].itemname){
            max=r;
        }
        if(max!=i){
            swap(items[max],items[i]);
            maxHeapify_by_name(items,size,max);
        }
    }

    void maxHeapify_by_price(vector<item>&items,int size, int i){
        int l =i*2+1;
        int r=i*2+2;
        int max=i;
        if(l<size && items[max].price<items[l].price){
            max=l;
        }
        if(r<size && items[max].price<items[r].price){
            max=r;
        }
        if(max!=i){
            swap(items[max],items[i]);
            maxHeapify_by_price(items,size,max);
        }

    }

    void buildHeap_by_name(vector<item>& items, int size){
        for(int i=(items.size()/2)-1;i>=0;i--){
            maxHeapify_by_name(items,items.size(),i);
        }
    }

    void buildHeap_by_price(vector<item>& items, int size){
        for(int i=(items.size()/2)-1;i>=0;i--){
            maxHeapify_by_price(items,items.size(),i);
        }
    }

    void heapsort_ascending_name(){
        buildHeap_by_name(items,items.size());
        for(int i=items.size()-1;i>0;i--){
            swap(items[0],items[i]);
            maxHeapify_by_name(items,i,0);
        }
        print();
    }

    void heapsort_ascending_price(){
        buildHeap_by_price(items,items.size());
        for(int i=items.size()-1;i>0;i--){
            swap(items[0],items[i]);
            maxHeapify_by_price(items,i,0);
        }
        print();
    }

};

class MinHeap{
    vector<item>items;
    public:

    void add_item(item to_add){
        items.push_back(to_add);
    }

    void remove_item(string to_remove){
        int i=0;
        for(;i<items.size();i++){
            if(items[i].itemname==to_remove){
                break;
            }
        }
        swap(items[i],items[items.size()-1]);
        items.pop_back();
    }

    void print(){
        for(auto val:items){
            val.print();
        }
    }

    void minHeapify_by_name(vector<item>&items,int size, int i){
        int l =i*2+1;
        int r=i*2+2;
        int min=i;
        if(l<size && items[l].itemname<items[min].itemname){
            min=l;
        }
        if(r<size && items[r].itemname<items[min].itemname){
            min=r;
        }
        if(min!=i){
            swap(items[min],items[i]);
            minHeapify_by_name(items,size,min);
        }
    }

    void minHeapify_by_price(vector<item>&items,int size, int i){
        int l =i*2+1;
        int r=i*2+2;
        int min=i;
        if(l<size && items[min].price>items[l].price){
            min=l;
        }
        if(r<size && items[min].price>items[r].price){
            min=r;
        }
        if(min!=i){
            swap(items[min],items[i]);
            minHeapify_by_price(items,size,min);
        }
    }

    void buildHeap_by_name(vector<item>& items, int size){
        for(int i=(items.size()/2)-1;i>=0;i--){
            minHeapify_by_name(items,items.size(),i);
        }
    }

    void buildHeap_by_price(vector<item>& items, int size){
        for(int i=(items.size()/2)-1;i>=0;i--){
            minHeapify_by_price(items,items.size(),i);
        }
    }

    void heapsort_descending_name(){
        buildHeap_by_name(items,items.size());
        for(int i=items.size()-1;i>0;i--){
            swap(items[0],items[i]);
            minHeapify_by_name(items,i,0);
        }
        print();
    }

    void heapsort_descending_price(){
        buildHeap_by_price(items,items.size());
        for(int i=items.size()-1;i>0;i--){
            swap(items[0],items[i]);
            minHeapify_by_price(items,i,0);
        }
        print();
    }

};

void readItems(ifstream &file, MaxHeap &tree1, MinHeap &tree2) {
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

            tree1.add_item(ITEM);
            tree2.add_item(ITEM);
        }
    }
}




#endif //HEAP_H