#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

inline bool readInt(int& value) {
    if (cin >> value) return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

inline void SequentialSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            cout << "Target found at index " << i << endl;
            return;
        }
    }
    cout << "Target not found in the array." << endl;
}

inline void RecursiveSequentialSearch(const vector<int>& arr, int target, int index = 0) {
    if (index >= static_cast<int>(arr.size())) {
        cout << "Target not found in the array." << endl;
        return;
    }
    if (arr[index] == target) {
        cout << "Target found at index " << index << endl;
        return;
    }
    RecursiveSequentialSearch(arr, target, index + 1);
}

inline void BinarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            cout << "Target found at index " << mid << endl;
            return;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "Target not found in the array." << endl;
}

inline void RecursiveBinarySearch(const vector<int>& arr, int target, int low, int high) {
    if (high < low) {
        cout << "Target not found in the array." << endl;
        return;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        cout << "Target found at index " << mid << endl;
        return;
    }
    if (arr[mid] > target) {
        RecursiveBinarySearch(arr, target, low, mid - 1);
    } else {
        RecursiveBinarySearch(arr, target, mid + 1, high);
    }
}

inline void runSearchMenu() {
    while (true) {
        int size;
        cout << "Enter the size of the array (0 to go back): ";
        if (!readInt(size)) return;
        if (size == 0) return;
        if (size < 0) {
            cout << "Invalid size. Please enter a positive number." << endl;
            continue;
        }

        vector<int> arr(size);
        cout << "Enter the " << size << " elements:" << endl;
        for (int i = 0; i < size; i++) {
            if (!readInt(arr[i])) return;
        }

        int target;
        cout << "Enter the target value you want to search for: ";
        if (!readInt(target)) return;

        cout << "Please choose the desired search algorithm:\n"
             << "1- Sequential search.\n"
             << "2- Recursive sequential search.\n"
             << "3- Binary search (uses sorted copy of array).\n"
             << "4- Recursive binary search (uses sorted copy of array).\n"
             << "5- Back to main menu.\n";

        int choice;
        if (!readInt(choice)) return;
        if (choice == 5) return;

        switch (choice) {
            case 1:
                SequentialSearch(arr, target);
                break;
            case 2:
                RecursiveSequentialSearch(arr, target);
                break;
            case 3: {
                vector<int> sorted = arr;
                sort(sorted.begin(), sorted.end());
                BinarySearch(sorted, target);
                break;
            }
            case 4: {
                vector<int> sorted = arr;
                sort(sorted.begin(), sorted.end());
                RecursiveBinarySearch(sorted, target, 0, static_cast<int>(sorted.size()) - 1);
                break;
            }
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

#endif
