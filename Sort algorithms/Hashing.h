#ifndef HASHING_H
#define HASHING_H

#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
using namespace std;

inline int divisionMethod(int key, int tableSize) {
    return key % tableSize;
}

inline int multiplicationMethod(int key, int tableSize) {
    const double A = 0.6;
    double fractionalPart = (key * A) - floor(key * A);
    return static_cast<int>(tableSize * fractionalPart);
}

inline int midSquareMethod(int key, int tableSize) {
    int square = key * key;
    int numDigits = static_cast<int>(log10(tableSize)) + 1;
    int divisor = static_cast<int>(pow(10, numDigits));
    return (square / divisor) % tableSize;
}

inline int foldingMethod(int key, int tableSize) {
    int addressSize = static_cast<int>(log10(tableSize)) + 1;
    int partSize = static_cast<int>(pow(10, addressSize));
    int sum = 0;
    while (key > 0) {
        sum += key % partSize;
        key /= partSize;
    }
    return sum % tableSize;
}

inline void chainingInsert(vector<list<int>>& hashTable, const vector<int>& keys, int tableSize) {
    for (int key : keys) {
        int index = divisionMethod(key, tableSize);
        hashTable[index].push_back(key);
    }
}

inline void printChainingHashTable(const vector<list<int>>& hashTable) {
    for (size_t i = 0; i < hashTable.size(); i++) {
        cout << i << ": ";
        for (int key : hashTable[i]) {
            cout << key << " -> ";
        }
        cout << "NULL\n";
    }
}

inline void linearProbingInsert(vector<int>& hashTable, const vector<int>& keys, int tableSize) {
    for (int key : keys) {
        int index = divisionMethod(key, tableSize);
        while (hashTable[index] != -1) {
            index = (index + 1) % tableSize;
        }
        hashTable[index] = key;
    }
}

inline void printOpenAddressingHashTable(const vector<int>& hashTable) {
    for (size_t i = 0; i < hashTable.size(); i++) {
        cout << i << ": " << (hashTable[i] == -1 ? "EMPTY" : to_string(hashTable[i])) << "\n";
    }
}

inline int primaryHash(int key, int tableSize) {
    return key % tableSize;
}

inline int secondaryHash(int key, int tableSize, int prime) {
    return prime - (key % prime);
}

inline void doubleHashingInsert(vector<int>& hashTable, const vector<int>& keys, int tableSize, int prime) {
    for (int key : keys) {
        int h1 = primaryHash(key, tableSize);
        int h2 = secondaryHash(key, tableSize, prime);
        int i = 0;
        while (hashTable[(h1 + i * h2) % tableSize] != -1) {
            i++;
        }
        hashTable[(h1 + i * h2) % tableSize] = key;
    }
}

inline void printDoubleHashingHashTable(const vector<int>& hashTable) {
    for (size_t i = 0; i < hashTable.size(); i++) {
        cout << i << ": " << (hashTable[i] == -1 ? "EMPTY" : to_string(hashTable[i])) << "\n";
    }
}

inline vector<int> parseKeys(const string& input) {
    vector<int> keys;
    stringstream ss(input);
    int key;
    while (ss >> key) {
        keys.push_back(key);
    }
    return keys;
}

inline void runHashingMenu() {
    int choice, tableSize, prime;

    while (true) {
        cout << "\nChoose a hashing option:\n"
             << "1. Division Method\n"
             << "2. Multiplication Method\n"
             << "3. Mid Square Method\n"
             << "4. Folding Method\n"
             << "5. Chaining\n"
             << "6. Open Addressing (Linear Probing)\n"
             << "7. Double Hashing\n"
             << "8. Back to main menu\n";
        cin >> choice;

        if (choice == 8) break;

        cout << "Enter table size: ";
        cin >> tableSize;
        cin.ignore();

        if (choice >= 5 && choice <= 7) {
            cout << "Enter space-separated keys: ";
        } else {
            cout << "Enter key: ";
        }

        string input;
        getline(cin, input);
        vector<int> keys = parseKeys(input);
        if (keys.empty()) {
            cout << "No keys entered.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Hash Value (Division Method): " << divisionMethod(keys[0], tableSize) << "\n";
                break;
            case 2:
                cout << "Hash Value (Multiplication Method): " << multiplicationMethod(keys[0], tableSize) << "\n";
                break;
            case 3:
                cout << "Hash Value (Mid Square Method): " << midSquareMethod(keys[0], tableSize) << "\n";
                break;
            case 4:
                cout << "Hash Value (Folding Method): " << foldingMethod(keys[0], tableSize) << "\n";
                break;
            case 5: {
                vector<list<int>> chainingHashTable(tableSize);
                chainingInsert(chainingHashTable, keys, tableSize);
                cout << "Chaining Hash Table:\n";
                printChainingHashTable(chainingHashTable);
                break;
            }
            case 6: {
                vector<int> openAddressingHashTable(tableSize, -1);
                linearProbingInsert(openAddressingHashTable, keys, tableSize);
                cout << "Open Addressing Hash Table:\n";
                printOpenAddressingHashTable(openAddressingHashTable);
                break;
            }
            case 7: {
                prime = tableSize - 1;
                vector<int> doubleHashingHashTable(tableSize, -1);
                doubleHashingInsert(doubleHashingHashTable, keys, tableSize, prime);
                cout << "Double Hashing Hash Table:\n";
                printDoubleHashingHashTable(doubleHashingHashTable);
                break;
            }
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
}

#endif
